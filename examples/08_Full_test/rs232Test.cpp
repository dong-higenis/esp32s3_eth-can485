#include "rs232Test.h"

void Rs232Test::setup()
{
  Serial2.begin(115200, SERIAL_8N1, rs232RxPin, rs232TxPin);
}

void Rs232Test::send(uint8_t *data, uint16_t len)
{
  Serial2.write(data, len);
}

void Rs232Test::loop()
{ 
  uint8_t len = Serial2.available();
  if(len > 0)
  {
    for(uint8_t i=0;i<len;i++)
    {
      Serial.write(Serial2.read());
    }
  }
}
