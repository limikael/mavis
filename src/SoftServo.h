#ifndef __SOFT_SERVO_H__
#define __SOFT_SERVO_H__

#include <Arduino.h>
#include "rotenc/RotEnc.h"

class SoftServo {
public:
	SoftServo(int motorAPin, int motorBPin, int encAPin, int encBPin);
	void setTarget(int target);
	void loop();
	void setDuty(int duty);
	void setTolerance(int tolerance);

private:
	int _duty;
	int _target;
	int _motorAPin;
	int _motorBPin;
	int _tolerance;
	RotEnc _rotEnc;
	int _lastVal;
};

#endif