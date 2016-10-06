## Lesson 4: I2C

I2C - Pronounced "i-squared-c", stands for "inter-integrated circuit" and is a method of connecting two microcontrollers or other devices using only a minimum of pins. Many microcontrollers, memory chips, and sensors use this protocol to communicate.

You'll need a Grove RGB LCD, two 10k ohm resistors, a breadboard, eight male-male jumper wires (two red, two black, two yellow, and two white), and a 4-pin JST cable to continue. You can also setup this circuit on the Grove shield from before, using a Grove RGB LCD, a pair of 4-pin JST connectors, and a Grove I2C ADC, and four male-male jumper wires.

**Remeber to power down your Joule board _before_ making these connections!**

### Breadboard

1. Connect a red jumper wire between;
	* Pin 44 (pin 4 on the Joule's JI3/Breakout #2 IO rail)
	* The positive rail of your breadboard
2. Connect a black jumper wire between;
	* Pin 43 (pin 3 on the Joule's JI3/Breakout #2 IO rail)
	* The negative rail of your breadboard
3. Connect a 10k resistor between;
	* The positive rail of your breadboard
	* An empty column on your breadboard
4. Connect a white jumper wire between;
	* Pin 11 (on the Joule's JI2/Breakout #1 IO rail)
	* The column you just attached a resistor to on your breadboard
5. Connect a white jumper wire between;
	* The column you just attached pin 11 to on your breadboard
	* The white cable on the 4-pin JST connector
6. Connect a 10k resistor between;
	* The positive rail of your breadboard
	* An empty column on your breadboard
7. Connect a yellow jumper wire between;
	* Pin 13 (on the Joule's JI2/Breakout #1 IO rail)
	* The column you just attached a resistor to on your breadboard
8. Connect a yellow jumper wire between;
	* The column you just attached pin 13 to on your breadboard
	* The yellow cable on the 4-pin JST connector
9. Connect a red jumper wire between;
	* The positive column on your breadboard
	* The red cable on the 4-pin JST connector
10. Connect a black jumper wire between;
	* The negative rail on your breadboard
	* The black cable on the 4-pin JST connector
11. Connect the open end of the 4-pin JST connector to;
	* The J1 socket on your Grove LCD
	

### Grove Shield

1. Connect a jumper wire between;
	* Pin 44 (pin 2 on the Joule's JI3/Breakout #2 IO rail)
	* The 5V pin on your Grove shield
2. Connect a jumper wire between;
	* Pin 43 (pin 1 on the Joule's JI3/Breakout #2 IO rail)
	* Any of the GND pins on your Grove shield
3. Ensure that the PWR LED on the Grove shield is on, if it isn't;
	* Ensure that the VCC switch is set to 5V
4. Connect a jumper wire between;
	* Pin 11 (on the Joule's JI2/Breakout #1 IO rail)
	* The SDA pin on your Grove shield
5. Connect a jumper wire between;
	* Pin 13 (on the Joule's JI2/Breakout #1 IO rail)
	* The SCL pin on your Grove shield
6. Connect a 4-pin JST connector between;
	* The I2C socket closest to your PWM LED
	* The J1 socket on your Grove LCD
7. Connect a 4-pin JST connector between;
	* The I2C socket furthest away from your PWM LED
	* The J1 socket on your Grove I2C ADC
	
![Lesson 4 diagram](https://raw.githubusercontent.com/intel-iot-devkit/joule-code-samples/master/exploring-cpp/lesson_4_i2c/cpp/lesson_4_diagram.jpg "Lesson 4 diagram")

### The Code

The first thing we do in this code, is define two variables. These global variables are the I2C addresses of the LCD and its RGB backlight. If you aren't using a Grove RGB LCD, than you will need to change these to the proper addresses for your specific device. This way of defining things allows you to only have to change one line of code to allow the program to interact with something completely different.

Next we add another include, which is a UPM library, specifically made for the Grove LCD. As before, we create an object to hold our output device. Though this time, instead of PWM or GPIO it's a device specifically made for the LCD. Next we instantiate the I2C LCD with the following values; 0 for I2C bus 0 which is the bus that we plugged wires into, and the I2C addresses we created with the define statements.

Next we set a trio of integer variables in order to allow us to set the color or the backlight. We then use one of our LCD object's functions to set the LED backlight. Now we use another one of our LCD object's functions to set the cursor position to the top left corner of the screen, at position 0, 0. Finally we use the write function to write the string `Hello world` on the LCD screen.

Now we just print out `Press ctrl+c to exit...` on the console and loop until they press ctrl+c!

Now ensure to use the proper compiler flags when you attempt to compile this program!

`g++ -I /usr/include/upm -lupm-i2clcd lesson_4.cpp -o lesson_4`

Now run the program using the following command.

`./lesson_4`

### Troubleshooting

Upon running the code, your LCD should turn purple, and read `Hello world` on it. 

If you get an error similar to `Could not initialize LCD controller` then that means you aren't pulling the logic voltage up properly. If you're using the Grove shield make sure that the I2C ADC is connected on the right end (J1 Port), and connected at the end of the I2C bus (farthest away from the power LED). If you're using a breadboard, ensure that your 10k ohm resistors are going between your 5V line and your SDA and SCL cables. They have to be separate resistors in order to keep the lines separate, and communication clear.

If you get an error similar `Lost arbitration` then it means some communication is going wrong with your I2C device. Usually this is caused by a wire being shorted, or not having contact all of the time. Be sure to check your connections, and make sure none of them are crossed/shorted. Once you do that, feel free to re-run the program and it should be fixed. 

If you get an error with something saying `upm::Jhd1313m1 *lcd is not declared in this scope` during compiling, it could mean a few things. Generally it means you've forgotten to use, or misspelled the `-lupm-i2clcd` compiler flag. It can also mean that you misspelled one of the functions within the program. Just check your spelling and try compiling the program again.

### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|
|:---------------------:|:-----------------:|:-----------------:|
|	Ostro 166			|Intel Stock Board	|	mraa 1.2.3		|
|	Ostro 166 			|Intel Stock Board	|	mraa 1.2.2		|
