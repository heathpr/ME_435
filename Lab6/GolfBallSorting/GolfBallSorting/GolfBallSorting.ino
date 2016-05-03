/*
 Name:		GolfBallSorting.ino
 Created:	4/29/2016 4:14:07 PM
 Author:	heathpr
*/
#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>
#include <LiquidCrystal.h>
#include <RobotAsciiCom.h>
#include <WildThumperCom.h>
#include <GolfBallStand.h>

#define TEAM_NUMBER 12  // Replace this with your team number.

char manufacturer[] = "Rose-Hulman";
char model[] = "Golf Ball Sorting";  // Change to your app name.
char versionStr[] = "1.0";

// Only Manufacturer, Model, and Version matter to Android
AndroidAccessory acc(manufacturer,
	model,
	"ME435 robot arm message relay station.",
	versionStr,
	"https://sites.google.com/site/me435spring2015/",
	"12345");

byte rxBuf[255];
char txBuf[64];
int batteryVoltageReplyLength = 0;
int wheelCurrentReplyLength = 0;
// Note, when sending commands <b>to</b> Android I don't add the '\n'.
// Turned out to be easier since the whole message arrives together.

// Just a random set of scripts that you might make for testing.
char rightButtonScript[] = "rball3";
char leftButtonScript[] = "rball2";
char selectButtonScript[] = "rball1";

/***  Pin I/O   ***/
#define PIN_RIGHT_BUTTON 2
#define PIN_LEFT_BUTTON 3
#define PIN_SELECT_BUTTON 21

/*** Interrupt flags ***/
volatile int mainEventFlags = 0;
#define FLAG_INTERRUPT_0                   0x0001
#define FLAG_INTERRUPT_1                   0x0002
#define FLAG_INTERRUPT_2                   0x0004
#define FLAG_NEED_TO_SEND_BATTERY_VOLTAGE  0x0008
#define FLAG_NEED_TO_SEND_WHEEL_CURRENT    0x0010

LiquidCrystal lcd(14, 15, 16, 17, 18, 19, 20);
#define LINE_1 0
#define LINE_2 1

RobotAsciiCom robotAsciiCom;
WildThumperCom wildThumperCom(TEAM_NUMBER);

GolfBallStand stand;

#define TIME_OUT 5


int ballColor_1, ballColor_2, ballColor_3;

void setup() {
	Serial.begin(9600);  // Change if you are using a different baudrate.
	pinMode(PIN_LEFT_BUTTON, INPUT_PULLUP);
	pinMode(PIN_RIGHT_BUTTON, INPUT_PULLUP);
	pinMode(PIN_SELECT_BUTTON, INPUT_PULLUP);
	attachInterrupt(0, int0_isr, FALLING);
	attachInterrupt(1, int1_isr, FALLING);
	attachInterrupt(2, int2_isr, FALLING);
	lcd.begin(16, 2);

	// Register callbacks for commands you might receive from Android.
	robotAsciiCom.registerWheelSpeedCallback(wheelSpeedMessageFromAndroid);
	robotAsciiCom.registerPositionCallback(positionMessageFromAndroid);
	robotAsciiCom.registerJointAngleCallback(jointAngleMessageFromAndroid);
	robotAsciiCom.registerGripperCallback(gripperMessageFromAndroid);
	robotAsciiCom.registerAttachSelectedServosCallback(attachSelectedServosCallback);
	robotAsciiCom.registerBatteryVoltageRequestCallback(batteryVoltageRequestFromAndroid);
	robotAsciiCom.registerWheelCurrentRequestCallback(wheelCurrentRequestFromAndroid);
	robotAsciiCom.registerCustomStringCallback(customStringCallbackFromAndroid);

	// Register callbacks for commands you might receive from the Wild Thumper.
	wildThumperCom.registerBatteryVoltageReplyCallback(batteryVoltageReplyFromThumper);
	wildThumperCom.registerWheelCurrentReplyCallback(wheelCurrentReplyFromThumper);

	lcd.clear();
	lcd.print("Relay Station");
	delay(1500);
	acc.powerOn();
}

