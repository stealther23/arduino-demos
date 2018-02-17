#include <LiquidCrystal.h>
#include "IRremote.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int RECV_PIN = 11;
int LED_BLUE = 13;
int LED_RED = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop() {
  // write at the beginning of lcd
  lcd.setCursor(0, 0);

  // watch IR sensor input
  /* you can use any codes you want to,
   these are just the codes i used that worked 
  for my remote */
  if (irrecv.decode(&results)) {
    lcd.clear();
    switch (results.value) {
      case 16728765:
        lcd.print("K7: blue ON");
        digitalWrite(LED_BLUE, HIGH);
        break;
      case 16730805:
        lcd.print("K8: blue OFF");
        digitalWrite(LED_BLUE, LOW);
        break;
      case 16724175:
        lcd.print("K1: red ON");
        digitalWrite(LED_RED, HIGH);
        break;
      case 16718055:
        lcd.print("K2: red OFF");
        digitalWrite(LED_RED, LOW);
        break;
    }
    lcd.setCursor(0, 1); // go to line 2
    lcd.print(results.value); // print IR code
    irrecv.resume(); // Receive the next IR value
  }
  
}
