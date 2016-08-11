//Exploring C++ Programming on the Intel Joule Module

/*
* At this point, you've learned how to format a c++ program,
* how to work with GPIO pins, and how to work with Pulse Width
* Modulation. Now, let's try something a bit harder. i2c.
* 
* i2c - Pronounced "i-squared-c", stands for "inter-integrated circuit"
* and is a method of connecting two microcontrollers or other devices
* using only a minimum of pins. Many microcontrollers, memory chips,
* and sensors use this protocol to communicate.
* 
* Setup: You'll need a Grove RGB LCD, two 10kohm resistors, a breadboard,
* six male-male jumper wires (two red, two black, one yellow, and one white),
* and a 4-pin JST cable to continue.
* 
* <TODO>Insert link to schematic here.</TODO>
*
* So now, let's go ahead and lay down some code to talk to that LCD panel.
*/

#define LCD_ADDR (0x3E) //Since these are both static, we'll use #define statements to make
#define RGB_ADDR (0x62) //them global definitions. Makes them easier to change later, too.

//Include the library for the RGB LCD
//We'll need to remember to use -lupm-i2clcd
#include "jhd1313m1.hpp"
#include <iostream>
#include <string>

using namespace std;

//Create an object to hold our LCD.
upm::Jhd1313m1 *lcd;

void sig_handler(int sig) {
	cout << "Exiting." << endl;
	delete lcd;
	exit(0);
}

int main(int argc, char **argv) {
	//Instantiate our LCD object. It's on I2C Bus 0,
	//and has the addresses as defined before.
	lcd = new upm::Jhd1313m1(0, LCD_ADDR, RGB_ADDR);

	//What color do we want our backlight to be? (Out of 255)
	int red = 128, green = 0, blue = 128;

	//Set the color to the desired one. It will show up purple.
	lcd->setColor(red, green, blue);

	//Now, let's print something to the screen. First, set the
	//cursor position.
	lcd->setCursor(0,0); //Set the cursor to 0rows x 0cols.

	//Now, this line will print "Hello, world!" to the screen.
	lcd->write("Hello, world!");
	cout << "\nPress ctrl+c to exit..." << endl << endl;
	//That's it! We've now written a line to our purple display.
	//Continue on with the next section, and we'll add to it!

	for (;;) {} //Loop indefinitely until ctrl+c is pressed.

	delete lcd;
	return 1;
}