BOARD_TAG     = leonardo
ARDUINO_DIR   = /Applications/Arduino.app/Contents/Java
AVR_TOOLS_DIR = /usr/local
MONITOR_PORT  = /dev/tty.usbmodem14321
CXXFLAGS_STD  = -lstdc++ -fno-threadsafe-statics

ARDUINO_LIBS  = Wire SPI EEPROM Arduboy

include /usr/local/opt/arduino-mk/Arduino.mk
