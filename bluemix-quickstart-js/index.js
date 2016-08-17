/*
* Copyright (c) 2015 - 2016 Intel Corporation.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
* LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
