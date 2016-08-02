var LCD            = require('jsupm_i2clcd');
var accelerometer  = require('jsupm_mma7660');
var bluemixClient  = require('ibmiotf');
var async          = require('async');
var noble          = require('noble');
var getmac         = require('getmac');
var macAddress, sensorTag, deviceClient;

//instantiate LCD
var myLcd = new LCD.Jhd1313m1 (0, 0x3E, 0x62);
myLcd.setColor(53, 39, 249); //blue

//instantiate accelerometer
var myAccelerometer = new accelerometer.MMA7660(accelerometer.MMA7660_I2C_BUS, accelerometer.MMA7660_DEFAULT_I2C_ADDR);
myAccelerometer.setModeStandby();
myAccelerometer.setSampleRate(accelerometer.MMA7660.AUTOSLEEP_64);
myAccelerometer.setModeActive();

var x, y, z;
x = accelerometer.new_intp();
y = accelerometer.new_intp();
z = accelerometer.new_intp();

//instantiate BLE, make sure you enable BT with 'rfkill unblock bluetooth'
noble.on('stateChange', function(state){
	if(state === 'poweredOn'){
		noble.startScanning();
		console.log('Scanning for BLE peripherals...');
	}else{
		noble.stopScanning();
	}
});

noble.on('discover', function(peripheral){
	console.log('Found BLE Device: [' + peripheral.id + '] ' + peripheral.advertisement.localName);
	if(peripheral.advertisement.localName == 'CC2650 SensorTag'){
		console.log('Found TI SensorTag!');
	}
});

//get MAC address
getmac.getMac(function(err, mac){
	macAddress = mac.replace(/:/g,''); //strip out colons
	myLcd.setCursor(0,0);
	myLcd.write('ID: ' + macAddress); 
	connectToBluemix(macAddress);
});

//instantiate client
function connectToBluemix(macAddress){
	deviceClient = new bluemixClient.IotfDevice({
		'org'  : 'quickstart',
		'id'   : macAddress,
		'type' : 'sensor'
	});

	deviceClient.on('connect', function(){
        	console.log('Connected To Bluemix! Your Device ID is: ' + macAddress);
        	console.log('Visit https://quickstart.internetofthings.ibmcloud.com/#/ to visualize your data');
        	publishData();
	});

	deviceClient.connect();
}

//publish data to IBM Bluemix IoT
function publishData()
{
  var accelerometerData = getAccelerometerData();
  var msg = {
    d : {
    	x: accelerometerData.x,
    	y: accelerometerData.y,
    	z: accelerometerData.z,
    	sensorTag: sensorTag
    }
  };
  deviceClient.publish("status","json", JSON.stringify(msg));
  setTimeout(publishData,1000); //recursively call and publish data
}

//get accelereometer data
function getAccelerometerData(){
	myAccelerometer.getRawValues(x, y, z);
	return {
		x: accelerometer.intp_value(x),
		y: accelerometer.intp_value(y),
		z: accelerometer.intp_value(z)
	}
}

// on exit
process.on('SIGINT', function()
{
	// clean up memory
	accelerometer.delete_intp(x);
	accelerometer.delete_intp(y);
	accelerometer.delete_intp(z);

	myAccelerometer.setModeStandby();
	console.log("Exiting...");
	process.exit(0);
});