void wheelSpeedMessageFromAndroid(byte leftMode, byte rightMode, byte leftDutyCycle, byte rightDutyCycle) {
	wildThumperCom.sendWheelSpeed(leftMode, rightMode, leftDutyCycle, rightDutyCycle);
	lcd.clear();
	lcd.print("Wheel speed:");
	lcd.setCursor(0, LINE_2);
	lcd.print("L");
	lcd.print(leftMode);
	lcd.print(" R");
	lcd.print(rightMode);
	lcd.print(" L");
	lcd.print(leftDutyCycle);
	lcd.print(" R");
	lcd.print(rightDutyCycle);
}

void positionMessageFromAndroid(int joint1Angle, int joint2Angle, int joint3Angle, int joint4Angle, int joint5Angle) {
	wildThumperCom.sendPosition(joint1Angle, joint2Angle, joint3Angle, joint4Angle, joint5Angle);
	lcd.clear();
	lcd.print("Position:");
	lcd.setCursor(0, LINE_2);
	lcd.print(joint1Angle);
	lcd.print(" ");
	lcd.print(joint2Angle);
	lcd.print(" ");
	lcd.print(joint3Angle);
	lcd.print(" ");
	lcd.print(joint4Angle);
	lcd.print(" ");
	lcd.print(joint5Angle);
}

void jointAngleMessageFromAndroid(byte jointNumber, int jointAngle) {
	wildThumperCom.sendJointAngle(jointNumber, jointAngle);
	lcd.clear();
	lcd.print("Joint angle:");
	lcd.setCursor(0, LINE_2);
	lcd.print("J");
	lcd.print(jointNumber);
	lcd.print(" move to ");
	lcd.print(jointAngle);
}

void gripperMessageFromAndroid(int gripperDistance) {
	gripperDistance = constrain(gripperDistance, 10, 65);
	wildThumperCom.sendGripperDistance(gripperDistance);
	lcd.clear();
	lcd.print("Gripper:");
	lcd.setCursor(0, LINE_2);
	lcd.print("Gripper to ");
	lcd.print(gripperDistance);
}

void attachSelectedServosCallback(byte servosToEnable) {
	wildThumperCom.sendAttachSelectedServos(servosToEnable);
	lcd.clear();
	lcd.print("Attach:");
	lcd.setCursor(0, LINE_2);
	lcd.print("54321G = ");
	lcd.print(servosToEnable, BIN);
}

void batteryVoltageRequestFromAndroid(void) {
	wildThumperCom.sendBatteryVoltageRequest();
}

void wheelCurrentRequestFromAndroid(void) {
	wildThumperCom.sendWheelCurrentRequest();
}

void customStringCallbackFromAndroid(String customString) {
	lcd.clear();
	if (customString.equalsIgnoreCase("run ball test indoors")) {
		lcd.print("Known CUSTOM");
		// perform that command
		runBallTestIndoors();
	}
	else if (customString.equalsIgnoreCase("run ball test outdoors cloudy"))
	{
		lcd.print("Known CUSTOM");
		// perform that command
		runBallTestOutdoorsCloudy();
	}
	else if (customString.equalsIgnoreCase("run ball test outdoors sunny"))
	{
		lcd.print("Known CUSTOM");
		// perform that command
		runBallTestOutdoorsSunny();
	}
	else {
		lcd.print("Unknown CUSTOM");
	}
	lcd.setCursor(0, LINE_2);
	lcd.print(customString);
}

