//This is the A version of the Lora receiver, this one uses the HTTPclient to send messages to the LoRa server.\
  It listens for LoRa messages, checks their validity and passes them on using Wifi.

#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <HTTPClient.h>

const int ss = 5;
const int rst = 32;
const int dio0 = 33;

const char* ssid = "<ssid>"; // Insert the wireless network SSID
const char* psswd = "<psswd>"; // Insert the wireless network password

String host = "http://0.0.0.0"; // insert target host, no need to add port (which is 80/tcp in this case)
String validLoRaUid[] ={"LoraA01","LoraB01","LoraA02","LoraB02"}; // define the known transmitter device uid's, this is a checklist.

void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(1000);
  wifiConnect(); // prepare the wifi connection
  loraSetup();  // prepare the LoRa connection
}

void loop() {
  String loRaData;
  String loraUid;
  int arrayContainsUid=0;
  int sensorValue = 2;
  
  int packetSize = LoRa.parsePacket();  //Check if there is a new packet to be received
  if (packetSize) {
    Serial.println("Received message");
        
    while(LoRa.available()) { // Loop as long there is a message row to read.
      loRaData += LoRa.readString(); //Read message row     
    }
    
    Serial.print("RSSI = ");
    Serial.println(LoRa.packetRssi()); // print the signal strength of the received package
    Serial.print("SnR = ");
    Serial.println(LoRa.packetSnr()); // print signal to noise ratio
        
    int splitIndex=loRaData.indexOf("="); // Get the index of the symbol '='    
    loraUid = loRaData.substring(0,splitIndex); //Parse the String portion from beginning (0) to the index ('=').\
                                                  This should be the transmitter uid. 
    for(int i=0;i<2;i++){
      if(validLoRaUid[i].equals(loraUid)){
        arrayContainsUid=1; // if the String equals a known transmitter uid, set value to 1 (true).  
      }
    }
    
    if(arrayContainsUid==1){ // if an only if true, prepare to parse the sensor value.
      Serial.println("Sender is valid, LoRaUid = "+loraUid);
    
      String sValue = (String)loRaData.charAt(splitIndex+1); // parse the sensor value ( 0 or 1 / false or true).    
      sensorValue = sValue.toInt(); // check and convert to int if possible.
              
        if(sensorValue==1||sensorValue==0){ //if Int value is 1 or 0, prepare to send http message.
          Serial.println("Payload is valid, sensor value = "+(String)sensorValue);
                  
          if(WiFi.status() != WL_CONNECTED){ // if there is no WiFi connection, attempt reconnect.
            wifiConnect();
          }        
          HTTPClient http;
          Serial.println("Sending message!");
          http.begin(host+"/Lora-Tocsin/AddSensorData?loraUid="+loraUid+"&sensorValue="+String(sensorValue)); // prepare the http message.
          http.GET(); // send the http message using GET
          http.end();      
        }else{
          Serial.println("No valid Payload");  // If toInt convertion failed.
        }    
    }else{
      Serial.println("Not valid loraUid!!"); // if no LoRa uid was found in the validLoRaUid array.
    }
  }
}

void loraSetup(){
  LoRa.setPins(ss, rst, dio0); // define the nss, reset and digital 0 pins

  while (!LoRa.begin(868E6)) { // Set the proper LoRa frequency before 'E6'. Europe is 868, USA is 915, Asia 433.
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0xFF);//Define a syncword to be used, the range is 0-0xFF (public network [LoRaWAN] is 0x34). \
                           In a point to point connection, the receiver (defined to use the same syncword) will only accept packages send using\
                           this specific syncword.
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125000);  
  Serial.println("LoRa Initialized");
}

void wifiConnect(){
  WiFi.begin(ssid, psswd); // use the credentials for wifi login.

  while (WiFi.status() != WL_CONNECTED) { //while loop is as long there is no connection made.
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  delay(500);
  Serial.println("");
  delay(500);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //print network ip address.
}
