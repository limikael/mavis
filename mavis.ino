#include "src/mqthing/MqThing.h"
#include "src/rotenc/RotEnc.h"
#include "src/SoftServo.h"

MqThing thing;
SoftServo servo(D2,D6,D5,D7);

void on_connect() {
  Serial.println("Yey... Connect...");

  thing.subscribe("mavis");
  thing.publish("hello","connected...");
}

void on_message(String topic, String payload) {
  Serial.println(String("In: ")+topic+String(": ")+payload);

  char *c=strtok((char*)payload.c_str()," \n\t\r");
  char *a=strtok(NULL," \n\t\r");

  String cmd=String(c);
  String arg=String(a);

  if (cmd=="green") {
    if (arg=="off")
      digitalWrite(D3,LOW);

    else
      digitalWrite(D3,HIGH);
  }

  else if (cmd=="target") {
    int target=atoi(arg.c_str());
    servo.setTarget(target);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  thing.setButtonPin(D1);
  thing.setLedPin(D8);
  thing.setName("Mavis");
  thing.setServer("postman.cloudmqtt.com",13342);
  thing.setServerAuth("hbpiywwf","q6YEkRNQwT4x");
  thing.onConnect(on_connect);
  thing.onMessage(on_message);

  pinMode(D3,OUTPUT);
  servo.setMinDuty(0);
  servo.setMaxDuty(768);
  servo.setTolerance(10);
  servo.setRamp(1000);
}

void loop() {
  thing.loop();
  servo.loop();
}
