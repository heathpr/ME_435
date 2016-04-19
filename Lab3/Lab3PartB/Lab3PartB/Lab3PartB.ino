/*
 Name:		Lab3PartB.ino
 Created:	3/24/2016 1:33:28 PM
 Author:	heathpr
*/

#define RIGHT_BUTTON 2
#define LEFT_BUTTON 3

#define LED_1 64
#define LED_2 65
#define LED_3 66
#define LED_4 67
#define LED_5 68
#define LED_6 69


// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LEFT_BUTTON, INPUT_PULLUP);
	pinMode(RIGHT_BUTTON, INPUT_PULLUP);

	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	pinMode(LED_4, OUTPUT);
	pinMode(LED_5, OUTPUT);
	pinMode(LED_6, OUTPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (!digitalRead(LEFT_BUTTON)) {
		digitalWrite(LED_1, HIGH);
		digitalWrite(LED_2, HIGH);
		digitalWrite(LED_3, HIGH);
		digitalWrite(LED_4, LOW);
		digitalWrite(LED_5, LOW);
		digitalWrite(LED_6, LOW);
	}
	else if (!digitalRead(RIGHT_BUTTON)) {
		digitalWrite(LED_4, HIGH);
		digitalWrite(LED_5, HIGH);
		digitalWrite(LED_6, HIGH);
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_3, LOW);
	}
	else {
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_3, LOW);
		digitalWrite(LED_4, LOW);
		digitalWrite(LED_5, LOW);
		digitalWrite(LED_6, LOW);
	}
}
