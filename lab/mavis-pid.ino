#include "src/mqthing/MqThing.h"
#include "src/rotenc/RotEnc.h"
#include <PID_v1.h>

MqThing thing;
RotEnc rotEnc(D5,D7);
double setpoint, input, output;
PID pid(&input,&output,&setpoint,.1,0,0,DIRECT);

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
    setpoint=target;
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
  pinMode(D2,OUTPUT);
  pinMode(D6,OUTPUT);

  digitalWrite(D2,LOW);
  digitalWrite(D6,LOW);

  setpoint=0;
  input=rotEnc.getValue();

  pid.SetOutputLimits(-768,768);
  pid.SetMode(AUTOMATIC);
}

void loop() {
  thing.loop();

  input=rotEnc.getValue();
  pid.Compute();
  Serial.println(String(input)+" -> "+String(setpoint)+" d: "+String(output));

  if (abs(output)<25) {
    analogWrite(D2,0);
    analogWrite(D6,0);
  }

  else if (output>0) {
    analogWrite(D2,255+output);
    analogWrite(D6,0);
  }

  else {
    analogWrite(D2,0);
    analogWrite(D6,255+(-output));
  }
}
