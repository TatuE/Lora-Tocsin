
//insert ledpin negative and flame sensor gnd to gnd \
  insert 3.3v arduino pin to flame sensor +  
const int systemLed = 13;
const int ledPin = 12; // insert ledpin positive to pin 12 
const int digitalPin = 8; // insert led sensor 'do' to pin 8

void setup() {
  Serial.begin(115200);
  pinMode (digitalPin, INPUT);
  pinMode (ledPin, OUTPUT);
  pinMode (systemLed, OUTPUT);
  digitalWrite (systemLed, LOW); 
}

void loop() {
  int flameSensor = LOW; 
  flameSensor = digitalRead(digitalPin);
  Serial.println(flameSensor);
  delay(500);
  if(flameSensor==HIGH){
   digitalWrite(ledPin, HIGH);
  }else{
   digitalWrite(ledPin, LOW);
  }
}
