
#ifndef _RS232_TEST_H_
#define _RS232_TEST_H_

#include <Arduino.h>

class Rs232Test {
private:    
  uint8_t rs232TxPin = 4;
  uint8_t rs232RxPin = 5;
public:
    Rs232Test(){}
    void setup();
    void send(uint8_t *data, uint16_t len);
    void loop();
};

#endif