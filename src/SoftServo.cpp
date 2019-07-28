#include "SoftServo.h"
#include <stdio.h>

SoftServo::SoftServo(int motorAPin, int motorBPin, int encAPin, int encBPin)
		:_rotEnc(encAPin,encBPin) {
	_target=0;
	_motorAPin=motorAPin;
	_motorBPin=motorBPin;
	_lastVal=0;
	_lastDir=0;
	_minDuty=0;
	_maxDuty=255;
	_ramp=100;

	pinMode(_motorAPin,OUTPUT);
	pinMode(_motorBPin,OUTPUT);
}

void SoftServo::setTarget(int target) {
	_target=target;
	_osc=0;
	_lastDir=0;
}

void SoftServo::_setDuty(int duty) {
	if (duty>0) {
		analogWrite(_motorAPin,duty);
		analogWrite(_motorBPin,0);
	}

	else {
		analogWrite(_motorAPin,0);
		analogWrite(_motorBPin,-duty);
	}
}

void SoftServo::setRamp(int ramp) {
	_ramp=ramp;
}

void SoftServo::setMinDuty(int minDuty) {
	_minDuty=minDuty;
}

void SoftServo::setMaxDuty(int maxDuty) {
	_maxDuty=maxDuty;
}

void SoftServo::loop() {
	int val=_rotEnc.getValue();
	int dir=(val<_target);
	if (dir!=_lastDir)
		_osc++;

	_lastDir=dir;
	_lastVal=val;

	if (_osc>3) {
		_setDuty(0);
		return;
	}

	if (val<_target-_ramp)
		_setDuty(_maxDuty);

	else if (val<_target)
		_setDuty(_minDuty+(_target-val)*(_maxDuty-_minDuty)/_ramp);

	else if (val>_target+_ramp)
		_setDuty(-_maxDuty);

	else if (val>_target)
		_setDuty(-(_minDuty+(val-_target)*(_maxDuty-_minDuty)/_ramp));

	else
		_setDuty(0);
}