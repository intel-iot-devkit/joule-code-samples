## Lesson 8: Multithreading

Most of this code is easily recognizable from that of Lesson 7. In this lesson, however, we're going to make it multithreaded, and add in a Crow webserver to allow the user to turn the system on and off, as well as to set its temperature.

**Remeber to power down your Joule board _before_ making these connections!**

### The Hardware

1. Set up your Grove shield as detailed in Lesson 7

### The Code

This combines the code from lesson 7 with some of the code of lesson 6. The `devices.h` and `devices.cpp` files are the same from lesson 7, which just proves how handy it is to write classes! To begin, you can notice that we start with `thread_function` which does everything that the main function from lesson 7 did. We create it in this function in order to multithread the program! We then create our standard `sig_handler` function, before creating a few variables that all of our functions need access to. 

We then go into our main statement. This statement creates a thread named `t1` which runs our `thread_function` from earlier in its own thread. This allows the program to work on other things as the loop executes. We then create our crow page, which displays the target temperature and system state. The user can then change it, which will change the variables we set above the main statement for the loop to access. Now we start the app on port 80, and tell our thread to join the one we started earlier. This simply makes the thread safe to delete when the time comes.

Now ensure to use the proper compiler flags when you attempt to compile this program!

`g++ -I /usr/include/upm -std=c++11 lesson_8.cpp devices.cpp -o lesson_8 -lupm-i2clcd -lupm-adc121c021 -lmraa -lpthread -lboost_system`

Now run the program using the following command.

`./lesson_8`

### Troubleshooting

Upon running the code, the LCD should light up, showing the target and current temperatures. Changing the temperature to a degree above or below the target temperature should activate one of the relays.

If you get an error similar to `Could not initialize LCD controller` then that means you aren't pulling the logic voltage properly. If you're using the Grove shield make sure that the I2C ADC is connected on the right end (J1 Port), and connected at the end of the I2C bus (farthest away from the power LED). If you're using a breadboard, ensure that your 10k ohm resistors are going between your 5V line and your SDA and SCL cables. They have to be separate resistors in order to keep the lines separate, and communication clear.

If you get an error similar `Lost arbitration` then it means some communication is going wrong with your I2C device. Usually this is caused by a wire being shorted, or not having contact all of the time. Be sure to check your connections, and make sure none of them are crossed/shorted. Once you do that, feel free to re-run the program and it should be fixed. 

If you get an error with something saying `upm::ADC121C021 *adc is not declared in this scope` during compiling, it could mean a few things. Generally it means you've forgotten to use, or misspelled the `-lupm-adc121c021` compiler flag. It can also mean that you misspelled one of the functions within the program. Just check your spelling and try compiling the program again.

If you get an error with something saying `upm::Jhd1313m1 *lcd is not declared in this scope` during compiling, it could mean a few things. Generally it means you've forgotten to use, or misspelled the `-lupm-i2clcd` compiler flag. It can also mean that you misspelled one of the functions within the program. Just check your spelling and try compiling the program again.


For any of the above issues, you might also need to ensure that you're using the `-I /usr/include/upm` compiler flag.

If you can't access your webserver there are a few problems that can generally happen. First, you must make sure that your device is on the same network as your board. Finally, ensure that your board's ports are correctly opened. Do so by running the following code.

```bash
iptables -F
iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -S
```

This should set everything up properly.

If you get an error similar to `undefined reference to Devices::` then you forgot to include `devices.cpp` in your compiler flags.

### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|
|:---------------------:|:-----------------:|:-----------------:|
|	Ostro 166			|Intel Stock Board	|	mraa 1.2.3		|
|	Ostro 166 			|Intel Stock Board	|	mraa 1.2.2		|
