const int relayPin =  8;      // the number of the LED pin

void setup() {
  pinMode(relayPin, OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  digitalWrite(relayPin, LOW);
}

void loop() {}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if(inChar == '0') {
      digitalWrite(relayPin, LOW);
    } else if(inChar == '1') {
      digitalWrite(relayPin, HIGH);
    }
  }
}
