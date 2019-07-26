#include "SoftServo.h"
#include <stdio.h>

SoftServo::SoftServo(int motorAPin, int motorBPin, int encAPin, int encBPin)
		:_rotEnc(encAPin,encBPin) {
	_target=0;
	_motorAPin=motorAPin;
	_motorBPin=motorBPin;
	_minDuty=0;
	_maxDuty=255;
	_tolerance=0;
	_lastVal=0;
	_ramp=0;

	pinMode(_motorAPin,OUTPUT);
	pinMode(_motorBPin,OUTPUT);
}

void SoftServo::setTarget(int target) {
	_target=target;
}

void SoftServo::setTolerance(int tolerance) {
	_tolerance=tolerance;
}

void SoftServo::setMinDuty(int minDuty) {
	_minDuty=minDuty;
}

void SoftServo::setMaxDuty(int maxDuty) {
	_maxDuty=maxDuty;
}

void SoftServo::setRamp(int ramp) {
	_ramp=ramp;
}

void SoftServo::_setDuties(int aDuty, int bDuty) {
	analogWrite(_motorAPin,aDuty);
	analogWrite(_motorBPin,bDuty);
}

void SoftServo::loop() {
	int v=_rotEnc.getValue();

	if (v!=_lastVal) {
		//Serial.println(String("Servo enc: ")+v);
		_lastVal=v;
	}

	if (v<_target-_tolerance-_ramp)
		_setDuties(_maxDuty,0);

	else if (v<_target-_tolerance)
		_setDuties(_minDuty+(_target-_tolerance-v)*(_maxDuty-_minDuty)/_ramp,0);

	else if (v>_target+_tolerance+_ramp)
		_setDuties(0,_maxDuty);

	else if (v>_target+_tolerance)
		_setDuties(0,_minDuty+(v-_target-_tolerance)*(_maxDuty-_minDuty)/_ramp);

	else
		_setDuties(0,0);
}