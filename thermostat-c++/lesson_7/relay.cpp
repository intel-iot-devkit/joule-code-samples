#include "relay.h"
#include <mraa.hpp>

Relay::Relay() {}

Relay::Relay(int pin) {
	relay = new mraa::Gpio(pin);
	relay->dir(mraa::DIR_OUT);
}

Relay::~Relay() {
	delete relay;
}

void Relay::on() {
	relay->write(1);
}

void Relay::off() {
	relay->write(0);
}

bool Relay::getState() {
	return (bool)relay->read();
}