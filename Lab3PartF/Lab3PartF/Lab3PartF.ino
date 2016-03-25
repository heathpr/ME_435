/*
 Name:		Lab3PartF.ino
 Created:	3/25/2016 12:13:08 PM
 Author:	heathpr
*/

// Include header files
#include <LiquidCrystal.h>

// Global constants
#define PIN_RIGHT_BUTTON 2
#define PIN_LEFT_BUTTON 3
#define PIN_CONTRAST_ANALOG 8
#define LINE_1 0
#define LINE_2 1


// Glodal variables
LiquidCrystal lcd(14, 15, 16, 17, 18, 19, 20);
int analogReading;

// the setup function runs once when you press reset or power the board
void setup() {
	lcd.begin(16, 2);
}

// the loop function runs over and over again until power down or reset
void loop() {
	analogReading = analogRead(PIN_CONTRAST_ANALOG);
	lcd.setCursor(0, LINE_1);
	lcd.print("Reading = ");
	lcd.print(analogReading);
	lcd.print("  ");
	lcd.setCursor(0, LINE_2);
	lcd.print("Voltage = ");
	lcd.print((float)analogReading / 1023.0 * 5.0);
	lcd.print("  ");
}
