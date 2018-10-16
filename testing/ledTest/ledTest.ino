//insert both ledlamp negatives to gnd
#define greenLed 12 //digital pin 12 = greenled positive
#define redLed 9 // digital pin 9 = redled positive

void setup() {
  pinMode (greenLed, OUTPUT);
  pinMode (redLed, OUTPUT);
}

void loop() {
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  delay(500);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  delay(500);  

}
