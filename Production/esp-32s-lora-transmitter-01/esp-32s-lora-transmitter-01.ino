//This is the LoRa transmitter production code, version 01. It uses a flame sensor to detect the presence of fire\
  determines the result on a three sensor reading basis and sends the results using a LoRa point-to-point connection.
  
#include <SPI.h>
#include <LoRa.h>

const int ss = 5;
const int rst = 32;
const int dio0 = 33;
const int SensorDigital = 22;

const int sleepTime=15; // time to sleep in minutes
const int mSConverter = 60000000; // The sleep timer works using micro seconds,\
                                    this converts the sleepTime appropriately.

const String loraUid = "LT-A01"; // define the uid for the transmitter, this must also be included in the receiver module code.
int flameCount=0;
int loopCount=0;
int sensorResult;

void setup() {
  delay(500);
  Serial.begin(115200);
  delay(1000);
  pinMode(SensorDigital, INPUT);
  loraSetup();
  Serial.println("Setup complete");
}

void loop() {
  int sensorValue = LOW;
  sensorValue = digitalRead(SensorDigital);

  if(sensorValue==HIGH){ // if the sensor detects fire, the flamecount adds one
    flameCount++;
  }

  loopCount++;
  delay(3300);

  if(loopCount==3){
    if(flameCount>=2){
      sensorResult=1; //if the flame count is 2 or higher, the return value is 1(true).
    }else{
      sensorResult=0; //else the return value is 0(false).
    }
    Serial.println(loraUid+"="+String(sensorResult));
    LoRa.beginPacket();
    LoRa.print(loraUid+"="+String(sensorResult));
    LoRa.endPacket();    
    sleep();
  }
}

void loraSetup(){
   LoRa.setPins(ss, rst, dio0); // define the nss, reset and digital 0 pins

  while (!LoRa.begin(868E6)) { // Set the proper LoRa frequency before 'E6'. Europe is 868, USA is 915, Asia 433. 
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0x34);//Define a syncword to be used, the range is 0-0xFF (public network [LoRaWAN] is 0x34). \
                           In a point to point connection, the receiver (defined to use the same syncword) will only accept packages send using\
                           this specific syncword.
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125000);                           
  Serial.println("LoRa Initialized");
}

void sleep(){
  esp_sleep_enable_timer_wakeup(sleepTime*mSConverter); // define the wakeup timer (time to sleep).
  Serial.println("Sleeping for "+String(sleepTime)+" minutes.");
  delay(500);
  esp_deep_sleep_start();  // start the deep sleep
}
