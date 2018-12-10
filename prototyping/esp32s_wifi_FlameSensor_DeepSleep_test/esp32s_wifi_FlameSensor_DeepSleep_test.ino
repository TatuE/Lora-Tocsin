//This test makes network connection, detects flame using the flame sensor and send out a http GEt message of the results. \
  after this, the ESP-32S goes to sleep.
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "<ssid>"; // Insert the wireless network SSID
const char* psswd = "<psswd>"; // Insert the wireless network password

const int SensorDigital = 22;
const int sleepTime=60; // time to sleep in seconds
const int mSConverter = 1000000; // The sleep timer works using micro seconds,\
                                    this converts the sleepTime appropriately.
int flameCount=0;
int loopCount=0;
int sensorResult;

String host = "http://0.0.0.0/"; // insert target host, no need to add port (which is 80/tcp in this case)

void setup() {
  delay(500); // it seems there is a bug that prevents the ESP32 waking from deep sleep.\
                 It happens randomly after some reboots have taken place \
                 adding a small delay in the start should prevent this. \
                 This has not occured in this project as of this time.
  Serial.begin(115200);
  delay(1000);
  pinMode(SensorDigital, INPUT);
  wifiConnect();
}

void loop() {
  //The loop is intended to be performed in 10 second intervals. \
    Three flame sensor readings are taken. The result that is send out, is based on a 2/3 (66%) majority from the results. \
    After this, the ESP-32S goes in to deep sleep mode for a predetermined time.
  int sensorValue = LOW;
  sensorValue = digitalRead(SensorDigital);

  if(sensorValue==HIGH){ // if the sensor detects fire, the flamecount adds one
    flameCount++;
  }

  loopCount++;
  delay(3300);

  if(loopCount==3){
    if(WiFi.status() != WL_CONNECTED){
      wifiConnect();
    }

    if(flameCount>=2){
      sensorResult=1; //if the flame count is 2 or higher, the return value is 1(true).
    }else{
      sensorResult=0; //else the return value is 0(false).
    }

    HTTPClient http;
    Serial.println("Sending message!");
    http.begin(host+"?Fire="+String(sensorResult)); // prepare the http message.
    http.GET(); // send the http message using GET
    http.end();
    sleep();
  }
}

void wifiConnect(){
  WiFi.begin(ssid, psswd); // use the credentials for wifi login.

  while (WiFi.status() != WL_CONNECTED) { //while loop is as long there is no connection made.
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  delay(500);
  Serial.println("");
  delay(500);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //print network ip address.
}

void sleep(){
  esp_sleep_enable_timer_wakeup(sleepTime*mSConverter); // define the wakeup timer (time to sleep).
  Serial.println("Sleeping for "+String(sleepTime)+" seconds.");
  Serial.println("Going to sleep.");
  delay(500);
  esp_deep_sleep_start();  // start the deep sleep
}
