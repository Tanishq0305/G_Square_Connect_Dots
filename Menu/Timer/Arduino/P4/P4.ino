const int buttonPin = 3; 
bool levelCompleted = false;
unsigned long previousMillis = 0; 
unsigned long interval = 5000;
int currentLevel = 1; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600);
  startLevel();
}

void loop() {
  checkElapsedTime();
  checkUserInput();
}

void checkElapsedTime() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    if (!levelCompleted) {
      Serial.println("Time's up! Restarting level...");
      startLevel(); 
    }
  }
}

void checkUserInput() {
  if (digitalRead(buttonPin) == LOW) { 
    levelCompleted = true;
    Serial.println("Button pressed! Proceeding to the next level...");
    nextLevel();
  }
}

void startLevel() {
  levelCompleted = false;
  previousMillis = millis(); 


  switch (currentLevel) {
    case 1:
      interval = 5000; 
      break;
    case 2:
      interval = 10000; 
      break;
    case 3:
      interval = 15000; 
      break;
    default:
      interval = 5000; 
  }

  Serial.print("Starting level ");
  Serial.print(currentLevel);
  Serial.print(" with ");
  Serial.print(interval / 1000);
  Serial.println(" seconds.");
  
}

void nextLevel() {
  currentLevel++;
  Serial.println("Next level!");
  delay(1000);
  startLevel(); 
}
