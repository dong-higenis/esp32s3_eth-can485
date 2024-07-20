#include "eepromTest.h"

bool EepromTest::readAndWritePage(unsigned int pageAddress, int bufferLen) {
    byte testBuffer[LONG_BUFFER_LEN + 1];
    byte readTestBuffer[LONG_BUFFER_LEN + 1];

    testBuffer[bufferLen] = '\0';
    readTestBuffer[bufferLen] = '\0';

    eeprom.readBlock(pageAddress, testBuffer, bufferLen);


    for (int i = 0; i < bufferLen; i++) {
      readTestBuffer[i] = 0;
      // use max to init to all AAAA's on first run.
      testBuffer[i] = 'A';
      char c = (testBuffer[i] + ((i % 4) + 1) % 'z');
      if (testBuffer[i] < c) testBuffer[i] = c;
    }

    eeprom.writeBlock(pageAddress, testBuffer, bufferLen);
    delay(10);

    eeprom.readBlock(pageAddress, readTestBuffer, bufferLen);
    bool compare = true;
    for(int i=0;i<bufferLen;i++)
    {
      if(readTestBuffer[i] != testBuffer[i])
      {
        compare = false;
        break;
      }
    }
    if(!compare)
    {
      Serial.println("\tRead Failed");;
    }
    else
    {
      Serial.println("\tRead/Write OK");;
    }
    return compare;
}

EepromTest::EepromTest():
  eeprom(DEVICEADDRESS, EE24LC64MAXBYTES)
{  
}

bool EepromTest::start()
{
  Wire.begin(i2c_sda_pin, i2c_scl_pin);
  eeprom.begin();  
  return readAndWritePage(TEST_PAGE_ADDR, LONG_BUFFER_LEN);
}