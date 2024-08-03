const int buttonPin = 4;     
const int ledPin =  3;     

void setup() {
  //Input or output?
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT_PULLUP);   
  Serial.begin(9600);
}

void loop(){
  //Read button state (pressed or not pressed?)
 int buttonState = digitalRead(buttonPin);

  //If button pressed...
  if (buttonState == 0) { 
     Serial.println("LOW");
     digitalWrite(ledPin, 0);
     }
     else if(buttonState == 1){
       Serial.println("HIGH");
        digitalWrite(ledPin, 1);
       }
     else{
      Serial.println("ERR");
     }
    delay(100);

}
