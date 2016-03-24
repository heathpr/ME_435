/*
 Name:		Lab3PartC.ino
 Created:	3/24/2016 1:44:10 PM
 Author:	heathpr
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(14, 15, 16, 17, 18, 19, 20);

// the setup function runs once when you press reset or power the board
void setup() {
	lcd.begin(16, 2);
	//lcd.print("hello, world!");
	lcd.setCursor(0, 0);
	lcd.print("Rose");
	lcd.setCursor(10, 0);
	lcd.print("Hulman");
	lcd.setCursor(0, 1);
	lcd.print("Peter");
	lcd.setCursor(9, 1);
	lcd.print("Spencer");
}

// the loop function runs over and over again until power down or reset
void loop() {
	// lcd.setCursor(column, line);
	// Set the cursor to column 0, line 1
	// If line = 1 that’s the second row, since counting begins with 0
	
	// print the number of seconds since reset:
	//lcd.print(millis() / 1000);

}
