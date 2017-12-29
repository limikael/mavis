# not working right now...

BOARD_TAG = uno

#ARDMK_DIR = /home/m/usr/arduino/
ARDUINO_DIR = /home/m/usr/arduino/
#AVR_TOOLS_DIR = /home/m/usr/arduino/hardware/tools/avr/
AVR_TOOLS_DIR = /usr/

#ARDUINO_LIBS = StepperDriver Scheduler
USER_LIB_PATH=./libraries

ARDUINO_SKETCHBOOK = src/mavis.ino

CXXFLAGS_STD = -std=c++11

include /home/m/usr/arduino/Arduino.mk

