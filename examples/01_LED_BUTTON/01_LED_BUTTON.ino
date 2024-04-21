uint8_t btnPin = 46;
uint8_t ledPin = 19;

void setup() {
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  digitalWrite(ledPin, digitalRead(btnPin));
}
