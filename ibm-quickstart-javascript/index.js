var Client = require("ibmiotf");

var config = {
    "org" : "quickstart",
    "id" : "trial555",
    "type" : "iotsensor"
};

var deviceClient = new Client.IotfDevice(config);
deviceClient.connect();

deviceClient.on("connect", function(){
    periodicActivity(); //call the periodicActivity function
})

var count = 1;

function periodicActivity() //
{
  deviceClient.publish("status","json",'{"d" : {"pir" : ' + count +'}}');
  setTimeout(periodicActivity,1000); //call the indicated function after 1 second (1000 milliseconds)
  if(count == 1){
    count = 0;
  }
  else {
     count = 1;
  }
}