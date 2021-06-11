/*
Atem helper

Based on https://github.com/mathijsk/Arduino-Library-for-ATEM-Switchers

To use https://github.com/UIPEthernet/UIPEthernet library (with ENC28j60 chip)
make EthernetUDP.h alias for provided UIPUdp.h
 */


#include <SPI.h> 
#include <Ethernet.h>

#include <ATEM.h>


byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x6B, 0xB9};
IPAddress selfIp(192, 168, 1, 222);
IPAddress atemIp(192, 168, 1, 241);

ATEM AtemSwitcher(atemIp,56789);


void setup() {
  Serial.begin(115200);


  Ethernet.begin(mac, selfIp);

  AtemSwitcher.serialOutput(0x80);
  AtemSwitcher.connect();


  Serial.print("Init ok\n");
}


void loop() {

  AtemSwitcher.runLoop();

  
  Serial.print(".\n");
  delay(500);
}
