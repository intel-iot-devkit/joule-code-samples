## Lesson 7: Classes and Encapsulation

In this lesson, we use some new techniques to create classes of our own, breaking our program into smaller, easier-to-digest pieces. Each of these classes holds its own data, and handles all of its own input and output. This makes them much simpler to use. We also use a new device: A relay. A relay is an electromechanical device that switches a high-current device on and off using a low-current digital signal. This lesson will create a temperature control system which will keep an office or home at 22degC (72degF) or within one degree of it on either side.

### The Hardware

1. Set up your Grove shield as detailed in Lesson 4
2. Connect a jumper wire between;
	* Pin 2 (on the Joule's JI2/Breakout #1 IO rail)
	* Pin 2 on the digital rail of the Grove shield
3. Connect a jumper wire between;
	* Pin 4 (on the Joule's JI2/Breakout #1 IO rail)
	* Pin 4 on the digital rail of the Grove shield
4. Connect a 4-pin JST connector between;
	* The input end of the Grove I2C ADC (labeled J2)
	* The Grove temperature sensor
5. Connect a 4-pin JST connector between;
	* The D2 socket of your Grove shield
	* A Grove relay (or a Grove LED module, ensure it has an LED in it)
6. Connect a 4-pin JST connector between;
	* The D4 socket of your Grove shield
	* A Grove relay

### The Code

This lesson includes several files, including `devices.h` and `devices.cpp` which are called class files. The code within them helps our main program `lesson_7.cpp` and allows us to put encapsulate functions and objects within their own files. Let's begin exploring `devices.h` and `devices.cpp` first!

#### Devices

`Devices.h` is what's called a header file. It provides definitions for use later on in the `devices.cpp` file. As you can see, we set some I2C addresses to use further on, you can change them here and the rest of the program will use the updated addresses! After that, we do our normal include libraries for working with I2C and mraa. Now we jump into the class itself. We define objects for the ADC, LCD, and the two relays. These are private objects, meaning that an outside class can't actually directly access these objects. Normal C++ variables can be given the same treatment within a class.

Now we define a few things as public, that way they can be accessed by any outside class that includes `devices.cpp`. The first thing defined is `Devices();`. This is called an empty, or default, constructor. This allows you to build a default object, whose attributes can be manipulated later. We also create a constructor which requires input to run, by default it has input already, but you can always change it when you call it. Next, we make a copy constructor, which is used to allow us to work with the object later. Now we make the destructor `~Devices();` which deletes the object once it goes out of the scope of the class.

Now we generate our functions, which are used to manipulate the object we create. We start with `void display(int row, int col, std::string str);`. This function is used to print something out to our LCD screen, using the row. column and string we provide. Next we create a function called clear, which we use to simply clear the LCD. Now `color(int r, int g, int b);` which is used to set the r, g, b values on the backlight of the LCD. Now we create a function which grabs the value of our thermometer, transforming it into a meaningful value of degrees Celsius, before returning that value to whatever called it. Finally, there are two functions; `setAc` and `setHtr` which can be used to turn on and off the relays attached to pins 2 or 4.

You can explore the `devices.cpp` file on your own, and view exactly how we interact with our I2C and GPIO devices!

#### lesson_7.cpp

Firstly, we define two new things, one being a buffer, that will tell the system how far away from its' target temperature it can go. The next one simply sets a variable to use as the refresh rate of the LCD screen. We also include our `devices.h` file. You can also notice we aren't using namespace standard anymore, which means we have to add `std::` to the beginning of some functions.

Now, in our main statement, we create an object, of the type `Devices` called devices, with our current settings defined above. We also create two float variables, one called `set`, which is the temperature our system will aim for, and `cur` which is the current temperature. We also make two Boolean variables, one which decides the mode (AC or Heater), and one which tells the program whether the heating or cooling system is on or not.

We then create a loop, which repeats until the user enters ctrl+c. Firstly it clears the LCD of any content it had on it before. It then writes "Target :" and the target temperature, before retrieving and displaying the current temperature.

Now we go through a series of "if then else" statements. These statements detect how far away the current temperature is from the target temperature. The program then takes the appropriate action to keep the current temperature within one degree of either side of the target temperature. It uses the functions we created in `devices.h` and `devices.cpp` to manipulate our `devices` object, to keep close to its' target temperature. We then sleep the system for whatever refresh rate you set earlier before looping again!

Now ensure to use the proper compiler flags when you attempt to compile this program!

`g++ -I /usr/include/upm -lupm-i2clcd -lupm-adc121c021 -lmraa -std=c++11 lesson_7.cpp devices.cpp -o lesson_7`

### Troubleshooting

Upon running the code, the LCD should light up, showing the target and current temperatures. Changing the temperature to a degree above or below the target temperature should activate one of the relays.

If you get an error similar to `Could not initialize LCD controller` then that means you aren't pulling the logic voltage properly. If you're using the Grove shield make sure that the I2C ADC is connected on the right end (J1 Port), and connected at the end of the I2C bus (farthest away from the power LED). If you're using a breadboard, ensure that your 10k ohm resistors are going between your 5V line and your SDA and SCL cables. They have to be separate resistors in order to keep the lines separate, and communication clear.

If you get an error similar `Lost arbitration` then it means some communication is going wrong with your I2C device. Usually this is caused by a wire being shorted, or not having contact all of the time. Be sure to check your connections, and make sure none of them are crossed/shorted. Once you do that, feel free to re-run the program and it should be fixed. 

If you get an error with something saying `upm::ADC121C021 *adc is not declared in this scope` during compiling, it could mean a few things. Generally it means you've forgotten to use, or misspelled the `-lupm-adc121c021` compiler flag. It can also mean that you misspelled one of the functions within the program. Just check your spelling and try compiling the program again.

If you get an error with something saying `upm::Jhd1313m1 *lcd is not declared in this scope` during compiling, it could mean a few things. Generally it means you've forgotten to use, or misspelled the `-lupm-i2clcd` compiler flag. It can also mean that you misspelled one of the functions within the program. Just check your spelling and try compiling the program again.


For any of the above issues, you might also need to ensure that you're using the `-I /usr/include/upm` compiler flag.

If you get an error similar to `undefined reference to Devices::` then you forgot to include `devices.cpp` in your compiler flags.

### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|
|:---------------------:|:-----------------:|:-----------------:|
|	Ostro 166			|Intel Stock Board	|	mraa 1.2.3		|
|	Ostro 166 			|Intel Stock Board	|	mraa 1.2.2		|