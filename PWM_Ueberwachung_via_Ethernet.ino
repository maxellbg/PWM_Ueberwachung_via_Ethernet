/***********************************************************************************
  Sketch zu checken ob Pins eine Zeit lang LOW sind.
  wenn die definierte Zeit überschritten ist wird ein Fehler gesetzt, dieser wird 
  erst resettet sobald der Pin wieder HIGH war.
  Die Fehler werden in "errorCount" gezählt
 ***********************************************************************************/

//Eingaben:
int lowTimer = 500;                  // Entscheidungskriterium wie lange der Pin auf 0 muss [ms]
int ausgabeFreq = 20000;                // in welcher Frequenz soll ein Wert ausgegeben werden [ms] ? 

//***********************************************************************************
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 178, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
//***********************************************************************************

int pinIn[] = {2, 4, 6, 8, 10, 12};   // Pins die als Eingang dienen
int pinCount = 6;                     // Anzahl der Pins die gemessen werden
int pinInState[6];                    // welchen Status hat der Pin HIGH oder LOW
unsigned long loopTimer[6];           // der Timer wird in der jeweiligen Schleife gesetzt wenn der Pin LOW ist
int error[6];                         // wichtig für Timer1 um diesen nicht jedes mal wieder zu setzen
int errorRepeat[6];                   // wurde der Fehler evtl im letzten Loop schon gezählt ? wenn ja dann 1
unsigned long errorCount[6];          // Zähler für die Fehler

// grundsätzliches
int LED = 13;
unsigned long secRunning;
unsigned long printTimer = 0;         // Timer für die Ausgabe
unsigned long loops = 0;              // zählt wie viele loops durchlaufen wurden
unsigned long loops1 = 0;             // Merker für die Ausgabe zur berechnung der seid letzter Ausgabe durchlaufenen loops
int loops2 = 0;                       // loops seid letzter Ausgabe


void setup() {
  for (int j = 0; j < pinCount; j++)  {
    pinMode(pinIn[j], INPUT);
    pinInState[j] = 0;
    error[j] = 0;
    errorRepeat[j] = 0;
    errorCount[j] = 0;
  }
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("booting...");
  digitalWrite(LED, LOW);
//***********************************************************************************  
    // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
//***********************************************************************************
  delay(1000);
  Serial.println("done");
  
}

void loop() {
  output_Ethernet();
  for (int j = 0; j < pinCount; j++)  {
    pinInState[j] = digitalRead(pinIn[j]);
    if (pinInState[j] == LOW) {
      if (error[j] == 0) {
        error[j] = 1;
        loopTimer[j] = millis();
      }
      if (millis() - loopTimer[j] >= lowTimer) {      
        if (errorRepeat[j] == 0) {
          errorCount[j] = errorCount[j] + 1;
          errorRepeat[j] = 1;
          digitalWrite(LED, HIGH);
        }
      }
    }
    else {
      errorRepeat[j] = 0;
      error[j] = 0;
      digitalWrite(LED, LOW);
    }
  }
  loops = loops + 1;
  output_Serial();
}


void output_Serial() {
  if (millis()-printTimer >= ausgabeFreq) {
    secRunning= millis()/1000;
    loops2 = loops - loops1;
    loops1 = loops;
    if (printTimer == 0) {
      // 
      Serial.print("secRunning");
      Serial.print(";");
      for (int j = 0; j < pinCount; j++)  {
        Serial.print("Error_auf_PinIn");
        Serial.print(pinIn[j]);
        Serial.print(";");
      }
      Serial.print("Schleifen_seid_letzter_Ausgabe"); 
      Serial.println(";");
    }  
    printTimer= millis();
    Serial.print(secRunning);
    Serial.print("  ;  ");
    for (int j = 0; j < pinCount; j++)  {
      Serial.print(errorCount[j]);
      Serial.print("  ;  ");
    }
    Serial.print(loops2); 
    Serial.println("  ;  ");
  }
}
