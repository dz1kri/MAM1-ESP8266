#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  // Additional setup code
}

void loop() {
  lcd.setCursor(3, 0);
  lcd.print("Hello, World!");
  delay(1000);

  lcd.setCursor(2, 1);
  lcd.print("THANKS");
  delay(800);

  lcd.clear();
  // Additional LCD control code
}
