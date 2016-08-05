## Lesson 4: I2C LCD

I2c - Pronounced "i-squared-c", stands for "inter-integrated circuit" and is a method of connecting two microcontrollers or other devices using only a minimum of pins. Many microcontrollers, memory chips, and sensors use this protocol to communicate.

You'll need a Grove RGB LCD, two 10kohm resistors, a breadboard, six male-male jumper wires (two red, two black, one yellow, and one white), and a 4-pin JST cable to continue. You can also use the setup on the Grove shield from before, using a Grove RGB LCD, a pair of 4-pin JST connectors, and a Grove I2C ADC, and a few male-male jumper wires.

#### Breadboard
TBA

#### Grove Shield
For Grove shield setup, first connect pin 44 (pin 4 on breakout 2) on Grosse Tete to the 5V pin on your Grove shield. Then connect pin 43 (pin 3 on breakout 2) to any GND pin on your Grove shield. Your Grove shields PWR LED should be lit, if not, make sure that the VCC switch on it is set to 5V. Now, because we’re using I2C connect pin 11 (on breakout 1) to the SDA pin on the Grove shield. Next, you can connect pin 13 (on breakout 1) to the SCL pin on the Grove shield.

Finally, you can set up the LCD. Do so by connecting one of your 4-pin JST connectors to the I2C socket closest to the PWR LED on your Grove shield. Connect the other end of this connector to your LCD screen. And to complete the setup, connect the I2C side of the ADC (Labeled J1) to the I2C socket furthest away from the PWR LED.

(More detail on code coming soon!)

Now ensure to use the proper compiler flags when you attempt to compile this program!
`g++ -I /usr/include/upm -lupm-i2clcd lesson_4.cpp -o lesson_4`
