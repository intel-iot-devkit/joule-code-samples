#include "devices.h"
#include "jhd1313m1.hpp"
#include "adc121c021.hpp"
#include "mraa.hpp"
#include <sstream>
#include <string>
#include <iomanip>
#include <type_traits>
#include <cmath>

Devices::Devices(unsigned int lcd, unsigned int rgb, unsigned int adc, int acPin, int htrPin) {
	this->lcd = new upm::Jhd1313m1(0, lcd, rgb);
	this->adc = new upm::ADC121C021(0, adc);
	ac = new mraa::Gpio(acPin);
	htr = new mraa::Gpio(htrPin);
}

Devices::~Devices() {
	delete lcd;
	delete adc;
	delete ac;
	delete htr;
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
	if(b)
		ac->write(1);
	else
		ac->write(0);
}

void Devices::setHtr(bool b) {
	if(b)
		htr->write(1);
	else
		htr->write(0);
}