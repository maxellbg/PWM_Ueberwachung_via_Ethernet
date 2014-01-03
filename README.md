# PWM-Überwachung und zählen der Fehler

Überwachung eines PWM-Signals welches im Fall eines Fehlers für 3sec auf Masse gezogen wird.


Beschreibung:
Sketch checkt ob Pins eine Zeit lang LOW sind.
wenn die definierte Zeit überschritten ist wird ein Fehler gesetzt, dieser wird 
erst resettet sobald der Pin wieder HIGH war.
Die Fehler werden in "errorCount" gezählt

(c) 2014 by maxellbg
