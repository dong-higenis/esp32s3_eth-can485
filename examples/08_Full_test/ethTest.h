
#ifndef _ETH_TEST_H_
#define _ETH_TEST_H_

#include <Arduino.h>

#include <ETHClass.h>       //Is to use the modified ETHClass
#include <SPI.h>
#include <SD.h>
#include <AsyncUDP.h>

#define ETH_MISO_PIN                    11
#define ETH_MOSI_PIN                    12
#define ETH_SCLK_PIN                    10
#define ETH_CS_PIN                      9
#define ETH_INT_PIN                     13
#define ETH_RST_PIN                     14



class EthTest {
private:    
  AsyncUDP udp;
  const uint16_t udpPort = 1234;
  bool eth_connected = false;
  static EthTest* instance;

public:
    EthTest() {
      instance = this;
    }
    void setup();
    void loop();
    static void onEthEvent(WiFiEvent_t event);
};

#endif