/*
 Name:		Lab4PartB.ino
 Created:	4/5/2016 12:19:11 PM
 Author:	heathpr
*/

// Include libraries
#include <ArmServos.h>
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

// Dead zone for gripper
#define HIGH_THRESHOLD 900
#define LOW_THRESHOLD 100

// Interupt flags
#define FLAG_INTERRUPT_0 0x01
#define FLAG_INTERRUPT_1 0x02
#define FLAG_INTERRUPT_2 0x04

// limits for each servo angle
#define J1_HIGH 90
#define J1_LOW -90
#define J2_HIGH 180
#define J2_LOW 0
#define J3_HIGH 90
#define J3_LOW -90
#define J4_HIGH 0
#define J4_LOW -180
#define J5_HIGH 180
#define J5_LOW 0
#define GRIPPER_HIGH 71
#define GRIPPER_LOW 0

// create LCD object
LiquidCrystal lcd = LiquidCrystal(14, 15, 16, 17, 18, 19, 20);
ArmServos robotArm;


// create protoypes of functions
int updateValue(int,int,int);
void updateDisplay(void);
void int0_isr(void);
void int1_isr(void);
void updateLED(void);
void updateServoPositions(void);


// create global variables
int horz;
int vert;
int joint1 = (J1_HIGH+J1_LOW)/2;
int joint2 = (J2_HIGH + J2_LOW) / 2;
int joint3 = (J3_HIGH + J3_LOW) / 2;
int joint4 = (J4_HIGH + J4_LOW) / 2;
int joint5 = (J5_HIGH + J5_LOW) / 2;
int gripper = (GRIPPER_HIGH + GRIPPER_LOW) / 2;
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
	robotArm.attach();

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

	// reset joints
	if (!digitalRead(SELECT_BUTTON)) {
		switch (activeJoint)
		{
		case 1:
			joint1 = (J1_HIGH + J1_LOW) / 2;
			break;
		case 2:
			joint2 = (J2_HIGH + J2_LOW) / 2;
			break;
		case 3:
			joint3 = (J3_HIGH + J3_LOW) / 2;
			break;
		case 4:
			joint4 = (J4_HIGH + J4_LOW) / 2;
			break;
		case 5:
			joint5 = (J5_HIGH + J5_LOW) / 2;
			break;
		case 6:
			gripper = (GRIPPER_HIGH + GRIPPER_LOW) / 2;
			break;
		}
		updateDisplay();
	}
	switch (activeJoint)
	{
	case 1:
		joint1 = updateValue(joint1,J1_HIGH,J1_LOW);
		break;
	case 2:
		joint2 = updateValue(joint2,J2_HIGH,J2_LOW);
		break;
	case 3:
		joint3 = updateValue(joint3,J3_HIGH,J3_LOW);
		break;
	case 4:
		joint4 = updateValue(joint4,J4_HIGH,J4_LOW);
		break;
	case 5:
		joint5 = updateValue(joint5,J5_HIGH,J5_LOW);
		break;
	case 6:
		gripper = updateValue(gripper,GRIPPER_HIGH,GRIPPER_LOW);
		break;
	}
	updateDisplay();
	updateServoPositions();

}

int updateValue(int angle,int high, int low) {
	vert = analogRead(VERT_ANALOG);
	horz = analogRead(HORZ_ANALOG);
	if (vert >= HIGH_THRESHOLD) {
		if (angle < high) {
			angle = angle + 4;
		}
		else {
			angle = high;
		}
	}
	else if (vert <= LOW_THRESHOLD) {
		if (angle > low) {
			angle = angle - 4;
		}
		else {
			angle = low;
		}
	}
	else if (horz >= HIGH_THRESHOLD) {
		if (angle < high) {
			angle = angle + 1;
		}
		else {
			angle = high;
		}
	}
	else if (horz <= LOW_THRESHOLD) {
		if (angle > low) {
			angle = angle - 1;
		}
		else {
			angle =low;
		}
	}
	delay(100);
	return angle;
}

void updateDisplay() {
	lcd.setCursor(1, 0);
	lcd.print(joint1);
	lcd.print(" ");

	lcd.setCursor(6, 0);
	lcd.print(joint2);
	lcd.print(" ");

	lcd.setCursor(11, 0);
	lcd.print(joint3);
	lcd.print(" ");

	lcd.setCursor(1, 1);
	lcd.print(joint4);
	lcd.print(" ");

	lcd.setCursor(6, 1);
	lcd.print(joint5);
	lcd.print(" ");

	lcd.setCursor(11, 1);
	lcd.print(gripper);
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
	robotArm.setPosition(joint1, joint2, joint3, joint4, joint5);
	robotArm.setGripperDistance(gripper);
}
