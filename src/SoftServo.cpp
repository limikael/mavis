#include "SoftServo.h"

SoftServo::SoftServo(int motorAPin, int motorBPin, int encAPin, int encBPin)
		:_rotEnc(encAPin,encBPin) {
	_target=0;
	_motorAPin=motorAPin;
	_motorBPin=motorBPin;
	_duty=255;
	_tolerance=0;
	_lastVal=0;

	pinMode(_motorAPin,OUTPUT);
	pinMode(_motorBPin,OUTPUT);
}

void SoftServo::setTarget(int target) {
	_target=target;
}

void SoftServo::setTolerance(int tolerance) {
	_tolerance=tolerance;
}

void SoftServo::setDuty(int duty) {
	_duty=duty;
}

void SoftServo::loop() {
	int v=_rotEnc.getValue();

	if (v!=_lastVal) {
		Serial.println(String("Servo enc: ")+v);
		_lastVal=v;
	}

	if (v<_target-_tolerance) {
		analogWrite(_motorAPin,_duty);
		analogWrite(_motorBPin,0);
	}

	else if (v>_target+_tolerance) {
		analogWrite(_motorAPin,0);
		analogWrite(_motorBPin,_duty);
	}

	else {
		analogWrite(_motorAPin,0);
		analogWrite(_motorBPin,0);
	}
}