## Lesson 5: Adding Sensors

This lesson uses the same setup from the Grove shield setup of lesson 4, and adds a sensor, as well as functionality to the LCD!

**Remeber to power down your Joule board _before_ making these connections!**

### Hardware

1. Set up your Grove shield as detailed in Lesson 4
2. Connect a 4-pin JST connector between;
	* The input end of the Grove I2C ADC (labeled J2)
	* The Grove temperature sensor

### The Code

This time, we define another address at the top of the program. This address is for the I2C ADC (Analog-to-Digital Converter). This is used to convert the analog value from our temperature sensor, to a normal I2C data stream. We also include a few new things. The first new include is the header file for interacting with the ADC. Next is `iomanip` which simply lets us format our output strings to be nice. Next we include `sstream` which allows us to make small streams of data to work with. Finally, we include `cmath` which gives us access to all sorts of mathematical functions.

Now we declare our objects, including a new ADC object, allowing us to read from our analog sensor. We then create a new instance of the class, feeding it hub 0 as before, as well as the ADC address variable we made earlier. We also add that object to our standard signal handler destructor. Now we set the color of the LCD to green to start with. 

After this, we generate a new variable used to hold the resistance value of the analog sensor hooked into the ADC. The value on the ADC ranges between 0 and 4095. We use the type `unsigned int` in order to ensure that the variable can never be negative. This type of variable takes any integer and only store the absolute value of it. Before this coming while loop, we set the cursor back to 0,0 on the LCD and write out the phrase `Temperature:` on it, allowing us to not have to rewrite it every time.

Now we enter a while loop, that will go until someone presses ctrl+c as before. Within the loop, the first thing we do is pull the current value from the thermometer, and put it in the resistance variable that we created earlier. Now we use that value to calculate the temperature. The code uses known values of our thermistor to perform the proper mathematical operations on the resistance value to achieve a useable temperature value. Every sensor has its own values, which generally can be found in the thermistor's datasheet. We assign the value of this operation to a new variable called `temperature`.

The output is currently in Celsius, and can now be used in output! To begin, we create a stream using the data we processed from the thermistor. This allows us to set the significant digits of our temperature reading rather easily. Doing so simply requires that we feed the string stream `setprecision(2)` with 2 being the number of digits after the decimal place we want. Then we feed it the term `fixed` to make the number fixed point. Finally we give it our floating point temperature variable.

We then set the cursor to 1,1 in order to make sure we aren't overwriting the `Temperature:` that we wrote to it earlier. We then create a character string, made from our string stream. We then write this out to our LCD to give out the current temperature.

Now we use a series of "if then else" statements to set the LCDs color based on the temperature its feeling. Finally, we do our standard clean up at the end of the program in case something goes wrong.

Now ensure to use the proper compiler flags when you attempt to compile this program!

`g++ -I /usr/include/upm -lupm-i2clcd -lupm-adc121c021`

Now run the program using the following command. Please also note that mraa library requires root privileges to run properly. So either check that you are logged in as user `root` (`whoami` command will tell you) or use `sudo` command to run this example.

`./lesson_5`

### Troubleshooting

When you run the program, you should see the screen light up green with the words "Temperature: " and some value after it. The value should go up and down as you hold the temperature sensor and release it.

If you get an error similar to `Could not initialize LCD controller` then that means you aren't pulling the logic voltage properly. If you're using the Grove shield make sure that the I2C ADC is connected on the right end (J1 Port), and connected at the end of the I2C bus (farthest away from the power LED). If you're using a breadboard, ensure that your 10k ohm resistors are going between your 5V line and your SDA and SCL cables. They have to be separate resistors in order to keep the lines separate, and communication clear.

If you get an error similar `Lost arbitration` then it means some communication is going wrong with your I2C device. Usually this is caused by a wire being shorted, or not having contact all of the time. Be sure to check your connections, and make sure none of them are crossed/shorted. Once you do that, feel free to re-run the program and it should be fixed. 

If you get an error with something saying `upm::ADC121C021 *adc is not declared in this scope` during compiling, it could mean a few things. Generally it means you've forgotten to use, or misspelled the `-lupm-adc121c021` compiler flag. It can also mean that you misspelled one of the functions within the program. Just check your spelling and try compiling the program again.

For either of the above issues, you might also need to ensure that you're using the `-I /usr/include/upm` compiler flag.

### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|
|:---------------------:|:-----------------:|:-----------------:|
|	Ostro 166			|Intel Stock Board	|	mraa 1.2.3		|
|	Ostro 166 			|Intel Stock Board	|	mraa 1.2.2		|