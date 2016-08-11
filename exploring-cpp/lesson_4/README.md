## Lesson 4: I2C

I2C - Pronounced "i-squared-c", stands for "inter-integrated circuit" and is a method of connecting two microcontrollers or other devices using only a minimum of pins. Many microcontrollers, memory chips, and sensors use this protocol to communicate.

You'll need a Grove RGB LCD, two 10kohm resistors, a breadboard, six male-male jumper wires (two red, two black, one yellow, and one white), and a 4-pin JST cable to continue. You can also setup this circuit on the Grove shield from before, using a Grove RGB LCD, a pair of 4-pin JST connectors, and a Grove I2C ADC, and four male-male jumper wires.

#### Breadboard
TBA

#### Grove Shield
For Grove shield setup, first connect pin 44 (pin 4 on breakout 2) on Joule to the 5V pin on your Grove shield. Then connect pin 43 (pin 3 on breakout 2) to any GND pin on your Grove shield. Your Grove shields PWR LED should be lit, if not, make sure that the VCC switch on it is set to 5V. Now, because we’re using I2C, connect pin 11 (on breakout 1) to the SDA pin on the Grove shield. Next, you can connect pin 13 (on breakout 1) to the SCL pin on the Grove shield.

Finally, you can set up the LCD. Do so by connecting one of your 4-pin JST connectors to the I2C socket closest to the PWR LED on your Grove shield. Connect the other end of this connector to your LCD screen. And to complete the setup, connect the I2C side of the ADC (Labeled J1) to the I2C socket furthest away from the PWR LED.

#### The Code

The first thing we do in this code, is define two variables. These global variables are the I2C addresses of the LCD and its RGB backlight. If you aren't using a Grove RGB LCD, than you will need to change these to the proper addresses for your specific device. This way of defining things allows you to only have to change one line of code to allow the program to interact with something completely different.

Next we add another include, which is a UPM library, specifically made for the Grove LCD. As before, we create an object to hold our output device. Though this time, instead of PWM or GPIO it's a device specifically made for the LCD. Next we instantiate the I2C LCD with the following values; 0 for I2C bus 0 which is the bus that we plugged wires into, and the I2C addresses we created with the define statements.

Next we set a trio of integer variables in order to allow us to set the color or the backlight. We then use one of our LCD object's functions to set the LED backlight. Now we use another one of our LCD object's functions to set the cursor position to the top left corner of the screen, at position 0, 0. Finally we use the write function to write the string `Hello world` on the LCD screen.

Now we just print out `Press ctrl+c to exit...` on the console and loop until they press ctrl+c!

Now ensure to use the proper compiler flags when you attempt to compile this program!

`g++ -I /usr/include/upm -lupm-I2Clcd lesson_4.cpp -o lesson_4`

#### Troubleshooting

Upon running the code, your LCD should turn purple, and read `Hello world` on it. 

If you get an error similar to `Could not initialize LCD controller` then that means you aren't pulling the logic voltage properly. If you're using the Grove shield make sure that the I2C ADC is connected on the right end (J1 Port), and connected at the end of the I2C bus (farthest away from the power LED). If you're using a breadboard, ensure that your 10k ohm resistors are going between your 5V line and your SDA and SCL cables. They have to be separate resistors in order to keep the lines separate, and communication clear.

If you get an error similar `Lost arbitration` then it means some communication is going wrong with your I2C device. Usually this is caused by a wire being shorted, or not having contact all of the time. Be sure to check your connections, and make sure none of them are crossed/shorted. Once you do that, feel free to re-run the program and it should be fixed. 

If you get an error with something saying `upm::Jhd1313m1 *lcd is not declared in this scope` during compiling, it could mean a few things. Generally it means you've forgotten to use, or misspelled the `-lupm-adc121c021` compiler flag. It can also mean that you misspelled one of the functions within the program. Just check your spelling and try compiling the program again.