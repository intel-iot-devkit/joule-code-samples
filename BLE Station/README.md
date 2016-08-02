# BLE station with GT

## Introduction
This BLE station example publishes accelerometer data to the IBM Bluemix IoT cloud and also detects any nearby BLE devices.

## Setup
* Ensure that your GT has been updated with the latest build of Ostro-GT
* Ensure that your GT has internet access after setting up WiFi (i.e. using connman)
* Ensure that Bluetooth has been enabled by using the command:
```
rfkill unblock bluetooth
```

Here is the hardware setup:

![GT setup](gt-setup.jpg)

## Running the code
You can launch this project from XDK, or run it directly on your device:
```
npm install
node index.js
```

## IBM Bluemix IoT
Go to [IBM IoT Quickstart](https://quickstart.internetofthings.ibmcloud.com/#/) and enter your device ID to visualize your accelerometer data.

