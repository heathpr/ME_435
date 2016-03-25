/*
 Name:		Lab3PartG.ino
 Created:	3/25/2016 12:24:34 PM
 Author:	heathpr
*/

#include <LiquidCrystal.h>

/***  Pin I/O   ***/
#define LED_1 64
#define LED_2 65
#define LED_3 66
#define LED_4 67
#define LED_5 68
#define LED_6 69
#define RIGHT_BUTTON 2
#define LEFT_BUTTON 3
#define SELECT_BUTTON 21
#define CONTRAST_ANALOG 8
#define HORZ_ANALOG 0
#define VERT_ANALOG 1


// create LCD object
LiquidCrystal lcd = LiquidCrystal(14, 15, 16, 17, 18, 19, 20);


// create global variables
int horz;
int vert;

// the setup function runs once when you press reset or power the board
void setup() {
	lcd.begin(16, 2);
	pinMode(LEFT_BUTTON, INPUT_PULLUP);
	pinMode(RIGHT_BUTTON, INPUT_PULLUP);
	pinMode(SELECT_BUTTON, INPUT_PULLUP);

}

// the loop function runs over and over again until power down or reset
void loop() {
	horz = analogRead(HORZ_ANALOG);
	vert = analogRead(VERT_ANALOG);

	String horzS = String(horz);
	int hSize = horzS.length();

	String vertS = String(vert);
	int vSize = vertS.length();
	
	lcd.setCursor(0, 0);
	lcd.print("Horz = ");
	lcd.setCursor(7, 0);
	lcd.print(horz);
	lcd.setCursor(7 + hSize, 0);
	lcd.print("  ");
	
	lcd.setCursor(0, 1);
	lcd.print("Vert = ");
	lcd.setCursor(7, 1);
	lcd.print(vert);
	lcd.setCursor(7 + vSize, 1);
	lcd.print("  ");

	if (!digitalRead(SELECT_BUTTON)) {
		digitalWrite(LED_2, HIGH);
		delay(100);
	}
	else {
		digitalWrite(LED_2, LOW);
	}

	if (!digitalRead(LEFT_BUTTON)) {
		digitalWrite(LED_4, HIGH);
		delay(100);
	}
	else {
		digitalWrite(LED_4, LOW);
	}

	if (!digitalRead(RIGHT_BUTTON)) {
		digitalWrite(LED_6, HIGH);
		delay(100);
	}
	else {
		digitalWrite(LED_6, LOW);
	}

}
