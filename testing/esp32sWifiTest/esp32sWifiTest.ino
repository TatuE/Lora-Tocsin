#include <WiFi.h>

const char* ssid = "<SSID>";
const char* psswd = "<PASSWORD>";

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
