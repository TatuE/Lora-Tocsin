//This module detects flame sensor data and sends it to a host using a get request \

//From the flame sensor, insert the GND pin to ESP-32S GND pin(Any of them will do), \
  insert the flame sensor '+' pin to the 3.3V pin on the ESP-32S, \
  insert the flame sensot 'DO' pin to the pin 22 in the ESP-32S.

#include <WiFi.h>

const char* ssid = "<ssid>"; // Insert the wireless network SSID
const char* psswd = "<passwd>"; // Insert the wireless network password
const char* server = "0.0.0.0"; // Inser the server ip address or fully qualified domain name (FQDN)
const int serverPort = 8080; // Insert the server port to be used
const int SensorDigital = 22;

String loraUid = "LoraA01";
int sensorValue = 1;

void setup() {
  delay(1000);
  Serial.begin(115200);
  wifiConnect();
}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    wifiConnect();
  }

  WiFiClient client;
  int wifiCount=0;
  while(!client.connect(server, serverPort)){
    Serial.println("Connecting to server..");
    wifiCount++;
    if(wifiCount==5){
     Serial.println("Connection to server failed!");
     delay(1000);
     return;
    }
  }
  Serial.println("Connected to server!");
  delay(500);
  Serial.println("Sending message!");
  client.print(String("GET /Lora-Tocsin/AddSensorData?loraUid="+loraUid+"&sensorValue="+String(sensorValue)+" HTTP/1.1"));
  client.stop();
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
