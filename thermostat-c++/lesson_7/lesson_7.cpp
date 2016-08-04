//Truly learn to code with Intel on Grosse Tete - Lesson 7

/*
* Now that you've learned how to use Crow, we're ready to start on the next
* lesson. In this lesson, we'll be building a home thermostat that can be set
* via a web interface, and can control a heating and air conditioning system.
* 
* For this example, you'll need the setup as in lesson 5, but you'll also need
* two Grove relay modules.
* 
* The relay modules can be attached thusly:
* 
* <insert schematic link here>
* 
* We'll also be using some new code. A struct is a simple way of creating an
* object within the same class. It allows you to contain code for specific
* parts of a program in a single spot.

* compile with -lupm-adc121c021 -lupm-i2clcd -pthread -lboost_system -lmraa -std=c++11
*/

#define LCD_ADDR (0x3E)
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50)

#include <iostream>
#include <iomanip>
#include <crow_all.h>
#include <sstream>
#include <string>
#include <cmath>

#include <mraa.hpp>
#include <jhd1313m1.hpp>
#include <adc121c021.hpp>
#include "relay.h"
#include <thread>
#include <functional>

using namespace std;

struct Devices {
	upm::Jhd1313m1 *lcd;
	upm::ADC121C021 *adc;
	Relay ac;
	Relay htr;
	int currentMode = 0;
	int status = 0;

	Devices() {
		lcd = new upm::Jhd1313m1(0, LCD_ADDR, RGB_ADDR);
		adc = new upm::ADC121C021(0, ADC_ADDR);
		ac = Relay(2);
		htr = Relay(4);
	}

	~Devices() {
		delete lcd;
		delete adc;
	}

	void displayHeader(string str) {
		lcd->setCursor(0,0);
		lcd->write(str);
	}

	void displayTemp(float t) {
		lcd->setCursor(1,3);
		ostringstream ss;
		ss << setprecision(2) << fixed << t << " degC";
		lcd->write(ss.str().c_str());
	}

	float getTemp() {
		int resistance = adc->value();
		float temperature=1.0/(log((100000.0*(4095.0/((float)resistance)-1.0))/100000.0)/4275+1/298.15)-273.15;
		return temperature;
	}

	void unitControl(int mode, int status) {
		this->status = status;
		switch (currentMode) {
			case -1:
				if (this->currentMode != -1) {
					htr.off();
					ac.on();
					lcd->setColor(64, 64, 255);
				}
				break;
			case 0:
				if (this->currentMode != 0) {
					htr.off();
					ac.off();
					lcd->setColor(128, 128, 128);
				}
				break;
			case 1:
				if (this->currentMode != 1) {
					htr.on();
					ac.off();
					lcd->setColor(255, 64, 64);
				}
				break;
			default:
				break;
		}
		this->currentMode = mode;
	}

};

void control_thread(Devices &devices, float &highTemp, float &lowTemp) {
	while (true) {
		ostringstream ss;
		ss << "Hi: " << highTemp << " Lo: " << lowTemp;
		devices.displayHeader(ss.str());
		devices.displayTemp(devices.getTemp());

		if (devices.currentMode == -1 && devices.getTemp() > lowTemp && devices.status == 1) {
			//AC on, cooling, not yet to low temp.
			//Do nothing.
			cout << "AC Mode : Cooling On" << endl;
		}
		else if (devices.currentMode == -1 && devices.getTemp() <= lowTemp && devices.getTemp() > lowTemp-5 && devices.status == 1) {
			//AC on, cooling, reached low temp.
			//Shut off and set status to 0.
			devices.unitControl(-1, 0);
			cout << "AC Mode : Cooling On" << endl;
		}
		else if (devices.currentMode == -1 && devices.getTemp() <= lowTemp-5) {
			//AC on, not cooling, 5 degrees under minimum temperature
			//Switch to Heater mode, and start heating until high temperature reached.
			devices.unitControl(1, 1);
			cout << "Heater Mode : Heating On" << endl;
		}
		else if (devices.currentMode == -1 && devices.getTemp() >= highTemp && devices.status == 0) {
			//AC on, not cooling, at max temperature.
			devices.unitControl(-1, 1);
			cout << "AC Mode : Cooling Off" << endl;
		}
		else if (devices.currentMode == 1 && devices.getTemp() < highTemp && devices.status == 1) {
			//Heater on, heating, not yet to max temp.
			//Do nothing.
			cout << "Heater Mode : Heating On" << endl;
		}
		else if (devices.currentMode == 1 && devices.getTemp() >= highTemp && devices.getTemp() < highTemp+5 && devices.status == 1) {
			//Heater on, heating, at max temp.
			devices.unitControl(1, 0);
			cout << "Heater Mode : Heating Off" << endl;
		}
		else if (devices.currentMode == 1 && devices.getTemp() >= highTemp + 5) {
			//Heater on, 5 deg above maximum temperature
			//Switch to AC mode, and start cooling until low temperature reached.
			devices.unitControl(-1, 1);
			cout << "AC Mode : Cooling On" << endl;
		}
		else if (devices.currentMode == 1 && devices.getTemp() <= lowTemp && devices.status == 0) {
			//Heater on, not heating, at minimum temperature.
			devices.unitControl(1, 1);
			cout << "Heater Mode : Heating On" << endl;
		}
		else {
			cout << "currentMode: " << devices.currentMode << " Status: " << devices.status << endl;
			cout << "getTemp() -> " << devices.getTemp() << " lowTemp: " << lowTemp << " highTemp: " << highTemp << endl;
			cout << "Something wasn't caught..." << endl;
		}

		sleep(5);
	}
}

Devices devices;
float highTemp, lowTemp;

int main(int argc, char **argv) {
	crow::SimpleApp app;
	crow::mustache::set_base(".");
	
	thread t1(control_thread, ref(devices), ref(highTemp), ref(lowTemp));

	CROW_ROUTE(app, "/")
	([](const crow::request &req){
		if (req.url_params.get("high") != nullptr) {
			highTemp = boost::lexical_cast<float>(req.url_params.get("high"));
		}
		if (req.url_params.get("low") != nullptr) {
			lowTemp = boost::lexical_cast<float>(req.url_params.get("low"));
		}
		if (req.url_params.get("coolSetting") != nullptr) {
			string str = boost::lexical_cast<string>(req.url_params.get("coolSetting"));
			if (str == "on") {
				devices.unitControl(-1, 0)
			}
			else if (str == "off") {
				devices.unitControl(0,0);
			}
		}

		crow::mustache::context ctx;
		return crow::mustache::load("index.html").render();
	});

	app.port(10000).multithreaded().run();

	t1.join();

	return 0;

	// CROW_ROUTE(app, "/do").methods("POST"_method)
	// ([](const crow::request &req) {
	// 	ostringstream ss;
	// 	ss << req.body;
	// 	string str = ss.str();
	// 	boost::erase_all(str, "\\");
	// 	auto jsonStr = json::parse(str.substr(1,str.length()-2));
	// 	//jsonStr[][]
	// 	return "";
	// });
}
