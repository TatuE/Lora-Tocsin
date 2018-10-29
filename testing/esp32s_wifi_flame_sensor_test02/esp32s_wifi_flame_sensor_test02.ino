//This module detects flame sensor data and sends it to a host using a get request \

//From the flame sensor, insert the GND pin to ESP-32S GND pin(Any of them will do), \
  insert the flame sensor '+' pin to the 3.3V pin on the ESP-32S, \
  insert the flame sensot 'DO' pin to the pin 22 in the ESP-32S.

#include <WiFi.h>

const char* ssid = "<SSID>"; // Insert the wireless network SSID
const char* psswd = "<PASSWORD>"; // Insert the wireless network password
const char* server = "<SERVER/HOST>"; // Inser the server ip address or fully qualified domain name (FQDN)
const int serverPort = <SERVER/HOST PORT>; // Insert the server port to be used
const int SensorDigital = 22;

void setup() {
  Serial.begin(115200);
  pinMode(SensorDigital, INPUT);
  wifiConnect();
}

void loop() {
  int sensorValue = LOW;

  sensorValue = digitalRead(SensorDigital);
  if(sensorValue==HIGH){
    WiFiClient client;
    if(!client.connect(server, serverPort)){
      Serial.println("Connection to server failed!");
        delay(1000);
        return;
    }
    Serial.println("Connected to server!");
    delay(500);
    Serial.println("Sending message!");
    client.print(String("GET /?Fire=1 HTTP/1.1"));
    client.stop();
  }

  if(WiFi.status() != WL_CONNECTED){
    wifiConnect();
  }
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
