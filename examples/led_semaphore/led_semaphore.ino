int LED_RED = 11;
int LED_YELLOW = 12;
int LED_GREEN = 13;

void setup() {
  // set up the pins
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(LED_GREEN, HIGH);
  delay(1000);
  digitalWrite(LED_YELLOW, HIGH);
  delay(200);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, HIGH);
  delay(1000);
  digitalWrite(LED_YELLOW, HIGH);
  delay(200);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, HIGH);
  delay(1000);
}
