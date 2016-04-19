/*
 Name:		Lab4PartA.ino
 Created:	3/31/2016 1:53:44 PM
 Author:	heathpr
*/


#include <servo.h>
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
#define HIGH_THRESHOLD 900
#define LOW_THRESHOLD 100
#define FLAG_INTERRUPT_0 0x01
#define FLAG_INTERRUPT_1 0x02
#define FLAG_INTERRUPT_2 0x04



// create LCD object
LiquidCrystal lcd = LiquidCrystal(14, 15, 16, 17, 18, 19, 20);
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;
Servo servo_gripper;


// create protoypes of functions
int updateValue(int);
void updateDisplay(void);
void int0_isr(void);
void int1_isr(void);
void updateLED(void);
void updateServoPositions(void);


// create global variables
int horz;
int vert;
int servo1 = 90;
int servo2 = 90;
int servo3 = 90;
int servo4 = 90;
int servo5 = 90;
int servo6 = 90;
int activeJoint = 1;
volatile int mainEventFlags = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	// start Serial for debugging
	Serial.begin(9600);

	// Setup pins
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);
	pinMode(LED_4, OUTPUT);
	pinMode(LED_5, OUTPUT);
	pinMode(LED_6, OUTPUT);
	pinMode(RIGHT_BUTTON, INPUT_PULLUP);
	pinMode(LEFT_BUTTON, INPUT_PULLUP);
	pinMode(SELECT_BUTTON, INPUT_PULLUP);

	// Setup Servo pins
	servo_1.attach(12);
	servo_2.attach(11);
	servo_3.attach(10);
	servo_4.attach(9);
	servo_5.attach(8);
	servo_gripper.attach(6);

	// begin LCD
	lcd.begin(16, 2);

	// Set up interupts
	attachInterrupt(0, int0_isr, FALLING);
	attachInterrupt(1, int1_isr, FALLING);

	// set initial stuff
	updateDisplay();
	updateLED();
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (mainEventFlags & FLAG_INTERRUPT_0) {
		delay(20);
		mainEventFlags &= ~FLAG_INTERRUPT_0;
		if (!digitalRead(RIGHT_BUTTON)) {
			if (activeJoint < 6) {
				activeJoint++;
			}
			else {
				activeJoint = 1;
			}
			updateLED();
			//Serial.println(activeJoint);
		}
	}
	if (mainEventFlags & FLAG_INTERRUPT_1) {
		delay(20);
		mainEventFlags &= ~FLAG_INTERRUPT_1;
		if (!digitalRead(LEFT_BUTTON)) {
			if (activeJoint > 1) {
				activeJoint--;
			}
			else {
				activeJoint = 6;
			}
			updateLED();
			//	Serial.println(activeJoint);
		}
	}
	if (!digitalRead(SELECT_BUTTON)) {
		switch (activeJoint)
		{
		case 1:
			servo1 = 90;
			break;
		case 2:
			servo2 = 90;
			break;
		case 3:
			servo3 = 90;
			break;
		case 4:
			servo4 = 90;
			break;
		case 5:
			servo5 = 90;
			break;
		case 6:
			servo6 = 90;
			break;
		}
		updateDisplay();
	}
	switch (activeJoint)
	{
	case 1:
		servo1 = updateValue(servo1);
		break;
	case 2:
		servo2 = updateValue(servo2);
		break;
	case 3:
		servo3 = updateValue(servo3);
		break;
	case 4:
		servo4 = updateValue(servo4);
		break;
	case 5:
		servo5 = updateValue(servo5);
		break;
	case 6:
		servo6 = updateValue(servo6);
		break;
	}
	updateDisplay();
	updateServoPositions();

}

int updateValue(int angle) {
	vert = analogRead(VERT_ANALOG);
	horz = analogRead(HORZ_ANALOG);
	if (vert >= HIGH_THRESHOLD) {
		if (angle < 180) {
			angle = angle + 4;
		}
		else {
			angle = 180;
		}
	}
	else if (vert <= LOW_THRESHOLD) {
		if (angle > 0) {
			angle = angle - 4;
		}
		else {
			angle = 0;
		}
	}
	else if (horz >= HIGH_THRESHOLD) {
		if (angle < 180) {
			angle = angle + 1;
		}
		else {
			angle = 180;
		}
	}
	else if (horz <= LOW_THRESHOLD) {
		if (angle > 0) {
			angle = angle - 1;
		}
		else {
			angle = 0;
		}
	}
	delay(100);
	return angle;
}

void updateDisplay() {
	lcd.setCursor(1, 0);
	lcd.print(servo1);
	lcd.print(" ");

	lcd.setCursor(6, 0);
	lcd.print(servo2);
	lcd.print(" ");

	lcd.setCursor(11, 0);
	lcd.print(servo3);
	lcd.print(" ");

	lcd.setCursor(1, 1);
	lcd.print(servo4);
	lcd.print(" ");

	lcd.setCursor(6, 1);
	lcd.print(servo5);
	lcd.print(" ");

	lcd.setCursor(11, 1);
	lcd.print(servo6);
	lcd.print(" ");

}

void int0_isr() {
	mainEventFlags |= FLAG_INTERRUPT_0;
}

void int1_isr() {
	mainEventFlags |= FLAG_INTERRUPT_1;
}

void updateLED(void) {
	switch (activeJoint)
	{
	case 1:
		digitalWrite(LED_1, HIGH);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_3, LOW);
		digitalWrite(LED_4, LOW);
		digitalWrite(LED_5, LOW);
		digitalWrite(LED_6, LOW);
		break;
	case 2:
		digitalWrite(LED_2, HIGH);
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_3, LOW);
		digitalWrite(LED_4, LOW);
		digitalWrite(LED_5, LOW);
		digitalWrite(LED_6, LOW);
		break;
	case 3:
		digitalWrite(LED_3, HIGH);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_4, LOW);
		digitalWrite(LED_5, LOW);
		digitalWrite(LED_6, LOW);
		break;
	case 4:
		digitalWrite(LED_4, HIGH);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_3, LOW);
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_5, LOW);
		digitalWrite(LED_6, LOW);
		break;
	case 5:
		digitalWrite(LED_5, HIGH);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_3, LOW);
		digitalWrite(LED_4, LOW);
		digitalWrite(LED_1, LOW);
		digitalWrite(LED_6, LOW);
		break;
	case 6:
		digitalWrite(LED_6, HIGH);
		digitalWrite(LED_2, LOW);
		digitalWrite(LED_3, LOW);
		digitalWrite(LED_4, LOW);
		digitalWrite(LED_5, LOW);
		digitalWrite(LED_1, LOW);
		break;
	default:
		// do nothing
		break;
	}
}

void updateServoPositions(void) {
	servo_1.write(servo1);
	servo_2.write(servo2);
	servo_3.write(servo3);
	servo_4.write(servo4);
	servo_5.write(servo5);
	servo_gripper.write(servo6);
}
