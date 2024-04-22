uint8_t rs232TxPin = 4;
uint8_t rs232RxPin = 5;
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, rs232RxPin, rs232TxPin);

  Serial.println("hello RS232");
}

void loop() {
  uint8_t len;
  len = Serial.available();
  if(len > 0)
  {
    for(uint8_t i=0;i<len;i++)
    {
      Serial2.write(Serial.read());
    }
  }
  len = Serial2.available();
  if(len > 0)
  {
    for(uint8_t i=0;i<len;i++)
    {
      Serial.write(Serial2.read());
    }
  }
}
