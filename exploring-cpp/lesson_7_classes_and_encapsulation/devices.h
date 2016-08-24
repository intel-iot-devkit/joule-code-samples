/*
Copyright (c) 2015 - 2016 Intel Corporation.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef DEVICES_H_
#define DEVICES_H_

#define LCD_ADDR (0x3E)
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50)

#include "jhd1313m1.hpp"
#include "adc121c021.hpp"
#include "mraa.hpp"

#include <sstream>
#include <string>
#include <iomanip>

class Devices {
private:
	upm::Jhd1313m1 *lcd;
	upm::ADC121C021 *adc;
	mraa::Gpio *ac;
	mraa::Gpio *htr;
public:
	//Default (empty) constructor.
	Devices();
	//Constructor
	Devices(unsigned int lcd = LCD_ADDR, unsigned int rgb = RGB_ADDR, unsigned int adc = ADC_ADDR, int acPin = 2, int htrPin = 4);
	//Copy Constructor
	Devices(const Devices& d);
	//Destructor
	~Devices();

	//Functions
	void display(int row, int col, std::string str);
	void clear();
	void color(int r, int g, int b);
	float getTemp();
	void setAc(bool b);
	void setHtr(bool b);
};

#endif