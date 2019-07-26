bin/soft-servo-test: src/SoftServo.cpp src/SoftServo.h test/firmware/*
	gcc -o bin/soft-servo-test \
		-I. -I./test/firmware -DMOCK_ARDUINO \
		src/SoftServo.cpp \
		test/firmware/RotEnc.mock.cpp \
		test/firmware/Arduino.mock.cpp \
		test/firmware/SoftServo.test.cpp \
