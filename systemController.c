/*

Source Code for coin thickness measuring system

*/

#include <Servo.h>

#include <CapacitiveSensor.h>

#include <LiquidCrystal.h>

CapacitiveSensor capSensor = CapacitiveSensor(4,2);

LiquidCrystal lcd(13,11,5,8,3,7);

Servo servoMain;

int threshold = 70;

int switchState = 0;

bool start = false;

const float initialPos = 90;

float pos = initialPos;

int steps = 0;

void setup() {

	servoMain.attach(10);

	lcd.begin(16,2);

	lcd.print("press button");

	pinMode(12,INPUT);

	pinMode(13,OUTPUT);

	Serial.begin(2400);

}

void loop() {

	long sensorValue = capSensor.capacitiveSensor(30);

	switchState = digitalRead(12);

	Serial.print(digitalRead(12));

	if (switchState == 1){

		steps = 0;

		start = true;

	}

	if(start){

		if (sensorValue > threshold){

			lcd.print(" Done");

			start = false;

		}

		servoMain.write(pos);

		pos -=1;

		steps += 1;

		if (pos == 0){

			pos = initialPos;

		}

		lcd.clear();

		lcd.print(steps);

		delay(1000);

	}

delay (10);

}