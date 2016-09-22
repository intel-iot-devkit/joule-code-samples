## Lesson 3: PWM

In the last lessons, you learned how to format a C++ program, and how to use a GPIO pin of the Joule or Edison. In this lesson, we'll cover the basics of PWM, or Pulse Width Modulation. This is a way of simulating analog output in digital circuits. For this lesson, you'll need a small breadboard, a few jumper wires, any basic low-intensity LED, and a resistor of roughly 220ohm to limit the current. You could also use a Grove Shield, combined with an LED module (with LED), one of the 4 pin JST connectors and a few jumper wires.

**Remeber to power down your Joule board _before_ making these connections!**

### Breadboard

1. Connect a jumper wire between;
	* Pin 32 (on the Joule's JI2/Breakout #1 IO rail)
	* One column on your breadboard
2. Connect your resistor between;
	* The column the previous jumper wire is connected to
	* A seperate column of the breadboard
3. Connect a jumper wire between;
	* Pin 36 (on the Joule's JI2/Breakout #1 IO rail)
	* A column on your breadboard
4. Connect your LED;
	* Connect the positive leg of the LED to the column your resistor ended up on
	* Connect the other leg of the LED to the column where you connected Pin 36

### Grove Shield

1. Connect a jumper wire between;
	* Pin 44 (Pin 2 on the Joule's JI3/Breakout #2 IO rail)
	* The 5V pin on your Grove shield
2. Connect a jumper wire between;
	* Pin 43 (Pin 1 on the Joule's JI3/Breakout #2 IO rail)
	* Any of the GND pins on your Grove shield
3. Ensure that the PWR LED on the Grove shield is on, if it isn't;
	* Ensure that the VCC switch is set to 5V
4. Connect a jumper wire between;
	* Pin 32 (on the Joule's JI2/Breakout #1 IO rail)
	* Digital pin 2 on the Grove shield
5. Connect a 4-pin JST connector between;
	* The D2 port on your Grove shield
	* A Grove LED module
6. Connect an LED into the Grove LED module;
	* Ensure that the long leg of the LED is in on the side marked with a "+"
	
![Lesson 3 diagram](joule-code-samples/exploring-cpp/lesson_3_pwm/lesson_3_diagram.jpg )

### The Code

As before, we instantiate an object, but this time it’s a PWM object instead of a GPIO object. The program continues upon successful building of the object. This pin is then enabled, in order to allow for proper PWM. It runs the main loop forever, until Ctrl+c is pressed. The loop goes through the values 0.01 and 1 by 0.01 and write the value to the PWM pin at each iteration. It then loops through the values backwards.

It should cause the LED to glow brighter then dimmer through the iterations. Finally if the PWM object fails to be created, it’s deleted and the program returns 1, allowing you to know that it errored out.

Now ensure to use the proper compiler flags when you attempt to compile this program!

`g++ -lmraa lesson_3.cpp -o lesson_3`

Now run the program using the following command.

`./lesson_3`

### Troubleshooting

Running the program should make the LED you attached glow, dimly at first before getting brighter, then fading back out. If it doesnt, check your wiring and the polarity of your LED. Finally if it still doesnt work, enter the following command to find out what version of mraa you have.

`mraa-gpio version`

If it returns a version that's less than 1.2.1 then you need to update your copy of mraa to the latest version.

[//]: # (Insert link to installing mraa on GT)

### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|
|:---------------------:|:-----------------:|:-----------------:|
|	Ostro 166			|Intel Stock Board	|	mraa 1.2.3		|
|	Ostro 166 			|Intel Stock Board	|	mraa 1.2.2		|
