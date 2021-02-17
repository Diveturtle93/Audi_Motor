# **ADC Zuweisung**

Es sind zehn Kanäle für die ADC Auswertung vorgesehen. Jedem Kanal ist eine entsprechende
Priorisierung und ein dafür vorgesehenes Timing zugewiesen. Die Priorisierung ist von eins
bis zehn (wichtig bis unwichtig) aufgelistet. System relevante Signale bekommen eine hohe
Priorität, Signale die eher dem Komfort dienen eine niedrige Priorität. Zusätzlich ist
die Pinbelegung und die Aufgabe mit aufgeführt.

Der AD-Wandler kann nur mit einer maximalen Frequenz von 2.4 MHz Konversationen durchführen.
Bei einer APB2-Frequenz von 108 MHz muss noch ein Vorteiler gewählt werden, um den
AD-Wandler wieder mit einem zulässigen Clock zu betreiben. Gewählt wird hier der Teiler
vier. Mit diesem läuft der AD-Wandler nun mit einer Frequenz von 27 MHz.

Alle Ergbnisse werden als 12bit ausgegeben.

## Liste der AD-Kanäle

| Kanal | Pin | Funktion | Timing | Priorisierung |
|:----- |:---:|:-------- | ------:|:-------------:|
| Channel 3 | PA3 | KL15 | 5000ms | 6 |
| Channel 4 | PA4 | Kühlwasser | 5000ms | 3 |
| Channel 5 | PA5 | Klima-Flap | 1000ms | 4 |
| Channel 6 | PA6 | Gaspedal | 100ms | 2 |
| Channel 7 | PA7 | PCB | 5000ms | 7 |
| Channel 8 | PB0 | Return | 1000ms | 9 |
| Channel 9 | PB1 | Info | 1000ms | 10 |
| Channel 14 | PC4 | Bremsdruck | 100ms | 1 |
| Channel 15 | PC5 | Bremsdrucktemperatur | 5000ms | 5 |
| Channel 18 | Temperatur Sensor | STM32 Temperatur | 1000ms | 8 |

## Priorisierung der AD-Kanäle

Die Priorisierung dient dazu die Wichtigkeit eins Signales festzulegen. Diese müssen im
Programm entsprechend deutlich häufiger eingelesen und ausgewertet werden. Zudem können
Signale mit eine niedrigen Priorisierung auch wärend des Programmablaufes vernachlässigt
werden, sollte dies den Programmablauf stören.

## Zeitliches Timing der einzelnen Konversationen

Das zeitliche Timing gibt an wie oft ein Signal ausgewertet werden muss. Dabei ist wichtig
eine dynamische Veränderung des Signales mit zu berücksichtigen. So sind schnell veränderbare
Signale deutlich häufiger ausgewertet als langsame Temperaturanstiege.

## Pinbeschreibung

Im nachfolgenden werden die Aufgaben der Pins beschrieben. Zwei Pins sind dabei besonders
wichtig. Dies sind die Pins PA6 und PC4. Sie sind für die Auswertung des Gaspedals und
für den Bremsdruck zuständig.

Des Weiteren werden insgesamt vier Temperaturen eingelesen. Zwei sind dabei auf der Platine
(STM32 und PCB). Die anderen beiden Temperaturen kommen von externen Sensoren.

Zudem werden die Klima-Flap-Stellung und die Spannung der KL15 im Motorsteuergerät
eingelesen und ausgewertet.

Als letztes sind noch zwei analoge Eingänge für ein Tasterelement vorhanden. Hierbei wird
über unterschiedliche Spannungen eine Tastendruck erkannt.

## Sampletime Cycles

Eine zusätzliche Einstellung wird noch an den Sampletime Cycles vorgenommen. Dies ist eine
Zeitverzögerung, die für ein genaueres Ergebnis sorgen soll. Dabei wird der halte Konensator
um die entsprechenden Clock-Cycles geladen. Danach werden nochmal zwölf Clock-Cycles
für eine Konversation des AD-Wertes benötigt.