// 

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "<SSID>";
const char* psswd = "<SSID>";
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
