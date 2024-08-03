const int ledPins[4] = {10, 11, 12, 13};  // Array for LED pin numbers
const int switchPins[4] = {4, 5, 6, 7};  // Array for switch pin numbers

void setup() {
  // Set LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Set switch pins as inputs with pull-up resistors
  for (int i = 0; i < 4; i++) {
    pinMode(switchPins[i], INPUT);
  }
}

void loop() {
  // Loop through each switch and LED pair
  if(digitalRead(4)){
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }else if(digitalRead(5)){
    digitalWrite(11, HIGH);
     digitalWrite(10, LOW);
  }
}
