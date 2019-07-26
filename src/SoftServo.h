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
	void loop();

	void setTarget(int target);
	void setTolerance(int tolerance);
	void setMinDuty(int minDuty);
	void setMaxDuty(int maxDuty);
	void setRamp(int ramp);

private:
	int _minDuty,_maxDuty;
	int _target;
	int _motorAPin;
	int _motorBPin;
	int _tolerance, _ramp;
	int _lastVal;
	void _setDuties(int aDuty, int bDuty);
	RotEnc _rotEnc;
};

#endif