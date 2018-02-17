#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // write to your lcd
  lcd.setCursor(0, 0);
  lcd.print("yes, i am pretty awesome!");

  // move around the screen
  for (int i = 0; i < 8; i++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayRight();
    delay(200);
  }
  for (int i = 0; i < 8; i++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }

  delay(1000);
  
}
