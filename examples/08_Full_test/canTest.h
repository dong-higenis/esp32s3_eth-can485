
#ifndef _CAN_TEST_H_
#define _CAN_TEST_H_

/*
https://github.com/halfroad/TWAIMessager

The Can Bus (a.k.a Two-Wire Automobile Interface, TWAI on ESP32) Sender, Receiver,Serial Writer on EPS32 S3.
*/

#include <Arduino.h>
#include <driver/twai.h>

// for ESP32S3-ETH_CAN485 Board
#define RX_GPIO_PIN               GPIO_NUM_42
#define TX_GPIO_PIN               GPIO_NUM_41
#define CAN_EN_PIN                40


class CanTest {
private:    
  bool driver_installed = false;
  const uint32_t DEFULT_INTERVAL = 500;
public:
    CanTest(){}
    void setup();
    //void send(uint8_t *data, uint16_t len);
    void loop();
};

#endif