#include "src/mqthing/MqThing.h"
#include "src/rotenc/RotEnc.h"

MqThing thing;
RotEnc enc(D7,D5);
int lastEnc=0;

void on_connect() {
  Serial.println("Yey... Connect...");

  thing.subscribe("mavis");
  thing.publish("hello","connected...");
}

void on_message(String topic, String payload) {
  Serial.println(String("In: ")+topic+String(": ")+payload);

  if (payload=="green-on") {
    digitalWrite(D6,HIGH);
  }

  else if (payload=="green-off") {
    digitalWrite(D6,LOW);
  }

  else if (payload=="motor-stop") {
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
  }

  else if (payload=="motor-left") {
    digitalWrite(D2,HIGH);
    digitalWrite(D3,LOW);
  }

  else if (payload=="motor-right") {
    digitalWrite(D2,LOW);
    digitalWrite(D3,HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);

  thing.setButtonPin(D1);
  thing.setLedPin(D8);
  thing.setName("Mavis");
  thing.setServer("postman.cloudmqtt.com",13342);
  thing.setServerAuth("hbpiywwf","q6YEkRNQwT4x");
  thing.onConnect(on_connect);
  thing.onMessage(on_message);

  pinMode(D6,OUTPUT);
}

void loop() {
  thing.loop();

  int v=enc.getValue();
  if (v!=lastEnc) {
    Serial.println(v);
    lastEnc=v;
  }

//  delay(100);
}
