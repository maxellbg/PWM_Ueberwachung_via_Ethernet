# PWM-�berwachung und z�hlen der Fehler

�berwachung eines PWM-Signals welches im Fall eines Fehlers f�r 3sec auf Masse gezogen wird.


Beschreibung:
Sketch checkt ob Pins eine Zeit lang LOW sind.
wenn die definierte Zeit �berschritten ist wird ein Fehler gesetzt, dieser wird 
erst resettet sobald der Pin wieder HIGH war.
Die Fehler werden in "errorCount" gez�hlt

(c) 2014 by maxellbg
