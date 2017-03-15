# BLE station with Intel® Joule development platform

## Introduction
This BLE station example publishes accelerometer data and temperature and humidity from a TI SensorTag to the IBM Bluemix IoT cloud..

## Required Hardware
* TI SensorTag (CC2650), make sure it is turned on
* Grove Shield
* Grove LCD
* Grove 3-axis accelerometer
* 5 male to male wires

## Setup
* Ensure that your Intel® Joule Module has been updated with the latest build of Ostro-XT
* Ensure that your Intel® Joule Module has internet access after setting up WiFi (i.e. using connman)
* Ensure that Bluetooth has been enabled by using the command:
```
rfkill unblock bluetooth
```

Here is the hardware setup:

Connect male to male wires from the headers on the Intel® Joule Module to the grove shield, as shown below

![table](connection_table.jpg)

![table](breakout_1.jpg)

![table](breakout_2.jpg)

Then plug in the LCD screen to the grove shield on the I2C connector closest to the A0 connector, and the 3-axis accelerometer to the second I2C port. **make sure you turn your board off and on , I2C only detects on boot, so if you don't turn on your board with the LCD and accelerometer plugged in it won't detect them** You need to connect them in this order because the Intel® Joule Module board does not have pull up resistors, and the 3-axis accelerometer has them.

![lcd_accel](lcd_accel.jpg)


## Running the code
You can launch this project from XDK (after first importing it from XDK IoT Edition), or run it directly on your device:

When running directly on your device, please note that mraa library requires root privileges to run properly. So either
check that you are logged in as user `root` (`whoami` command will tell you) or use `sudo` command to run this app.

```
npm install
node index.js
```
![console output](console.png)


## IBM Bluemix IoT
Go to [IBM IoT Quickstart](https://quickstart.internetofthings.ibmcloud.com/#/) and enter your device ID to visualize your accelerometer data.

In order to change your device ID, see the Set your Device ID section of the IBM Quickstart Javascript tutorial https://github.com/intel-iot-devkit/joule-code-samples/tree/master/ibm-quickstart-javascript#set-your-device-id

![data visualizatin on IBM Bluemix IoT](bluemix.png)

