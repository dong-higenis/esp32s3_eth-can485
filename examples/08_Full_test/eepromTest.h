#ifndef _EEPROM_TEST_H_
#define _EEPROM_TEST_H_

#include <Arduino.h>
#include <Wire.h>
#include <I2C_eeprom.h>



// it's only 64Kbit!!!
#define EE24LC64MAXBYTES 65536/8

// the address of your EEPROM
#define DEVICEADDRESS (0x50)

#define TEST_ADDR 16

// this must start on a page boundary!
#define TEST_PAGE_ADDR 0
#define SHORT_BUFFER_LEN 4

// this tests multi-page writes
#define LONG_BUFFER_LEN 64
// make sure it's aligned on a page boundary
#define LONG_TEST_PAGE_ADDR (max(16, TEST_PAGE_ADDR + SHORT_BUFFER_LEN))


// this tests multi-page writes that don't start on a boundary
#define UNALIGNED_BUFFER_LEN 35
#define UNALIGNED_TEST_PAGE_ADDR (LONG_TEST_PAGE_ADDR + LONG_BUFFER_LEN + 5)


#define SERIAL_DEBUG Serial
 

class EepromTest {
private:    
  uint8_t i2c_sda_pin = 48;
  uint8_t i2c_scl_pin = 47;
  I2C_eeprom eeprom;

public:
    EepromTest();

    bool readAndWritePage(unsigned int pageAddress, int bufferLen);
    bool start();
};

#endif