/*
 Name:		Lab3PartA.ino
 Created:	3/24/2016 1:19:30 PM
 Author:	heathpr
*/

#define PIN_LED_1 64
#define PIN_LED_2 65
#define PIN_LED_3 66
#define PIN_LED_4 67
#define PIN_LED_5 68
#define PIN_LED_6 69

#define speed 400


// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(PIN_LED_1, OUTPUT);
	pinMode(PIN_LED_2, OUTPUT);
	pinMode(PIN_LED_3, OUTPUT);
	pinMode(PIN_LED_4, OUTPUT);
	pinMode(PIN_LED_5, OUTPUT);
	pinMode(PIN_LED_6, OUTPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	digitalWrite(PIN_LED_1, HIGH);
	delay(speed);
	digitalWrite(PIN_LED_1, LOW);
	digitalWrite(PIN_LED_2, HIGH);
	delay(speed);
	digitalWrite(PIN_LED_2, LOW);
	digitalWrite(PIN_LED_3, HIGH);
	delay(speed);
	digitalWrite(PIN_LED_3, LOW);
	digitalWrite(PIN_LED_4, HIGH);
	delay(speed);
	digitalWrite(PIN_LED_4, LOW);
	digitalWrite(PIN_LED_5, HIGH);
	delay(speed);
	digitalWrite(PIN_LED_5, LOW);
	digitalWrite(PIN_LED_6, HIGH);
	delay(speed);
	digitalWrite(PIN_LED_6, LOW);
}
