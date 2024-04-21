uint8_t rs485DePin = 16;
uint8_t rs485TxPin = 17;
uint8_t rs485RxPin = 18;
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, rs485RxPin, rs485TxPin);
  pinMode(rs485DePin, OUTPUT);
  digitalWrite(rs485DePin, LOW); //read mode
  Serial.println("hello RS485");
}

void loop() {
  uint8_t len;
  len = Serial.available();
  if(len > 0)
  {
    digitalWrite(rs485DePin, HIGH); //write mode
    for(uint8_t i=0;i<len;i++)
    {      
      Serial1.write(Serial.read());
    }
    Serial1.flush(); // wait until the writing is done
    digitalWrite(rs485DePin, LOW); //read mode
  }
  len = Serial1.available();
  if(len > 0)
  {
    for(uint8_t i=0;i<len;i++)
    {
      Serial.write(Serial1.read());
    }
  }
}
