#include <Arduino.h>
#include "./ledButton.h"
#include "./eepromTest.h"
#include "./spiFlashTest.h"
#include "./rs232Test.h"
#include "./rs485Test.h"
#include "./canTest.h"
#include "./ethTest.h"

LedButtons    ledButton;
EepromTest    eepromTest;
SpiFlashTest  spiFlashTest;
Rs232Test     rs232Test;
Rs485Test     rs485Test;
CanTest       canTest;
EthTest       ethTest;

void setup() { 
  Serial.begin(115200);  
  ledButton.setup();
  rs232Test.setup();
  rs485Test.setup();
  canTest.setup();
  ethTest.setup();

  Serial.println("EEPROM TEST START");
  if(!eepromTest.start())
  {
    Serial.println("EEPROM TEST FAILED");
    return;
  }
  Serial.println("EEPROM TEST DONE");
  
  Serial.println("FLASH TEST START");
  if(!spiFlashTest.start())
  {
    Serial.println("FLASH TEST FAILED");
    return;
  }  
  Serial.println("FLASH TEST DONE");  
  
}

void loop() {
  uint8_t buf[128];
  int len = Serial.available();
  if(len > 128)
  {
    len = 128;
  }
  for(uint8_t i=0;i<len;i++)
  {
    buf[i] = Serial.read();
  }
  if(len)
  {
    rs232Test.send(buf, len);
    rs485Test.send(buf, len);
  }
  rs232Test.loop();
  rs485Test.loop();
  canTest.loop();
  ethTest.loop();
  ledButton.loop();
}
