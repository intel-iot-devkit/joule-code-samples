#include <mraa.hpp>
#include "relay.h"

//Default Constructor
Relay::Relay() {}

//Constructor (int)
Relay::Relay(int pin) {
	outPin = new mraa::Gpio(pin);
	outPin->dir(mraa::DIR_OUT);
}

//Destructor
Relay::~Relay() {
	if (outPin != nullptr)
		delete outPin;
}

void Relay::on() {
	if (outPin != nullptr)
		outPin->write(1);
}

void Relay::off() {
	if (outPin != nullptr)
		outPin->write(0);
}

bool Relay::getState() {
	if (outPin != nullptr)
		return outPin->read();
}