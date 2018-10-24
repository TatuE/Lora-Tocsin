// This is a basic wifi login test for the ESP-32S. It attemps to log in and prints the acquired ip address

#include <WiFi.h>

const char* ssid = "<SSID>"; // Insert the wireless network SSID
const char* psswd = "<PASSWORD>"; // Insert the wireless network password

void setup() {
  Serial.begin(115200);

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
  Serial.println(WiFi.localIP());
  delay(500);

}