void batteryVoltageReplyFromThumper(int batteryMillivolts) {
	// Send to Android from within the main event loop.
	mainEventFlags |= FLAG_NEED_TO_SEND_BATTERY_VOLTAGE;
	batteryVoltageReplyLength = robotAsciiCom.prepareBatteryVoltageReply(
		batteryMillivolts, txBuf, sizeof(txBuf));
	// Display battery voltage on LCD.
	lcd.clear();
	lcd.print("Battery voltage:");
	lcd.setCursor(0, LINE_2);
	lcd.print(batteryMillivolts / 1000);
	lcd.print(".");
	if (batteryMillivolts % 1000  < 100) {
		lcd.print("0");
	}
	if (batteryMillivolts % 1000 < 10) {
		lcd.print("0");
	}
	lcd.print(batteryMillivolts % 1000);
}

void wheelCurrentReplyFromThumper(int leftWheelMotorsMilliamps, int rightWheelMotorsMilliamps) {
	// Send to Android from within the main event loop.
	mainEventFlags |= FLAG_NEED_TO_SEND_WHEEL_CURRENT;
	wheelCurrentReplyLength = robotAsciiCom.prepareWheelCurrentReply(
		leftWheelMotorsMilliamps, rightWheelMotorsMilliamps, txBuf, sizeof(txBuf));

	// Display wheel currents on LCD.
	lcd.clear();
	lcd.print("Wheel current:");
	lcd.setCursor(0, LINE_2);
	lcd.print(leftWheelMotorsMilliamps / 1000);
	lcd.print(".");
	if (leftWheelMotorsMilliamps % 1000  < 100) {
		lcd.print("0");
	}
	if (leftWheelMotorsMilliamps % 1000 < 10) {
		lcd.print("0");
	}
	lcd.print(leftWheelMotorsMilliamps % 1000);
	lcd.print("  ");
	lcd.print(rightWheelMotorsMilliamps / 1000);
	lcd.print(".");
	if (rightWheelMotorsMilliamps % 1000  < 100) {
		lcd.print("0");
	}
	if (rightWheelMotorsMilliamps % 1000 < 10) {
		lcd.print("0");
	}
	lcd.print(rightWheelMotorsMilliamps % 1000);
}

