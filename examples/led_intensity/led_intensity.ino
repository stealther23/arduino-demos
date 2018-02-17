void setup() {
  // setup pin for the led
  pinMode(11, OUTPUT);
}

void loop() {
  // modify intensity of the led
  for (int i = 0; i< 255; i++) {
    analogWrite(11, i);
    delay(50);
  }

  for (int i = 255; i > 0; i--) {
    analogWrite(11, i);
    delay(50);
  }
}
