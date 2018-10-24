//This module detects flame sensor data and sends it to a HTTP server by a GET request \
  using a wireless connection. Note this only works with the HTTP protocol.

//From the flame sensor, insert the GND pin to ESP-32S GND pin(Any of them will do), \
  insert the flame sensor '+' pin to the 3.3V pin on the ESP-32S, \
  insert the flame sensot 'DO' pin to the pin 22 in the ESP-32S.

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "<SSID>"; // Insert the wireless network SSID
const char* psswd = "<SSID>"; // Insert the wireless network password
const int SensorDigital = 22;

void setup() {
  Serial.begin(115200);
  pinMode(SensorDigital, INPUT);
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

void loop() {
  String host = "http://192.168.1.16:80/";
  int sensorValue = LOW;

  sensorValue = digitalRead(SensorDigital);
  if(sensorValue==HIGH){
    HTTPClient http;
    Serial.println("Sending message!");
    http.begin(host+"?Fire=1");
    http.GET();
    http.end();
    delay(1000);
  }
}