bool isValid(int ball1, int ball2, int ball3) {
	// no ball or error
	if (ball1 == BALL_ERROR || ball2 == BALL_ERROR || ball3 == BALL_ERROR) {
		return false;
	}
	if (ball1 == BALL_NONE || ball2 == BALL_NONE || ball3 == BALL_NONE) {
		return false;
	}

	
	// black or white
	if (ball1 == BALL_BLACK) {
		if (ball2 == BALL_BLACK || ball2 == BALL_WHITE) {
			return false;
		}
		else if (ball3 == BALL_BLACK || ball3 == BALL_WHITE) {
			return false;
		}
	}
	else if (ball2 == BALL_BLACK) {
		if (ball1 == BALL_BLACK || ball1 == BALL_WHITE) {
			return false;
		}
		else if (ball3 == BALL_BLACK || ball3 == BALL_WHITE) {
			return false;
		}
	}
	else if (ball3 == BALL_BLACK) {
		if (ball1 == BALL_BLACK || ball1 == BALL_WHITE) {
			return false;
		}
		else if (ball2 == BALL_BLACK || ball2 == BALL_WHITE) {
			return false;
		}
	}
	else if (ball1 == BALL_WHITE) {
		if (ball2 == BALL_BLACK || ball2 == BALL_WHITE) {
			return false;
		}
		else if (ball3 == BALL_BLACK || ball3 == BALL_WHITE) {
			return false;
		}
	}
	else if (ball2 == BALL_WHITE) {
		if (ball1 == BALL_BLACK || ball1 == BALL_WHITE) {
			return false;
		}
		else if (ball3 == BALL_BLACK || ball3 == BALL_WHITE) {
			return false;
		}
	}
	else if (ball3 == BALL_WHITE) {
		if (ball1 == BALL_BLACK || ball1 == BALL_WHITE) {
			return false;
		}
		else if (ball2 == BALL_BLACK || ball2 == BALL_WHITE) {
			return false;
		}
	}
	// red or green
	if (ball1 == BALL_RED) {
		if (ball2 == BALL_RED || ball2 == BALL_GREEN) {
			return false;
		}
		else if (ball3 == BALL_RED || ball3 == BALL_GREEN) {
			return false;
		}
	}
	else if (ball2 == BALL_RED) {
		if (ball1 == BALL_RED || ball1 == BALL_GREEN) {
			return false;
		}
		else if (ball3 == BALL_RED || ball3 == BALL_GREEN) {
			return false;
		}
	}
	else if (ball3 == BALL_RED) {
		if (ball1 == BALL_RED || ball1 == BALL_GREEN) {
			return false;
		}
		else if (ball2 == BALL_RED || ball2 == BALL_GREEN) {
			return false;
		}
	}
	else if (ball1 == BALL_GREEN) {
		if (ball2 == BALL_RED || ball2 == BALL_GREEN) {
			return false;
		}
		else if (ball3 == BALL_RED || ball3 == BALL_GREEN) {
			return false;
		}
	}
	else if (ball2 == BALL_GREEN) {
		if (ball1 == BALL_RED || ball1 == BALL_GREEN) {
			return false;
		}
		else if (ball3 == BALL_RED || ball3 == BALL_GREEN) {
			return false;
		}
	}
	else if (ball3 == BALL_GREEN) {
		if (ball1 == BALL_RED || ball1 == BALL_GREEN) {
			return false;
		}
		else if (ball2 == BALL_RED || ball2 == BALL_GREEN) {
			return false;
		}
	}

	// blue and yellow
	if (ball1 == BALL_YELLOW) {
		if (ball2 == BALL_YELLOW || ball2 == BALL_BLUE) {
			return false;
		}
		else if (ball3 == BALL_YELLOW || ball3 == BALL_BLUE) {
			return false;
		}
	}
	else if (ball2 == BALL_YELLOW) {
		if (ball1 == BALL_YELLOW || ball1 == BALL_BLUE) {
			return false;
		}
		else if (ball3 == BALL_YELLOW || ball3 == BALL_BLUE) {
			return false;
		}
	}
	else if (ball3 == BALL_YELLOW) {
		if (ball1 == BALL_YELLOW || ball1 == BALL_BLUE) {
			return false;
		}
		else if (ball2 == BALL_YELLOW || ball2 == BALL_BLUE) {
			return false;
		}
	}
	else if (ball1 == BALL_BLUE) {
		if (ball2 == BALL_YELLOW || ball2 == BALL_BLUE) {
			return false;
		}
		else if (ball3 == BALL_YELLOW || ball3 == BALL_BLUE) {
			return false;
		}
	}
	else if (ball2 == BALL_BLUE) {
		if (ball1 == BALL_YELLOW || ball1 == BALL_BLUE) {
			return false;
		}
		else if (ball3 == BALL_YELLOW || ball3 == BALL_BLUE) {
			return false;
		}
	}
	else if (ball3 == BALL_BLUE) {
		if (ball1 == BALL_YELLOW || ball1 == BALL_BLUE) {
			return false;
		}
		else if (ball2 == BALL_YELLOW || ball2 == BALL_BLUE) {
			return false;
		}
	}

	return true;
}

