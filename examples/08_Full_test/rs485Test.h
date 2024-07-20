
#ifndef _RS485_TEST_H_
#define _RS485_TEST_H_

#include <Arduino.h>

class Rs485Test {
private:    
  uint8_t rs485DePin = 16;
  uint8_t rs485TxPin = 17;
  uint8_t rs485RxPin = 18;
public:
    Rs485Test(){}
    void setup();
    void send(uint8_t *data, uint16_t len);
    void loop();
};

#endif