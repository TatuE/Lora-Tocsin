//This module detects flame sensor data and sends it to a HTTP server by a GET request \
  using a wireless connection. Note this only works with the HTTP protocol.

//From the flame sensor, insert the GND pin to ESP-32S GND pin(Any of them will do), \
  insert the flame sensor '+' pin to the 3.3V pin on the ESP-32S, \
  insert the flame sensot 'DO' pin to the pin 22 in the ESP-32S.

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "<ssid>"; // Insert the wireless network SSID
const char* psswd = "<psswd>"; // Insert the wireless network password

String loraUid = "LoraA01";
int sensorValue = 1;

void setup() {
  Serial.begin(115200);
  wifiConnect();
}

void loop() {

    if(WiFi.status() != WL_CONNECTED){
      wifiConnect();
    }
  
    String host = "http://0.0.0.0/";  // host address
    HTTPClient http;
    Serial.println("Sending message!");
    http.begin(host+"/Lora-Tocsin/AddSensorData?loraUid="+loraUid+"&sensorValue="+String(sensorValue));
    Serial.println("/Lora-Tocsin/AddSensorData?loraUid="+loraUid+"&sensorValue="+String(sensorValue));
    http.GET();
    http.end();
    delay(1000); 
}

void wifiConnect(){
  WiFi.begin(ssid, psswd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  delay(500);
  Serial.println("");
  delay(500);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
