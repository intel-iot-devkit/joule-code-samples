## Lesson 5: Adding Sensors

This lesson uses the same setup from lesson 4, and adds a sensor, as well as functionality to the LCD! Start with your setup from lesson 4, connect a 4-pin JST connector to the other end of your Grove I2C ADC (labeled J2). On the end of this JST connecter, snap a Grove thermometer to it, and you’re done!

(More detail on code coming soon!)

Now ensure to use the proper compiler flags when you attempt to compile this program!
`g++ -I /usr/include/upm -lupm-i2clcd -lupm-adc121c021`
