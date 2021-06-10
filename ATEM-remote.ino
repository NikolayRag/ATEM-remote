/*
 * 
 * 
 */
 
#include <Ethernet.h>


byte mac[] = {0x00,0x01,0x02,0x03,0x04,0x05};
IPAddress selfIp(192, 168, 1, 222);
IPAddress atemIp(192, 168, 1, 241);



EthernetUDP UDP;
unsigned long Timeout;


void setup() {
  Ethernet.begin(mac,selfIp);

  Serial.begin(9600);
  Serial.print("init\n");

  Timeout = millis()+1000;
}

void loop() {
  int success;

  if (millis()>Timeout){

      Serial.print("\nConnect");
      do {
          success = UDP.beginPacket(atemIp,5000);
          Serial.print(success ? " ok\n" : " fail\n");
      } while (!success && (millis()<Timeout));
      
      if (success) {
        success = UDP.write("hello world from arduino");
        Serial.print("Sent "); Serial.print(success); Serial.print(" bytes, ");

        success = UDP.endPacket();
        Serial.print(success ? "ok\n" : "fail\n");

        do {
          success = UDP.parsePacket();
          Serial.print(".");
        } while (!success && (millis()<Timeout));
        
        Serial.print(success ? " parse ok\n" : " parse none\n");


        if (success) {
          Serial.print(F("received '")); Serial.print(UDP.available()); Serial.print("b:\n");

          while (UDP.available()) {
            char c = UDP.read();
            Serial.print(c);
          }
          

          UDP.flush();
        }
        
      }

      UDP.stop();
      Timeout = millis()+1000;
    }
}
