// Probably not working right now... :(

void setup() {
	Serial.begin(9600);
	Serial.print("starting now...\n\r");

	pinMode(8,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);

	digitalWrite(8,1);
}

void loop() {
	int v=analogRead(0)/4;

	/*Serial.print("val: ");
	Serial.println(v);
	delay(500);*/

	analogWrite(10,v);
	analogWrite(11,255-v);

/*	analogWrite(10,0);
	analogWrite(11,900);*/

/*	digitalWrite(13,0);
	delay(1000);
	digitalWrite(13,1);*/
}