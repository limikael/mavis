int arduinoMockPins[256];

void pinMode(int pin, int mode) {

}

void analogWrite(int pin, int duty) {
	arduinoMockPins[pin]=duty;
}
