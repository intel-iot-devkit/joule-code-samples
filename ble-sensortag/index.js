var util           = require('util');
var async          = require('async');
var getmac         = require('getmac');
var bluemixClient  = require('ibmiotf');
var TISensorTag    = require('sensortag');
var macAddress, deviceClient;

//get MAC address
getmac.getMac(function(err, mac){
    macAddress = mac.replace(/:/g,''); //strip out colons
    connectToBluemix(macAddress);
});

//instantiate client
function connectToBluemix(macAddress){
    deviceClient = new bluemixClient.IotfDevice({
        'org'  : 'quickstart',
        'id'   : macAddress,
        'type' : 'tisensortag'
    });

    deviceClient.on('connect', function(){
            console.log('Connected To Bluemix! Your Device ID is: ' + macAddress);
            console.log('Visit https://quickstart.internetofthings.ibmcloud.com/#/ to visualize your data\n');

            console.log('Discovering TI SensorTag...');
    });

    deviceClient.connect();
}

//format and send JSON to IBM Bluemix IoT
function sendToBluemix(data){
    var msg = {
        d : data
    };
    deviceClient.publish("status","json", JSON.stringify(msg));
}

//discover TI SensorTag and read sensor data
TISensorTag.discover(function(sensorTag){
    console.log('Discovered: ' + sensorTag);

    sensorTag.on('disconnect', function(){
        console.log('disconnected!');
        process.exit(0);
    });

    async.series([
        function(callback){
            console.log('Connecting...');
            sensorTag.connectAndSetUp(callback);
        },
        function(callback){
            console.log('Enabling Humidity & Temperature Sensor...');
            sensorTag.enableHumidity(callback);
        },
        function(callback){
            setTimeout(callback, 2000);
        },
        function readTempAndHumid(callback){
            console.log('Reading:');
            sensorTag.readHumidity(function(error, temperature, humidity){

                console.log('\tTemperature = %d °C', temperature.toFixed(1));
                console.log('\tHumidity    = %d %', humidity.toFixed(1));

                sendToBluemix({
                    temperature: temperature.toFixed(1),
                    humidity: humidity.toFixed(1)
                });

                setTimeout(readTempAndHumid, 1000);
        });
        },
        function(callback){
            console.log('disconnect');
            sensorTag.disconnect(callback);
      }
    ]);
});