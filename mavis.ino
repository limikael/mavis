void setup() {
	Serial.begin(9600);
	Serial.print("starting now...\n\r");

	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(12,OUTPUT);

	digitalWrite(12,1);
}

void loop() {
	int v=analogRead(0);
	Serial.println(v);

	if (v>512-64 && v<512+64) {
		analogWrite(10,128);
		analogWrite(11,128);
	}

	else {
		analogWrite(10,v/4);
		analogWrite(11,255-v/4);
	}

/*	digitalWrite(10,0);
	digitalWrite(11,1);*/

	delay(100);
}
