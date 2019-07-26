#include <stdio.h>
#include "src/SoftServo.h"

extern RotEnc *rotEncMockInstance;
void setRotEncMockValue(int v);
extern int arduinoMockPins[];

void testServo(SoftServo *servo, int target, int rotEncValue) {
	servo->setTarget(target);
	setRotEncMockValue(rotEncValue);
	servo->loop();

	printf("Target: %4d, value: %4d, Duty1: %4d, Duty2: %4d\n",
		target,rotEncValue,arduinoMockPins[0],arduinoMockPins[1]);
}

int main(void) {
	SoftServo servo(0,1,2,3);
	servo.setTolerance(10);
	servo.setMinDuty(100);
	servo.setMaxDuty(200);
	servo.setRamp(50);

	for (int i=-100; i<=100; i+=5)
		testServo(&servo,20,i);
}