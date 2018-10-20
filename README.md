Rechnerachitektur Praktikum SS 2018, Projekt 1: Signalfilter in Assembler - 15.06.2018
=======================================================================================

Dieser in Assambler und C implementierte Filter filtert verrauschte Signale, 
indem er eine Sequenz von vorzeichenbehaften 32-Bit Ganzzahlen entgegennimmt und 
mit einer frei wählbaren Gewichtung jeweils einen exponentiell gleitenden Mittelwert 
für die Einzelwerte errechnet.

Vorraussetzungen
-----------------
1.	Betriebssytem: Ubuntu 32 Bit 
2.	GNU C-Compiler GCC
3.	Netwide Assembler NASM

Installation
-------------
1.	Ordner der Implementierung aus SVN klonen.
2.	In den Ordner wechseln.

Ausführen von Tests
--------------------
1.	Die Tests im C-Rahmenprogramm laufen bei Ausführung nacheinander ab.
	Hinweise zum Ändern der Tests im Abschnitt "Ändern der Tests".
2.	Kompillieren der Assembler- und C-Programme und erstellen aller benötigter Dateien durch den Befehl `make`.
3.	Ausführen der Tests durch den Befehl `make run`.
4.	Löschen der für die Ausführung erzeugten Dateien mit dem Befehl `make clean`.

Ändern der Tests 
-----------------
- 	Die beiden konstanten Testsignale testData1 und testData2 sowie die Werte für alpha und beta
	können bearbeitet werden. Standardwerte sind gegeben.
-	Die randomisierten Testdaten werden automatisch erstellt. Ihre Länge wird durch randomSetLength bestimmt, 
	der maximal zugelassene Wert durch maxIntRandom. Diese können zu testzwecken verändert werden.
-   Nach dem Muster der bereits vorhandenen Tests durch die Validierungsfunktion können auch eigene Tests 
    unterhalb der vorhandenen eigefügt werden.  
-	Wichtig: Nach dem Ändern von Tests muss vor ihrer Ausführung (Ablauf siehe "Ausführen von Tests") `make clean` 
    aufgerufen werden.

Bemerkung zu Tests bei großen Werten
------------------------------------
Unterschiede in den errechneten Werten von Validierung und Filter deuten nicht zwingend auf eine Fehlfunktion des Filters hin,
da nicht bekannt ist, wie der C-Compiler die Berechnung der Floatingpoints handhabt. Gerade bei großen Float-Werten können hier
Ungenauigkeiten aufkommen (welche sich je nach alpha/beta weiter in den weiteren Berchnungen propagieren können). 
Daher ist es hilfreich, die einzelnen tatsächlich unterschiedlichen Werte zu betrachten, um die richtige Funktionsweise des 
Bausteins zu bewerten.

Befehle
--------
		compile: make
		run: make run
		cleanup: make clean


# Project Title

One Paragraph of project description goes here

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system


### And coding style tests

Explain what these tests test and why

```
Give an example
```




## Authors

* **Billie Thompson** - *Initial work* - 

* **Adrian Steffan** - Coding [adriansteffan](https://github.com/adriansteffan)
* **Vera Kowalczuk** - ########################### [verakowalczuk](https://github.com/verakowalczuk)
* **Uzay Gök** - *Testcase design*


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details




	