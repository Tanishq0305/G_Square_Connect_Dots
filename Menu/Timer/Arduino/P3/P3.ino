const unsigned long interval = 1000;
unsigned long previousMillis = 0; 
int highCount = 0; 
const int inputPin = 2;  
bool levelcomplete = false;
void setup() {
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // checkElapsedTime(5);
  level1();
}

bool checkElapsedTime(int targetCount) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; 
    highCount++;
    Serial.print("Elapsed time count: ");
    Serial.println(highCount);
  }

  if (highCount == targetCount) {
    Serial.println("5 seconds completed");
    highCount = 0;  
    return true;
  }
  return false;

}

void runGameLogic() {

}

void level1(){
while(levelcomplete){
  if (digitalRead(inputPin) == HIGH && !checkElapsedTime(5)) {
    levelcomplete = true;
    Serial.println("Level Completed")
  }else{
     levelcomplete = false;
     
  }
}

 }

}
