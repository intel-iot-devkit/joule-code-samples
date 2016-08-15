#include "devices.h"
#include "relay.h"
#include "jhd1313m1.hpp"
#include "adc121c021.hpp"
#include <sstream>
#include <string>
#include <iomanip>
#include <type_traits>
#include <cmath>

Devices::Devices() {}

Devices::Devices(unsigned int lcd, unsigned int rgb, unsigned int adc, int acPin, int htrPin) {
	this.lcd = new upm::Jhd1313m1(0, lcd, rgb);
	this.adc = new upm::ADC121C021(0, adc);
	this.ac =  Relay(acPin);
	this.htr = Relay(htrPin);
}

Devices::~Devices() {
	delete lcd;
	delete adc;
}

void Devices::display(int row, int col, std::string str) {
	lcd->setCursor(row, col);
	lcd->write(str);
}

void Devices::clear() {
	lcd->clear();
}

void Devices::color(int r, int g, int b) {
	lcd->setColor(r,g,b);
}

float Devices::getTemp() {
	int resistance = adc->value();
	float temperature = 1.0/(log((100000.0*(4095.0/((float)resistance)-1.0))/100000.0)/4275+1/298.15)-273.15;
	return temperature;
}

void Devices::setAc(bool b) {
	switch (b) {
		case true:
			ac.on();
			break;
		case false:
			ac.off();
			break;
	}
}

void Devices::setHtr(bool b) {
	switch (b) {
		case true:
			htr.on();
			break;
		case false:
			htr.off();
			break;
	}
}