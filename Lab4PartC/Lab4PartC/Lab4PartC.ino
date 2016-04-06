/*
 Name:		Lab4PartC.ino
 Created:	4/5/2016 12:47:31 PM
 Author:	heathpr
*/

// Include Libraries
#include <Servo.h>
#include <ArmServos.h>
#include <RobotAsciiCom.h>
#include <LiquidCrystal.h>

// Construct an instance of the class
ArmServos armServos;
RobotAsciiCom robotCom;
LiquidCrystal lcd = LiquidCrystal(14, 15, 16, 17, 18, 19, 20);


void setup() {
	Serial.begin(9600);  // Any speed is ok
						 // Register functions to be called when that command is received.
	robotCom.registerPositionCallback(positionCallback);
	robotCom.registerJointAngleCallback(jointAngleCallback);
	robotCom.registerGripperCallback(gripperCallback);

	// Set up robot arm
	armServos.attach();

	// begin LCD
	lcd.begin(16, 2);
	lcd.clear();
}

void positionCallback(int joint1Angle, int joint2Angle, int joint3Angle, int joint4Angle, int joint5Angle) {
	armServos.setPosition(joint1Angle, joint2Angle, joint3Angle, joint4Angle, joint5Angle);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("position recieved");
	armServos.setPosition(joint1Angle, joint2Angle, joint3Angle, joint4Angle, joint5Angle);
}

void jointAngleCallback(byte jointNumber, int jointAngle) {
	armServos.setJointAngle(jointNumber, jointAngle);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("joint recieved");
	armServos.setJointAngle(jointNumber, jointAngle);
}

void gripperCallback(int gripperDistance) {
	armServos.setGripperDistance(gripperDistance);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("gripper recieved");
	armServos.setGripperDistance(gripperDistance);
}

void loop() {
}


/** Send all bytes received to the Wild Thumper Com object. */
void serialEvent() {
	while (Serial.available()) {
		robotCom.handleRxByte(Serial.read());
	}
}