#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int voltageV = A0;

void setup() {
  pinMode (voltageV, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int VoltageMsmt = analogRead(voltageV);
  float Vcalc = (5.0/1023) * VoltageMsmt;
  lcd.setCursor(0,0);
  lcd.print("BATT ");
  lcd.print(Vcalc);
  lcd.print(" V");
  delay(500);
}