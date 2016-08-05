//Truly learn to code with Intel on Grosse Tete - Lesson 5

/*
* In the last lesson, you learned how to write the code to
* make an i2c device print out some text. Now let's combine that
* with some something else.
* 
* For this lesson, you'll need a few things:
*  1. Your setup from Lesson 4
*  2. A Grove ADC module.
*  3. A Grove tepmerature sensor.
*  4. Two more 4-pin JST cables.
* 
* And that's it! With those four things, we can write a basic
* temperature readout.
* 
* Connect the four-pin JST cable from the temperature sensor to
* the input of the ADC. You can recognize it by it's pin labels
* consisting of "GND", "Vcc", "NC" and "SIG". It will only fit
* one way, so just plug it in.
* 
* Next, connect the ADC's output, (The one with "SDA" and "SCL")
* to another I2C connector on the Grove Base Shield from the last
* lesson. That's it! If you need help rebuilding the circuit, check
* out the schematic on <link to lesson four>lesson 4</link>.
*/

#define LCD_ADDR (0x3E) 
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50) //Just like the LCD screen, we need to store our ADC's address somewhere.

#include "jhd1313m1.hpp"
#include "adc121c021.hpp" //The header file for the ADC we plan to use.
#include <iostream>
#include <iomanip> //Lets us format our output a bit, to make it pretty.
#include <sstream> //This allows us to create a small stream within the program to format our strings with.
#include <cmath> //This will give us access to the floor() function.

using namespace std;

upm::Jhd1313m1 *lcd;
upm::ADC121C021 *adc;

void sig_handler(int sig) {
	cout << "\nExiting..." << endl;
	delete lcd;
	delete adc;
	exit(0);
}

int main(int argc, char **argv) {
	lcd = new upm::Jhd1313m1(0, LCD_ADDR, RGB_ADDR);
	adc = new upm::ADC121C021(0, ADC_ADDR); //Just like the LCD, we have to create a new instance of the ADC class.

	lcd->setColor(0, 255, 0); //Start our LCD out at a green color.

	//Create a value to hold the resistance value from the ADC.
	//The values should always be between 0-4095
	//Unsigned means that the value can never be below zero.
	unsigned int resistance;

	lcd->setCursor(0,0);
	lcd->write("Temperature:");

	while (true) { //loop over this code indefinitely.

		//Now, let's get the current value from the ADC and
		//load it into the 
		resistance = adc->value();

		//Now, calculate the temperature from the resistance value, and
		//some known facts about the thermistor we're using.
		//Dont worry if this doesn't make sense. It's different for
		//every thermistor anyway, and you can find the information in
		//the thermistor's datasheet.
		float temperature=1.0/(log((100000.0*(4095.0/((float)resistance)-1.0))/100000.0)/4275+1/298.15)-273.15;

		//Now we have our temperature value contained in a floating-point variable.
		//Let's do something with it! First, let's print it to the screen.

		//The next two lines create a string stream, and output the temperature to it in
		//order to round it to two decimal places.
		ostringstream out;
		out << setprecision(2) << fixed << temperature;

		lcd->setCursor(1,1);

		//Write the stringstream's value, after converting it to a c-type string (a character array.)
		lcd->write(out.str().c_str());

		//Now, how about we change the color of the display, based on the temperature?
		if (temperature <= 20.0) {
			lcd->setColor(0, 255, 0);
		}
		else if (temperature > 20.0 && temperature <= 33.0) {
			lcd->setColor(128, 128, 0);
		}
		else if (temperature > 33.0) {
			lcd->setColor(255, 0, 0);
		}

		//That's it! We've got everything we need, and it should be displaying the temperature on your screen.
	}

	//Clean up...
	delete lcd;
	delete adc;
	return 1;
}