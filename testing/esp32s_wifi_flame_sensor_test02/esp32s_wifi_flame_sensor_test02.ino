#include <WiFi.h>

const char* ssid = "<SSID>";
const char* psswd = "<PASSWORD>";
const char* server = "<SERVER/HOST>";
const int serverPort = <SERVER/HOST PORT>;
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
}
