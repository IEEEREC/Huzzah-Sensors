#include <LiquidCrystal_I2C.h>

/*
 * Connection Map
 * 
 * SCL - SCL
 * SDA - SDA
 * VCC - USB (yes, it's 5v, but the I2C on the 3.3v ESP8266 does not complain)
 * Gnd - Gnd
 */
#include <Wire.h>

 
 
 
// Construct an LCD object and pass it the
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() {
 
 
  lcd.init();
 
  // Turn on the backlight.
  lcd.backlight();
 
  // Move the cursor 5 characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(5, 0);
 
  // Print HELLO to the screen, starting at 5,0.
  lcd.print("HELLO");
 
  // Move the cursor to the next line and print
  // WORLD.
  lcd.setCursor(5, 1);      
  lcd.print("WORLD");
}
 
void loop() {
}
