## Lesson 3: PWM
In the last lessons, you learned how to format a C++ program, and how to use a GPIO pin of the Grosse Tete or Edison. In this lesson, we'll cover the basics of PWM, or Pulse Width Modulation. This is a way of simulating analog output in digital circuits. For this lesson, you'll need a small breadboard, a few jumper wires, any basic low-intensity LED, and a resistor of roughly 220ohm to limit the current. You could also use a Grove Shield, combined with an LED module (with LED), one of the 4 pin JST connectors and a few jumper wires.

#### Breadboard
Connect pin 32 (on breakout 1) to one of the rows on your breadboard. Connect one leg of the resistor to another spot on that row, and the other leg to a spot on another row of the breadboard. Connect a second jumper to that same row, then connect the other end of that jumper to pin 36.

#### Grove Shield
Connect pin 44 (Number 4 on breakout 2) to the 5V pin on your shield. Now, connect pin 43 (Number 3 on breakout 2) to any one of the GND pins on your shield. Make sure that the LED on the shield is on at this point, if it isn’t make sure the VCC switch is set to 5V. Now you can connect the PWM line, do so by connecting pin 32 (on breakout 1) to digital pin number 2 on the shield. Next, connect the 4-pin JST connecter to D2, then to the port on the LED module. Finally, you can pop the LED onto the module, ensuring that the longer leg of the LED is on the side marked with a “+”.

As before, we instantiate an object, but this time it’s a PWM object instead of a GPIO object. The program continues upon successful building of the object. This pin is then enabled, in order to allow for proper PWM. It runs the main loop forever, until Ctrl+c is pressed. The loop goes through the values 0.01 and 1 by 0.01 and write the value to the PWM pin at each iteration. It then loops through the values backwards.

#### The Code

It should cause the LED to glow brighter then dimmer through the iterations. Finally if the PWM object fails to be created, it’s deleted and the program returns 1, allowing you to know that it errored out.

Now ensure to use the proper compiler flags when you attempt to compile this program!

`g++ -lmraa lesson_3.cpp -o lesson_3`

Running the program should make the LED you attached glow, dimly at first before getting brighter, then fading back out. If it doesnt, check your wiring and the polarity of your LED. Finally if it still doesnt work, enter the following command to find out what version of Mraa you have.

`mraa-gpio version`

If it returns a version that's less than 1.2.1 then you need to update your copy of Mraa to the latest version. Follow the instructions here.

[//]: # (Insert link to installing mraa on GT)