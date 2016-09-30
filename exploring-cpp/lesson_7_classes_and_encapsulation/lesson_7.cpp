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

//Exploring C++ Programming on the Intel Joule Module

/*
* In this lesson, we use some new techniques to create classes of our own, breaking our program into smaller, easier-to-digest pieces. Each of these classes holds it's own data, and handles all of it's own input and output. This makes them much simpler to use. See the README.md file on the github to learn more.
* We also use a new device: A relay.
* A relay is an electromechanical device that switches a high-current device on and off using a low-current digital signal.
* 
* This lesson will create a temperature control system which will keep an office or home at 22degC (72degF) or within one degree of it on either side. 
*/
#define BUF 2.0f //The distance from the set temperature where the system will switch modes.
#define REFRESH_RATE 5 //The time in seconds between system refreshes.
#define LCD_ADDR (0x3E)
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50)

#include "devices.h"
#include <sstream>
#include <string>

int main(int argc, char **argv) {
	Devices devices = Devices(LCD_ADDR, RGB_ADDR, ADC_ADDR, 2, 4);
	float set = 22.0f, cur = 0.0f; //Set the "starting temperature" to 72 degrees farenheit, and initialize a variable to hold the current temperature.
	bool mode = 0; //0=ac 1=htr
	bool power = 0;

	for (;;) {
		devices.clear();
		std::ostringstream ss;
		ss << std::fixed << std::setprecision(2) << "Target: " << set;
		devices.display(0, 0, ss.str());
		cur = devices.getTemp();
		ss.str(std::string()); //clear the stringstream
		ss << std::fixed << std::setprecision(2) << cur;
		devices.display(1, 5, ss.str());

		if (cur <= set-BUF) {
			mode = 1;
			power = 1;
		}
		else if (cur <= set-1.0f && cur > set-BUF) {
			if (!mode) //Set the power off.
				power = 0;
			else if (mode)
				power = 1;
		}
		else if (cur > set-1.0f && cur < set+1.0f) {
			//Do nothing, because we want to let it stay in this range.
			//This statement is here in case we want to add other functionality
			//	to this range.
		}
		else if (cur >= set+1.0f && cur < set+BUF) {
			if (!mode) //If the power's off, turn it on so it can cool.
				power = 1;
			else if (mode)
				power = 0;
		}
		else if (cur >= set+BUF) {
			//Set to AC mode and start cooling.
			mode = 0;
			power = 1;
		}

		if (power) {
			devices.setAc(!mode);
			devices.setHtr(mode);
		}

		else {
			devices.setAc(0);
			devices.setHtr(0);
		}

		sleep(REFRESH_RATE);
	}

	return 0;
}