//This is a basic blinking led light test for the ESP-32S
//Insert the led negative pint to ESP-32S GND
const int led = 22; //insert the led positive pin to ESP-32S pin 22

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);

  delay(500);
  digitalWrite(led,LOW);
}
