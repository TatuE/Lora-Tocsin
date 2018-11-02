// This is a wifi connection failure test for the ESP-32S \
   If the connection is lost, reconnect is attempted.	
#include <WiFi.h>

const char* ssid = "<SSID>"; // Insert the wireless network SSID
const char* psswd = "<PASSWORD>"; // Insert the wireless network password

void setup() {
  Serial.begin(115200);
  wifiConnect();
}

void loop() {
  

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Lost WiFi connection!");
    Serial.println("");
    wifiConnect();
  }

}

void wifiConnect(){
  WiFi.begin(ssid, psswd);

  Serial.println("Connecting to WiFi..");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   
  }

  Serial.println("Connected to the WiFi network");
  delay(500);
  Serial.println("");
  delay(500);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}
