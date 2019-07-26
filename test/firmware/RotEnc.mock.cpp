#include "src/rotenc/RotEnc.h"
#include <stdio.h>

RotEnc *rotEncMockInstance=NULL;

RotEnc::RotEnc(int pinA, int pinB) {
	printf("RotEnc mock instance created\n");

	rotEncMockInstance=this;
}

int RotEnc::getValue() {
	return _value;
}

void setRotEncMockValue(int v) {
	rotEncMockInstance->_value=v;
}