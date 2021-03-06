// This is a wifi login test for the ESP-32S. Updated with a login method. \
  It attemps to log in and prints the acquired ip address

#include <WiFi.h>

const char* ssid = "<SSID>"; // Insert the wireless network SSID
const char* psswd = "<PASSWORD>"; // Insert the wireless network password

void setup() {
  Serial.begin(115200);
  wifiConnect();
}

void loop() {
  Serial.println(WiFi.localIP());
  delay(1000);

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Lost WiFi connection!");
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
