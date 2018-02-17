void setup() {
  // set up on pin 7
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {

  // detect button state
  int buttonState = digitalRead(7);
  Serial.println(buttonState);
  delay(10);
}
