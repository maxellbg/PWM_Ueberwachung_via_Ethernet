unsigned long timer = 0;

void output_Ethernet(){
  EthernetClient client = server.available();
  if (client) {  
    timer=millis();
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          // output the value of each analog input pin
          client.println("<data>");
          client.print("<loops>"); client.print(loops); client.println("</loops>");
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.println("<analogSensors>");
            client.print("<"); client.print("analogPin"); client.print(">"); client.print(analogChannel); client.print("</"); client.print("analogPin"); client.println(">");           
            client.print("<"); client.print("value"); client.print(">"); client.print(sensorReading); client.print("</"); client.print("value"); client.println(">");
            client.println("</analogSensors>");
          }
//------------------------------------------------------------------------------------------
          for (int j = 0; j < pinCount; j++)  {
            client.println("<errorCount>");
            client.print("<"); client.print("pin"); client.print(">"); client.print(pinIn[j]); client.print("</"); client.print("pin"); client.println(">");           
            client.print("<"); client.print("value"); client.print(">"); client.print(errorCount[j]); client.print("</"); client.print("value"); client.println(">");
            client.println("</errorCount>");
          }
            
//------------------------------------------------------------------------------------------ 
          
          
          //client.print("<ArduinoLoops>"); client.print(loopCount); client.println("</ArduinoLoops>");
          client.print("</data>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.print("client disconnected ");
    Serial.print("time2translmit:"); Serial.println(millis()-timer);
  }
}
