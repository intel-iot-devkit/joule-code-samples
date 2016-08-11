//Exploring C++ Programming on the Intel Joule Module

/*
* In this lesson, we use some new techniques to create classes of our own, breaking our program into smaller, easier-to-digest pieces. Each of these classes holds it's own data, and handles all of it's own input and output. This makes them much simpler to use. See the README.md file on the github to learn more.
* We also use a new device: A relay.
* A relay is an electromechanical device that switches a high-current device on and off using a low-current digital signal.
* 
* This lesson will create a temperature control system which will keep an office or home at 22degC (72degF) or within one degree of it on either side. 
*/

#define LCD_ADDR (0x3E)
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50)

#include "devices.h"
#include <sstream>

int main(int argc, char **argv) {
	Devices *devices = new Devices(LCD_ADDR, RGB_ADDR, ADC_ADDR, 2, 4);
	crow::SimpleApp app;
	float set = 22.0f, cur = 0.0f; //Set the "starting temperature" to 72 degrees farenheit, and initialize a variable to hold the current temperature.
	bool mode = 0; //0=ac 1=htr
	bool power = 0;
	


	for (;;) {
		devices->clear();
		std::ostringstream ss;
		ss << std::fixed << std::setprecision(2) << "Hi: " << hi << " Low: " << low;
		devices->display(0, 0, ss.str());
		cur = devices->getTemp();
		devices->display(1, 0, devices->stringify(cur));

		if (cur <= set-5.0f) {
			mode = 1;
			power = 1;
		}
		else if (cur <= set-1.0f && cur > set-5.0f) {
			switch (mode) {
				case 0:
					//Set the power off.
					power = 0;
					break;
				case 1:
					power = 1;
					break;
			}
		}
		else if (cur > set-1.0f && cur < set+1.0f) {
			//Do nothing, because we want to let it stay in this range.
			//This statement is here in case we want to add other functionality
			//	to this range.
		}
		else if (cur >= set+1.0f && cur < set+5.0f) {
			switch (mode) {
				case 0:
					//If the power's off, turn it on so it can cool.
					power = 1;
					break;
				case 1:
					power = 0;
					break;
			}
		}
		else if (cur >= set+5.0f) {
			//Set to AC mode and start cooling.
			mode = 0;
			power = 1;
		}
	}
}