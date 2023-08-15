# RocciBoard Library

> Dieses Repository beinhaltet Projekte, Bibliotheken und Dateien, die für die Entwicklung der RocciBoard-Bibliothek notwendig sind.
> Funktionen und Komponenten der Bibliothek können **Fehler und Bugs enthalten**, **unvollständig**, **ungetestet** oder **nur für den experimentellen Gebrauch** bestimmt sein.
> Funktion und Vollständigkeit dieses Repositorys können nicht garantiert werden, **bitte den Inhalt daher mit Vorsicht genießen**!

Bibliothek zur Verwendung des RocciBoard Arduino Shield des [Robotics Competence Center Illertal e. V. (RoCCI e. V.)](https://rocci.net).
Die Bibliothek beinhaltet grundlegende und erweiterte Funktionen zur Verwendung von Funktionen des Boards, von Motoren und von Sensoren.
Klassen und Einbindungen sind zwar für das RocciBoard ausgelegt, können jedoch meist universell Verwendet werden und bieten eine komfortable und
vereinfachte Verwendung. *In der folgenden Dokumentation werden alle Funktionen ausgiebig erläutert und beschrieben.*

---

## Grundlagen

Die Bibliothek wird durch `#include "rocciboard.h"` **in das Projekt eingebunden**. Diese Precompiler-Anweisung beinhaltet bereits alle benötigten Biblitheken und Abhängigkeiten.    
Um das RocciBoard zu verwenden, muss in der Deklarations-Sektion des Projektes ein **RocciBoard-Objekt deklariert werden**. Dies wird durch die Anweisung `RocciBoard rb` erreicht, wobei `rb` als Bezeichner des RocciBoard-Objektes frei wählbar ist. Dieser festgelegte Name muss allerdings bei allen weiteren Aufrufen verwendet werden. In dieser Dokumentation wird der Bezeichner `rb` beibehalten.    
Das RocciBoard muss vor der **erstmaligen Verwendung initialisiert** werden, dazu wird die Funktion `rb.init()` aufgerufen.    

***Beispiel:***

```cpp
    #include "rocciboard.h"
    RocciBoard rb;
    void setup() {
        rb.init();
    }
```

---

## Grundfunktionen

Beschreibung

* Auflistung der Funktionen

***Beispiele:***

```cpp
    Beispielcode()
```

---

## Motoren

Die **Verwendung von Motoren** ist in jedem RocciBoard-Projekt **standardmäßig eingebunden**, bedarf also keiner weiteren Initilisierung.
Funktionen zur Ansteuerung von Motoren finden sich in den RBMotor-Objekten, die unter `rb.motor[i]` als Array im RocciBoard-Objekt zu finden sind. Der Index `i` gibt den anzusteuernden Motor an, also die Nummer des Motors von 0 bis 3. Eine Funktion der Motoren wird mit `rb.motor[i].eineFunktion()` aufgerufen.

* `[void] rotate(int16_t speed)` - Der Motor beginnt mit der Geschwindigkeit `speed` zu rotieren. 
Die Geschwindigkeit wird von -255 bis +255 angegeben, negative Werte lassen den Motor rückwärts rotieren.
* `[void] stop(bool brake)` - Der Motor wird gestoppt. `brake` gibt an, ob der Motor elektromechanisch gebremst wird 
oder ob er bis zum Stillstand auslaufen soll. Der Parameter `brake` ist optional und wird bei weglassen durch `true` ersetzt.
* `[int16_t] getSpeed(void)` - Gibt die aktuell eingestellte Geschwindigkeit des Motors zurück. (-255 bis +255)

***Beispiele:***

```cpp
    rb.motor[0].rotate(100);
    rb.motor[3].rotate(-200);
    rb.motor[EINE_INT_KONSTANTE].rotate(eine_int_variable);
    rb.motor[2].stop(false);
    rb.motor[EINE_BOOL_KONSTANTE].stop(eine_bool_variable);
    int speed = rb.motor[1].getSpeed();
    eine_int_variable = rb.motor[EINE_INT_KONSTANTE].getSpeed();
```

---

## Standardisierte Sensoren

Beschreibung

* Auflistung der Funktionen

***Beispiel:***

```cpp
    Beispielcode()
```

#### Kompass-Sensor (BNO055)

Beschreibung des Sensors

* Auflistung der Funktionen

#### Laser-Sensor (VL53L0X bzw. VL53L1X)

Beschreibung des Sensors

* Auflistung der Funktionen

---

## Nicht-standardisierte Sensoren

Beschreibung

***Beispiel:***

```cpp
    Beispielcode()
```