
#include "ledButton.h"

LedButtons::LedButtons(){
  this->btnPin = 46;
  this->ledPin = 19;
}
  
void LedButtons::setup() {
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void LedButtons::loop() {
  static bool blink = false;  
  static uint32_t tm = 0;  
  static uint16_t blinkCycleTm = 0;
  if(!digitalRead(btnPin))
  {    
    blinkCycleTm = 100;    
  }
  else
  {
    blinkCycleTm = 1000;
  }
  if(millis() - tm > blinkCycleTm) 
  {
    tm = millis();
    blink = !blink;
  }
  digitalWrite(ledPin, blink);
}
