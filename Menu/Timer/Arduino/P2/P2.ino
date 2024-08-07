const int inputPin = 2;  
const int targetCount = 5;  
int highCount = 0;  
bool prevState = LOW; 

void setup() {
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool currentState = digitalRead(inputPin);

  if (currentState == HIGH && prevState == LOW) {
    highCount++;
    Serial.print("HIGH signal count: ");
    Serial.println(highCount);
  }

  prevState = currentState;


  if (highCount == targetCount) {
    Serial.println("5 seconds completed");
    highCount = 0; 
  }
}
