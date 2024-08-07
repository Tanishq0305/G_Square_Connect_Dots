#define TIMER_PIN 2  // Pin connected to 555 timer output
int incr = 0;
boolean in_state = LOW;
void setup() {
    pinMode(TIMER_PIN, INPUT);
    Serial.begin(9600);
}

void loop() {
  if(debounceSignal(in_state) == HIGH)
  {
    // incr++;
    // Serial.println(incr);
    int a = 1;
    Serial.println(a);
   
    Serial.println("0");
  }

  // else if(debounceSignal(in_state) == LOW && in_state == HIGH)
  // {
  //   incr++;
  //   in_state = LOW;
  // }

  if(incr == 5)
  {
    Serial.println("5 Seconds Completed...");
  }
}

boolean debounceSignal(boolean state)
{
  boolean stateNow = digitalRead(TIMER_PIN);
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(TIMER_PIN);
  }
  return stateNow;
}