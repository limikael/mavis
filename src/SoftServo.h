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
	void setMinDuty(int minDuty);
	void setMaxDuty(int maxDuty);
	void setRamp(int ramp);

private:
	int _minDuty,_maxDuty;
	int _ramp;
	int _osc;
	int _target;
	int _motorAPin;
	int _motorBPin;
	int _lastVal,_lastDir;
	void _setDuty(int duty);
	RotEnc _rotEnc;
};

#endif