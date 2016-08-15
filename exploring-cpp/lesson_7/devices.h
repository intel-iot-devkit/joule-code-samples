#ifndef DEVICES_H_
#define DEVICES_H_

#define LCD_ADDR (0x3E)
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50)

#include "jhd1313m1.hpp"
#include "adc121c021.hpp"
#include <sstream>
#include <string>
#include <iomanip>
#include "relay.h"

class Devices {
private:
	upm::Jhd1313m1 *lcd;
	upm::ADC121C021 *adc;
	Relay ac;
	Relay htr;
public:
	//Default (empty) constructor.
	Devices();
	//Constructor
	Devices(unsigned int lcd = LCD_ADDR, unsigned int rgb = RGB_ADDR, unsigned int adc = ADC_ADDR, int acPin = 1, int htrPin = 2);
	//Destructor
	~Devices();

	//Functions
	void display(int row, int col, string str);
	void clear();
	void color(int r, int g, int b);
	float getTemp();
	void setAc(bool b);
	void setHtr(bool b);
};

#endif