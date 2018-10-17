//This is a debugging test for the flame sensor.
//insert ledpin negative and flame sensor gnd to gnd \
  insert 3.3v arduino pin to flame sensor +  
const int systemLed = 13; // Arduino onboard led
const int digitalPin = 8; // insert led sensor 'do' to pin 8
const int analogPin = A0; // insert led sensor 'Ao' to pin 8

void setup() {
  Serial.begin(115200);
  pinMode (digitalPin, INPUT);
  pinMode (analogPin, INPUT);
  digitalWrite (systemLed, LOW); //turn off the arduino onboard led.
}

void loop() {
  int flameSensorDigital = LOW;
  int flameSensorAnalog =-1; 
  flameSensorDigital = digitalRead(digitalPin);
  flameSensorAnalog = analogRead(analogPin);
  Serial.println(flameSensorDigital);
  Serial.println(flameSensorAnalog);
  delay(500);
}
