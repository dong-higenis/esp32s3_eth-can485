#include "rs485Test.h"

void Rs485Test::setup()
{
  Serial1.begin(115200, SERIAL_8N1, rs485RxPin, rs485TxPin);
  pinMode(rs485DePin, OUTPUT);
  digitalWrite(rs485DePin, LOW); //read mode
}

void Rs485Test::send(uint8_t *data, uint16_t len)
{
  digitalWrite(rs485DePin, HIGH); //write mode
  Serial1.write(data, len);
  Serial1.flush(); // wait until the writing is done
  digitalWrite(rs485DePin, LOW); //read mode
}


void Rs485Test::loop()
{ 
  uint8_t len = Serial1.available();
  if(len > 0)
  {
    for(uint8_t i=0;i<len;i++)
    {
      Serial.write(Serial1.read());
    }
  }
}
