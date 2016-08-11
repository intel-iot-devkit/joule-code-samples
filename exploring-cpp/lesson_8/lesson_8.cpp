//Exploring C++ Programming on the Intel Joule Module

/*
* Most of this code is easily recognizable from that of Lesson 7. In this lesson, however, we're going to make it multithreaded, and add in a Crow webserver to allow the user to turn the system on and off, as well as to set it's temperature. 
*/

#define LCD_ADDR (0x3E)
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50)

#include "devices.h"
#include "unistd.h"
#include <csignal>
#include <sstream>
#include "crow_all.h"

using namespace std;

Devices *devices;

void thread_function(Devices &devices, bool &mode, bool &power, float &set, bool &enabled) {
	for (;;) {
		devices->clear();
		ostringstream ss;
		ss << fixed << setprecision(2) << "Hi: " << hi << " Low: " << low;
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

		
		devices->acControl(false);
		devices->htrControl(false);
		if (power) {
			devices->acControl(!mode);
			devices->htrControl(mode);
		}

		sleep(5);
	}
}

void sig_handler(int sig) {
	delete devices;
}

int main(int argc, char **argv) {
	
	signal(SIGINT, sig_handler);

	devices = new Devices(LCD_ADDR, RGB_ADDR, ADC_ADDR, 2, 4);
	float set = 22.0f, cur = 0.0f; //Set the "starting temperature" to 72 degrees farenheit, and initialize a variable to hold the current temperature.
	bool mode = 0; //0=ac 1=htr
	bool power = 0;
	bool enabled = false;

	thread t1(ref(devices), ref(mode), ref(power), ref(set));

	crow::SimpleApp app;
	crow::mustache::set_base(".");

	//Implement crow server.
	CROW_ROUTE(app, "/")([](const crow::request &req){
		if (req.url_params.get("target") != nullptr) {
			set = boost::lexical_cast<float>(req.url_params.get("target"));
		}

		if (req.url_params.get("power") != nullptr) {
			if (boost::lexical_cast<string>(req.url_params.get("power")) == "on") {
				enabled = true;
			} else {
				enabled = false;
			}
		}
	});

	app.port(80).multithreaded().run();

	t1.join();

	delete devices;
	return 0;
}