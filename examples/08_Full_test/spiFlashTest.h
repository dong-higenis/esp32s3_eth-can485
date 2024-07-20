#ifndef _SPI_FLASH_TEST_H_
#define _SPI_FLASH_TEST_H_

#include <Arduino.h>
#include <SerialFlash.h>
#include <SPI.h>

#define FSPI_MISO 39
#define FSPI_MOSI 38
#define FSPI_SCLK 37
#define FSPI_CS   36

class SpiFlashTest {
private:    
  static const int spiClk = 240000000; // 1 MHz
  SPIClass * fspi = NULL;
  const int FlashChipSelect = 4; 

public:
    SpiFlashTest(){}
    bool start();
};

#endif