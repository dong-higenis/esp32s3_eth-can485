#ifndef _LED_BUTTON_H_
#define _LED_BUTTON_H_

#include <Arduino.h>

class LedButtons {
private:    
  uint8_t btnPin;
  uint8_t ledPin;

public:
    LedButtons();

    void setup();
    void loop();
};

#endif