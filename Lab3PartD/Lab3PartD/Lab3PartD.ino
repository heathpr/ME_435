/*
Name:		Lab3PartD.ino
Created:	3/24/2016 1:44:10 PM
Author:	heathpr
*/

// Include header files
#include <LiquidCrystal.h>

// Global constants
#define PIN_RIGHT_BUTTON 2
#define PIN_LEFT_BUTTON 3

// Glodal variables
String name = "Peter Heath";
LiquidCrystal lcd(14, 15, 16, 17, 18, 19, 20);
int age = 22;

// Prototypes of functions
void int0_isr(void);
void int1_isr(void);

// the setup function runs once when you press reset or power the board
void setup() {
	int size;
	
	pinMode(PIN_LEFT_BUTTON, INPUT_PULLUP);
	pinMode(PIN_RIGHT_BUTTON, INPUT_PULLUP);

	Serial.begin(9600);
	lcd.begin(16, 2);
	lcd.setCursor(0, 0);
	size = name.length()+1;
	//Serial.println(size);
	lcd.print(name);
	lcd.setCursor(size, 0);
	lcd.print("is");

	attachInterrupt(0, int0_isr, FALLING);
	attachInterrupt(1, int1_isr, FALLING);

}

// the loop function runs over and over again until power down or reset
void loop() {
	
	lcd.setCursor(4, 1);
	lcd.print(age);
	lcd.print(" ");
}

void int0_isr() {
	age++;
}
void int1_isr() {
	age--;
}
