//This demo code for the project is presented in\
  https://randomnerdtutorials.com/esp32-lora-rfm95-transceiver-arduino-ide/ 

#include <SPI.h>
#include <LoRa.h>

const int ss = 5;
const int rst = 32;
const int dio0 = 33;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("LoRa Receiver");
  
  LoRa.setPins(ss, rst, dio0); // define the nss, reset and digital 0 pins 

  while (!LoRa.begin(868E6)) { // Set the proper LoRa frequency before 'E6'. Europe is 868, USA is 915, Asia 433.
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0xFF);//Define a syncword to be used, the range is 0-0xFF (public network [LoRaWAN] is 0x34). \
                           In a point to point connection, the receiver (defined to use the same syncword) will only accept packages send using\
                           this specific syncword.  
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  int packetSize = LoRa.parsePacket(); //Check if there is a new packet to be received
  if (packetSize) { 
    Serial.print("Received message");
    while (LoRa.available()) {
      String LoRaData = LoRa.readString(); // read the package
      Serial.print(LoRaData); 
    }
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi()); // print the signal strength ofthe received package
  }
}
