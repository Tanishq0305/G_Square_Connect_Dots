#include<SPIMemory.h>
 
//SPIFlash flash; // If you don't specify the library use standard SPI connection
SPIFlash flash;
void setup() {
  Serial.begin(115200);
 
  while (!Serial) ; // Wait for Serial monitor to open
  delay(100);
 
//  flash.setClock(12000000); // uncomment here for Arduino SAMD boards
 Serial.print("Not recognised...");
  flash.begin(MB(1)); // If SPIMemory isn't recognized you can specify the size of memory
 
//  flash.eraseChip();
 
  Serial.print(F("Flash size: "));
  Serial.print((long)(flash.getCapacity()/1000));
  Serial.println(F("Kb"));
 
  unsigned long strAddr = 0;
  unsigned long strAddrSecondString = 0;
 
  Serial.println();
  String inputString = "I'm going to write this string on IC";
  flash.writeStr(strAddr, inputString);
  Serial.print(F("Written string: "));
  Serial.println(inputString);
  Serial.print(F("To address: "));
  Serial.println(strAddr);
  String outputString = "";
  if (flash.readStr(strAddr, outputString)) {
    Serial.print(F("Read string: "));
    Serial.println(outputString);
    Serial.print(F("From address: "));
    Serial.println(strAddr);
  }
 
  Serial.println();
  String secondInputString = "I'm going to write this second string on IC";
  Serial.print(F("Check first free sector: "));
  strAddrSecondString = flash.getAddress(secondInputString.length());
  Serial.println(strAddrSecondString);
  Serial.println();
 
  flash.writeStr(strAddrSecondString, secondInputString);
  Serial.print(F("Written string: "));
  Serial.println(secondInputString);
  Serial.print(F("To address: "));
  Serial.println(strAddrSecondString);
  outputString = "";
  if (flash.readStr(strAddrSecondString, outputString)) {
    Serial.print(F("Read string: "));
    Serial.println(outputString);
    Serial.print(F("From address: "));
    Serial.println(strAddrSecondString);
  }
 
  while (!flash.eraseSector(strAddr));
  while (!flash.eraseSector(strAddrSecondString));
 
}
 
void loop() {
 
}