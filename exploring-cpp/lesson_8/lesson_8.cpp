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
* Most of this code is easily recognizable from that of Lesson 7. In this lesson, however, we're going to make it multithreaded, and add in a Crow webserver to allow the user to turn the system on and off, as well as to set it's temperature. 
*/

#define BUF 2.0f //The distance from the set temperature where the system will switch modes.
#define REFRESH_RATE 5 //The time in seconds between system refreshes.
#define LCD_ADDR (0x3E)
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50)

#include "devices.h"
#include "unistd.h"
#include <csignal>
#include <sstream>
#include <string>
#include "crow_all.h"

using namespace std;

Devices devices = Devices(LCD_ADDR, RGB_ADDR, ADC_ADDR, 2, 4);

void thread_function(Devices &devices, bool &mode, bool &power, float &setTemperature) {
		for (;;) {
		devices.clear();
		std::ostringstream ss;
		ss << std::fixed << std::setprecision(2) << "Target: " << setTemperature;
		devices.display(0, 0, ss.str());
		float cur = devices.getTemp();
		ss.str(std::string()); //clear the stringstream
		ss << std::fixed << std::setprecision(2) << cur;
		devices.display(1, 5, ss.str());

		if (cur <= setTemperature-BUF) {
			mode = 1;
			power = 1;
		}
		else if (cur <= setTemperature-1.0f && cur > setTemperature-BUF) {
			if (!mode) //Set the power off.
				power = 0;
			else if (mode)
				power = 1;
		}
		else if (cur > setTemperature-1.0f && cur < setTemperature+1.0f) {
			//Do nothing, because we want to let it stay in this range.
			//This statement is here in case we want to add other functionality
			//	to this range.
		}
		else if (cur >= setTemperature+1.0f && cur < setTemperature+BUF) {
			if (!mode) //If the power's off, turn it on so it can cool.
				power = 1;
			else if (mode)
				power = 0;
		}
		else if (cur >= setTemperature+BUF) {
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
}

void sig_handler(int sig) {
	exit(1);
}


float setTemperature = 22.0f; //Set the "starting temperature" to 72 degrees farenheit, and initialize a variable to hold the current temperature.
bool mode = 0; //0=ac 1=htr
bool power = 0;

int main(int argc, char **argv) {
	
	signal(SIGINT, sig_handler);


	thread t1(thread_function, ref(devices), ref(mode), ref(power), ref(setTemperature));

	crow::SimpleApp app;
	crow::mustache::set_base(".");

	//Implement crow server.
	CROW_ROUTE(app, "/")
	([](const crow::request &req){
		crow::mustache::context ctx;
		if (req.url_params.get("target") != nullptr) {
			setTemperature = boost::lexical_cast<float>(req.url_params.get("target"));
		}

		if (req.url_params.get("power") != nullptr) {
			if (boost::lexical_cast<string>(req.url_params.get("power")) == "on") {
				power = true;
			} else {
				power = false;
			}
		}
		return crow::mustache::load("lesson_8_index.html").render();
	});

	app.port(80).multithreaded().run();

	t1.join();

	return 0;
}