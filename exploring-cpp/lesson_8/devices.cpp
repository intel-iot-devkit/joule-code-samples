#include "relay.h"
#include "jhd1313m1.hpp"
#include "adc121c021.hpp"
#include <sstream>
#include <string>
#include <iomanip>

Devices::Devices() {}

Devices::Devices(unsigned int lcd = LCD_ADDR, unsigned int rgb = RGB_ADDR, unsigned int adc = ADC_ADDR, int acPin, int htrPin) {
	lcd = new Jhd1313m1(0, lcd, rgb);
	adc = new ADC121C021(0, adc);
	ac =  Relay(acPin);
	htr = Relay(htrPin);
}

Devices::~Devices() {
	delete lcd;
	delete adc;
}

template <typename T> string Devices::stringify(T data) {
	std::ostringstream ss;
	ss << data
	return ss.str();
}

template <> string Devices::stringify(float data) {
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(2) << data;
	return ss.str();
}

void Devices::display(int row, int col, string str) {
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

void Devices::acControl(bool b) {
	switch (b) {
		case true:
			ac.on();
			break;
		case false:
			ac.off();
			break;
	}
}

void Devices::htrControl(bool b) {
	switch (b) {
		case true:
			htr.on();
			break;
		case false:
			htr.off();
			break;
	}
}