void sendBallColors(int ball1, int ball2, int ball3) {
	char *message;
	switch (ball1)
	{
	case(BALL_BLACK):
		message = "1K";
		acc.write(message, sizeof(message));
		break;
	case(BALL_WHITE):
		message = "1W";
		acc.write(message, sizeof(message));
		break;
	case(BALL_BLUE):
		message = "1B";
		acc.write(message, sizeof(message));
		break;
	case(BALL_YELLOW):
		message = "1Y";
		acc.write(message, sizeof(message));
		break;
	case(BALL_RED):
		message = "1R";
		acc.write(message, sizeof(message));
		break;
	case(BALL_GREEN):
		message = "1G";
		acc.write(message, sizeof(message));
		break;
	case(BALL_NONE):
		message = "1N";
		acc.write(message, sizeof(message));
		break;
	default:
		message = "1E";
		acc.write(message, sizeof(message));
		break;
	}
	delay(100);
	switch (ball2)
	{
	case(BALL_BLACK):
		message = "2K";
		acc.write(message, sizeof(message));
		break;
	case(BALL_WHITE):
		message = "2W";
		acc.write(message, sizeof(message));
		break;
	case(BALL_BLUE):
		message = "2B";
		acc.write(message, sizeof(message));
		break;
	case(BALL_YELLOW):
		message = "2Y";
		acc.write(message, sizeof(message));
		break;
	case(BALL_RED):
		message = "2R";
		acc.write(message, sizeof(message));
		break;
	case(BALL_GREEN):
		message = "2G";
		acc.write(message, sizeof(message));
		break;
	case(BALL_NONE):
		message = "2N";
		acc.write(message, sizeof(message));
		break;
	default:
		message = "2E";
		acc.write(message, sizeof(message));
		break;
	}
	delay(100);
	switch (ball3)
	{
	case(BALL_BLACK):
		message = "3K";
		acc.write(message, sizeof(message));
		break;
	case(BALL_WHITE):
		message = "3W";
		acc.write(message, sizeof(message));
		break;
	case(BALL_BLUE):
		message = "3B";
		acc.write(message, sizeof(message));
		break;
	case(BALL_YELLOW):
		message = "3Y";
		acc.write(message, sizeof(message));
		break;
	case(BALL_RED):
		message = "3R";
		acc.write(message, sizeof(message));
		break;
	case(BALL_GREEN):
		message = "3G";
		acc.write(message, sizeof(message));
		break;
	case(BALL_NONE):
		message = "3N";
		acc.write(message, sizeof(message));
		break;
	default:
		message = "3E";
		acc.write(message, sizeof(message));
		break;
	}
	
}


void runBallTestIndoors() {
	bool validCombination = false;
	int count = 1;
	while (!validCombination && count < TIME_OUT) {
		Serial.print("---------------------------------");
		ballColor_1 = stand.determineBallColorIndoors(LOCATION_1);
		Serial.print("  Location 1 ball   = ");
		printBallColor(ballColor_1);
		ballColor_2 = stand.determineBallColorIndoors(LOCATION_2);
		Serial.print("  Location 2 ball   = ");
		printBallColor(ballColor_2);
		ballColor_3 = stand.determineBallColorIndoors(LOCATION_3);
		Serial.print("  Location 3 ball   = ");
		printBallColor(ballColor_3);
		stand.setLedState(LED_GREEN, LOCATION_3, LED_FRONT);
		Serial.print("---------------------------------\n\n");
		count++;
		validCombination = isValid(ballColor_1, ballColor_2, ballColor_3);
	}
	sendBallColors(ballColor_1, ballColor_2, ballColor_3);

}

void runBallTestOutdoorsCloudy() {
	bool validCombination = false;
	int count = 1;
	while (!validCombination && count < TIME_OUT) {
		Serial.print("---------------------------------");
		ballColor_1 = stand.determineBallColorOutdoorsCloudy(LOCATION_1);
		Serial.print("  Location 1 ball   = ");
		printBallColor(ballColor_1);
		ballColor_2 = stand.determineBallColorOutdoorsCloudy(LOCATION_2);
		Serial.print("  Location 2 ball   = ");
		printBallColor(ballColor_2);
		ballColor_3 = stand.determineBallColorOutdoorsCloudy(LOCATION_3);
		Serial.print("  Location 3 ball   = ");
		printBallColor(ballColor_3);
		stand.setLedState(LED_GREEN, LOCATION_3, LED_FRONT);
		Serial.print("---------------------------------\n\n");
		count++;
		validCombination = isValid(ballColor_1, ballColor_2, ballColor_3);
	}
	sendBallColors(ballColor_1, ballColor_2, ballColor_3);

}

