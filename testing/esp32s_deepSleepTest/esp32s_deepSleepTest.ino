const int ledPin=23; // led + pin to pin 23, led - pin to gnd

const int sleepTime=10; // time to sleep in seconds
const int mSConverter = 1000000; // The sleep timer works using micro seconds,\
                                    this converts the sleepTime appropriately. 

void setup() {
  delay(500); // it seems there is a bug that prevents the ESP32 waking from deep sleep.\
                 It happens randomly after some reboots have taken place \
                 adding a small delay in the start should prevent this. \
                 This has not occured in this project as of this time.
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Waking up!");
  digitalWrite(ledPin, HIGH);
  delay(1000);
  sleep();
}

void loop() { 
 //No reason to use loop() in this test, since the setup() is performed at waking up from deep sleep.
}

void sleep(){
  esp_sleep_enable_timer_wakeup(sleepTime*mSConverter); // define the wakeup timer (time to sleep).
  Serial.println("Sleeping for "+String(sleepTime)+" seconds.");
  Serial.println("Going to sleep.");  
  delay(500);
  esp_deep_sleep_start();  // start the deep sleep
}
