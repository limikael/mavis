class RotaryEncoder {
private:
	int _aPin,_bPin;
	int _a,_b;
	int _value;

	void updateVals() {
		int aVal=analogRead(_aPin);
		int bVal=analogRead(_bPin);

		if (aVal<500)
			_a=0;

		if (aVal>600)
			_a=1;

		if (bVal<500)
			_b=0;

		if (bVal>600)
			_b=1;

/*		_a=aVal<550?1:0;
		_b=bVal<550?1:0;*/
	}

public:
	RotaryEncoder(int aPin, int bPin) {
		_aPin=aPin;
		_bPin=bPin;

		updateVals();

		_value=0;
	}

	void update() {
		int lastA=_a, lastB=_b;

		updateVals();

		// b: 0->1
		if (_b && !lastB)
			_value+=(_a?-1:1);

		// b: 1->0
		if (!_b && lastB)
			_value+=(_a?1:-1);

		// a: 0->1
		if (_a && !lastA)
			_value+=(_b?1:-1);

		// a: 1->0
		if (!_a && lastA)
			_value+=(_b?-1:1);
	}

	int getState() {
		return _a+(_b<<1);
	}

	int getValue() {
		return _value;
	}
};

RotaryEncoder encoder(0,1);
unsigned int lastMillis;

void setup() {
	Serial.begin(9600);
	Serial.print("starting now...\n\r");
	lastMillis=0;
}

void loop() {
	encoder.update();

	if (millis()>lastMillis+100) {
		lastMillis=millis();
//		Serial.print(" encstate: "); Serial.println(encoder.getState());
		Serial.print(" v: "); Serial.println(encoder.getValue());
	}
}
