#ifndef __SOFT_SERVO_H__
#define __SOFT_SERVO_H__

#ifdef MOCK_ARDUINO
#include "Arduino.mock.h"
#else
#include <Arduino.h>
#endif

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
	int _lastVal;
	RotEnc _rotEnc;
};

#endif