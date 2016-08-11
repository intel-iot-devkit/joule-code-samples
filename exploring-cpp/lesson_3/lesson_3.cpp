//Exploring C++ Programming on the Intel Joule Module

/*
* In the last lessons, you learned how to format a c++ program, and how to use a GPIO pin of the Grosse Tete or Edison.
* In this lesson, we'll cover the basics of PWM, or Pulse Width Modulation. This is a way of simulating analog output in
* digital circuits. For this lesson, you'll need a small breadboard, a few jumper wires, any basic low-intensity LED, and a resistor of roughly 220ohm to limit
* the current.
* 
* Pin 32 - PWM Out
* Pin 36 - GND
* 
* Connect pin 32 (on breakout 1) to one of the rows on your breadboard. Connect one leg of the resistor to another spot on that row, and the other leg to a spot
* on another row of the breadboard. Connect a second jumper to that same row, then connect the other end of that jumper to pin 36.
* 
* That's the whole circuit. Now, let's focus on the code...
*/

#define SLEEP_TIME 10000
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include <mraa.hpp>

using namespace std;

mraa::Pwm *pwm;

//Define the signal handler.
void signal_handler(int sig) {
	delete pwm;
	cout << "Exiting." << endl;
	exit(0);
}

//Main entry point.
int main(int argc, char **argv) {

	//Enable the signal handler.
	signal(SIGINT, signal_handler);

	//Print out a hello world statement
	//so that we know the program's running.
	cout << "Hello from Intel on Grosse Tete!" << endl
	<< "Press Ctrl+c to exit..." << endl;

	//Create a PWM object. This 
	pwm = new mraa::Pwm(32);

	//This will only run if the instantiation of
	//the PWM object was successful.
	if (pwm) { 

		//Enable the PWM pin.
		pwm->enable(true);

		//loop forever until ctrl+c is pressed.
		while (true) {
			float value = 0.00f;

			//Loop through the values between 0.00 and 1.00 by 0.01, and
			//write that value to the PWM pin at each iteration.
			//Then, loop through the same values backwards.

			do {
				value += 0.01f;
				pwm->write(value);
				usleep(SLEEP_TIME);
			} while (value < 1.00f);
			do {
				value -= 0.01f;
				pwm->write(value);
				usleep(SLEEP_TIME);
			} while (value > 0.00f);
			usleep(SLEEP_TIME);
		}
	}

	//Dispose of the object, now that we no longer need it.
	//This is only needed because the object was allocated
	//on the heap instead of the stack. (I.e. created with a pointer.)
	delete pwm;
	return 1;
}