void runBallTestOutdoorsSunny() {
	bool validCombination = false;
	int count = 1;
	while (!validCombination && count < TIME_OUT) {
		Serial.print("---------------------------------");
		ballColor_1 = stand.determineBallColorOutdoorsSunny(LOCATION_1);
		Serial.print("  Location 1 ball   = ");
		printBallColor(ballColor_1);
		ballColor_2 = stand.determineBallColorOutdoorsSunny(LOCATION_2);
		Serial.print("  Location 2 ball   = ");
		printBallColor(ballColor_2);
		ballColor_3 = stand.determineBallColorOutdoorsSunny(LOCATION_3);
		Serial.print("  Location 3 ball   = ");
		printBallColor(ballColor_3);
		stand.setLedState(LED_GREEN, LOCATION_3, LED_FRONT);
		Serial.print("---------------------------------\n\n");
		count++;
		validCombination = isValid(ballColor_1, ballColor_2, ballColor_3);
	}
	sendBallColors(ballColor_1, ballColor_2, ballColor_3);

}

void printBallColor(int ballColor) {
	switch (ballColor) {
	case BALL_NONE:
		Serial.println("No ball");
		break;
	case BALL_BLACK:
		Serial.println("Black ball");
		break;
	case BALL_BLUE:
		Serial.println("Blue ball");
		break;
	case BALL_GREEN:
		Serial.println("Green ball");
		break;
	case BALL_RED:
		Serial.println("Red ball");
		break;
	case BALL_YELLOW:
		Serial.println("Yellow ball");
		break;
	case BALL_WHITE:
		Serial.println("White ball");
		break;
	case BALL_ERROR:
		Serial.println("Error");
		break;
	}
}

void loop() {
	// See if there is a new message from Android.
	if (acc.isConnected()) {
		int len = acc.read(rxBuf, sizeof(rxBuf), 1);
		if (len > 0) {
			robotAsciiCom.handleRxBytes(rxBuf, len);
		}
		// Testing sending some scripts to Android on button press instead of a real sensor.
		if (mainEventFlags & FLAG_INTERRUPT_0) {
			delay(20);
			mainEventFlags &= ~FLAG_INTERRUPT_0;
			if (!digitalRead(PIN_RIGHT_BUTTON)) {
				acc.write(rightButtonScript, sizeof(rightButtonScript));
			}
		}
		if (mainEventFlags & FLAG_INTERRUPT_1) {
			delay(20);
			mainEventFlags &= ~FLAG_INTERRUPT_1;
			if (!digitalRead(PIN_LEFT_BUTTON)) {
				acc.write(leftButtonScript, sizeof(leftButtonScript));
			}
		}
		if (mainEventFlags & FLAG_INTERRUPT_2) {
			delay(20);
			mainEventFlags &= ~FLAG_INTERRUPT_2;
			if (!digitalRead(PIN_SELECT_BUTTON)) {
				acc.write(selectButtonScript, sizeof(selectButtonScript));
			}
		}
		// Passing commands from the Wild Thumper on up to Android.
		if (mainEventFlags & FLAG_NEED_TO_SEND_BATTERY_VOLTAGE) {
			mainEventFlags &= ~FLAG_NEED_TO_SEND_BATTERY_VOLTAGE;
			acc.write(txBuf, batteryVoltageReplyLength);
		}
		if (mainEventFlags & FLAG_NEED_TO_SEND_WHEEL_CURRENT) {
			mainEventFlags &= ~FLAG_NEED_TO_SEND_WHEEL_CURRENT;
			acc.write(txBuf, wheelCurrentReplyLength);
		}
	}

	// See if there is a new message from the Wild Thumper.
	if (Serial.available() > 0) {
		wildThumperCom.handleRxByte(Serial.read());
	}
}


void int0_isr() {
	mainEventFlags |= FLAG_INTERRUPT_0;
}

void int1_isr() {
	mainEventFlags |= FLAG_INTERRUPT_1;
}

void int2_isr() {
	mainEventFlags |= FLAG_INTERRUPT_2;
}