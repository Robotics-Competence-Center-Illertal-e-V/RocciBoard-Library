/**
 * @file rbmotor.cpp
*/

#include "Arduino.h"
#include "rbmotor.h"

#if defined(__SAM3X8E__)

#ifdef __cplusplus
extern "C" {
#endif

#define NEW_PWM_FREQUENCY 32000
#define NEW_TC_FREQUENCY 32000

static int _writeResolution = 8;

static uint8_t PWMEnabled = 0;
static uint8_t TCChanEnabled[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};


static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) {
	if (from == to)
		return value;
	if (from > to)
		return value >> (from-to);
	else
		return value << (to-from);
}

static void TC_SetCMR_ChannelA(Tc *tc, uint32_t chan, uint32_t v)
{
	tc->TC_CHANNEL[chan].TC_CMR = (tc->TC_CHANNEL[chan].TC_CMR & 0xFFF0FFFF) | v;
}

static void TC_SetCMR_ChannelB(Tc *tc, uint32_t chan, uint32_t v)
{
	tc->TC_CHANNEL[chan].TC_CMR = (tc->TC_CHANNEL[chan].TC_CMR & 0xF0FFFFFF) | v;
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
void custom_analogWrite(uint32_t ulPin, uint32_t ulValue) {
	uint32_t attr = g_APinDescription[ulPin].ulPinAttribute;

	if ((attr & PIN_ATTR_ANALOG) == PIN_ATTR_ANALOG) {
		EAnalogChannel channel = g_APinDescription[ulPin].ulADCChannelNumber;
		if (channel == DA0 || channel == DA1) {
			uint32_t chDACC = ((channel == DA0) ? 0 : 1);
			if (dacc_get_channel_status(DACC_INTERFACE) == 0) {
				/* Enable clock for DACC_INTERFACE */
				pmc_enable_periph_clk(DACC_INTERFACE_ID);

				/* Reset DACC registers */
				dacc_reset(DACC_INTERFACE);

				/* Half word transfer mode */
				dacc_set_transfer_mode(DACC_INTERFACE, 0);

				/* Power save:
				 * sleep mode  - 0 (disabled)
				 * fast wakeup - 0 (disabled)
				 */
				dacc_set_power_save(DACC_INTERFACE, 0, 0);
				/* Timing:
				 * refresh        - 0x08 (1024*8 dacc clocks)
				 * max speed mode -    0 (disabled)
				 * startup time   - 0x10 (1024 dacc clocks)
				 */
				dacc_set_timing(DACC_INTERFACE, 0x08, 0, 0x10);

				/* Set up analog current */
				dacc_set_analog_control(DACC_INTERFACE, DACC_ACR_IBCTLCH0(0x02) |
											DACC_ACR_IBCTLCH1(0x02) |
											DACC_ACR_IBCTLDACCORE(0x01));
			}

			/* Disable TAG and select output channel chDACC */
			dacc_set_channel_selection(DACC_INTERFACE, chDACC);

			if ((dacc_get_channel_status(DACC_INTERFACE) & (1 << chDACC)) == 0) {
				dacc_enable_channel(DACC_INTERFACE, chDACC);
			}

			// Write user value
			ulValue = mapResolution(ulValue, _writeResolution, DACC_RESOLUTION);
			dacc_write_conversion_data(DACC_INTERFACE, ulValue);
			while ((dacc_get_interrupt_status(DACC_INTERFACE) & DACC_ISR_EOC) == 0);
			return;
		}
	}

	if ((attr & PIN_ATTR_PWM) == PIN_ATTR_PWM) {
		ulValue = mapResolution(ulValue, _writeResolution, PWM_RESOLUTION);

		if (!PWMEnabled) {
			// PWM Startup code
		    pmc_enable_periph_clk(PWM_INTERFACE_ID);
		    PWMC_ConfigureClocks(NEW_PWM_FREQUENCY * PWM_MAX_DUTY_CYCLE, 0, VARIANT_MCK);
			PWMEnabled = 1;
		}

		uint32_t chan = g_APinDescription[ulPin].ulPWMChannel;
		if ((g_pinStatus[ulPin] & 0xF) != PIN_STATUS_PWM) {
			// Setup PWM for this pin
			PIO_Configure(g_APinDescription[ulPin].pPort,
					g_APinDescription[ulPin].ulPinType,
					g_APinDescription[ulPin].ulPin,
					g_APinDescription[ulPin].ulPinConfiguration);
			PWMC_ConfigureChannel(PWM_INTERFACE, chan, PWM_CMR_CPRE_CLKA, 0, 0);
			PWMC_SetPeriod(PWM_INTERFACE, chan, PWM_MAX_DUTY_CYCLE);
			PWMC_SetDutyCycle(PWM_INTERFACE, chan, ulValue);
			PWMC_EnableChannel(PWM_INTERFACE, chan);
			g_pinStatus[ulPin] = (g_pinStatus[ulPin] & 0xF0) | PIN_STATUS_PWM;
		}

		PWMC_SetDutyCycle(PWM_INTERFACE, chan, ulValue);
		return;
	}

	if ((attr & PIN_ATTR_TIMER) == PIN_ATTR_TIMER) {
		// We use MCLK/2 as clock.
		const uint32_t TC = VARIANT_MCK / 2 / NEW_TC_FREQUENCY;

		// Map value to Timer ranges 0..255 => 0..TC
		ulValue = mapResolution(ulValue, _writeResolution, TC_RESOLUTION);
		ulValue = ulValue * TC;
		ulValue = ulValue / TC_MAX_DUTY_CYCLE;

		// Setup Timer for this pin
		ETCChannel channel = g_APinDescription[ulPin].ulTCChannel;
		static const uint32_t channelToChNo[] = { 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2 };
		static const uint32_t channelToAB[]   = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
		static Tc *channelToTC[] = {
			TC0, TC0, TC0, TC0, TC0, TC0,
			TC1, TC1, TC1, TC1, TC1, TC1,
			TC2, TC2, TC2, TC2, TC2, TC2 };
		static const uint32_t channelToId[] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8 };
		uint32_t chNo = channelToChNo[channel];
		uint32_t chA  = channelToAB[channel];
		Tc *chTC = channelToTC[channel];
		uint32_t interfaceID = channelToId[channel];

		if (!TCChanEnabled[interfaceID]) {
			pmc_enable_periph_clk(TC_INTERFACE_ID + interfaceID);
			TC_Configure(chTC, chNo,
				TC_CMR_TCCLKS_TIMER_CLOCK1 |
				TC_CMR_WAVE |         // Waveform mode
				TC_CMR_WAVSEL_UP_RC | // Counter running up and reset when equals to RC
				TC_CMR_EEVT_XC0 |     // Set external events from XC0 (this setup TIOB as output)
				TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR |
				TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR);
			TC_SetRC(chTC, chNo, TC);
		}
		if (ulValue == 0) {
			if (chA)
				TC_SetCMR_ChannelA(chTC, chNo, TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_CLEAR);
			else
				TC_SetCMR_ChannelB(chTC, chNo, TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_CLEAR);
		} else {
			if (chA) {
				TC_SetRA(chTC, chNo, ulValue);
				TC_SetCMR_ChannelA(chTC, chNo, TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET);
			} else {
				TC_SetRB(chTC, chNo, ulValue);
				TC_SetCMR_ChannelB(chTC, chNo, TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_SET);
			}
		}
		if ((g_pinStatus[ulPin] & 0xF) != PIN_STATUS_PWM) {
			PIO_Configure(g_APinDescription[ulPin].pPort,
					g_APinDescription[ulPin].ulPinType,
					g_APinDescription[ulPin].ulPin,
					g_APinDescription[ulPin].ulPinConfiguration);
			g_pinStatus[ulPin] = (g_pinStatus[ulPin] & 0xF0) | PIN_STATUS_PWM;
		}
		if (!TCChanEnabled[interfaceID]) {
			TC_Start(chTC, chNo);
			TCChanEnabled[interfaceID] = 1;
		}
		return;
	}

	// Defaults to digital write
	pinMode(ulPin, OUTPUT);
	ulValue = mapResolution(ulValue, _writeResolution, 8);
	if (ulValue < 128)
		digitalWrite(ulPin, LOW);
	else
		digitalWrite(ulPin, HIGH);
}

#ifdef __cplusplus
}
#endif

#elif defined(__AVR__)

    #define custom_analogWrite(pin, duty) analogWrite(pin, duty)

#endif


RBMotor::RBMotor (uint8_t pin_1, uint8_t pin_2)
{
    pin_1_ = pin_1;
    pin_2_ = pin_2;
}

void RBMotor::init (void)
{
    pinMode(pin_1_, OUTPUT);
    pinMode(pin_2_, OUTPUT);
    stop(false);
}

void RBMotor::stop (bool brake)
{
    // 1-1: Using the slow-current-decay brake mode of the DRV8871
    // 0-0: Using the fast-current-decay coast mode of the DRV8871
    custom_analogWrite(pin_1_, brake ? 255 : 0);
    custom_analogWrite(pin_2_, brake ? 255 : 0);
    speed_ = 0;
}

void RBMotor::rotate (int16_t speed)
{
    // PWM should switch between braking and powering according to the DRV8871 datasheet (-> inverse PWM value)
    custom_analogWrite(pin_1_, speed < 0 ? 255 : 255 - speed);
    custom_analogWrite(pin_2_, speed < 0 ? 255 + speed : 255);
    speed_ = speed;
}

int16_t RBMotor::getSpeed (void)
{
    return speed_;
}