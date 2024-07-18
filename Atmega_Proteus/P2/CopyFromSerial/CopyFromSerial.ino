#include <SerialFlash.h>
#include <SPI.h>

//Buffer sizes
#define USB_BUFFER_SIZE      128
#define FLASH_BUFFER_SIZE    4096

//Max filename length (8.3 plus a null char terminator)
#define FILENAME_STRING_SIZE      13

//State machine
#define STATE_START      0
#define STATE_SIZE      1
#define STATE_CONTENT    2

//Special bytes in the communication protocol
#define BYTE_START      0x7e
#define BYTE_ESCAPE      0x7d
#define BYTE_SEPARATOR    0x7c


//SPI Pins (these are the values on the Audio board; change them if you have different ones)
#define MOSI              11
#define MISO              12
#define SCK               13
#define CSPIN             10
//#define CSPIN           21  // Arduino 101 built-in SPI Flash

void setup(){
  Serial.begin(9600);  //Teensy serial is always at full USB speed and buffered... the baud rate here is required but ignored

  pinMode(7, OUTPUT);
  
  //Set up SPI
  // SPI.setMOSI(MOSI);  // uncomment these if using the alternate pins
  // SPI.setMISO(MISO);
  // SPI.setSCK(SCK);
   digitalWrite(10, LOW);
  if (!SerialFlash.begin(CSPIN)) {
    while (1) {
      Serial.println(F("Unable to access SPI Flash chip"));
      delay(1000);
    }
  }


  //We start by formatting the flash...
  uint8_t id[5];
  SerialFlash.readID(id);
  SerialFlash.eraseAll();
  
  //Flash LED at 1Hz while formatting
  while (!SerialFlash.ready()) {
    delay(500);
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(7, LOW);
  }

  //Quickly flash LED a few times when completed, then leave the light on solid
  for(uint8_t i = 0; i < 10; i++){
    delay(100);
    digitalWrite(7, HIGH);
    delay(100);
    digitalWrite(7, LOW);
  }
  digitalWrite(7, HIGH);
  
  //We are now going to wait for the upload program
  while(!Serial.available());
  
  SerialFlashFile flashFile;
  
  uint8_t state = STATE_START;
  uint8_t escape = 0;
  uint8_t fileSizeIndex = 0;
  uint32_t fileSize = 0;
  char filename[FILENAME_STRING_SIZE];
  
  char usbBuffer[USB_BUFFER_SIZE];
  uint8_t flashBuffer[FLASH_BUFFER_SIZE];
  
  uint16_t flashBufferIndex = 0;
  uint8_t filenameIndex = 0;
  
  uint32_t lastReceiveTime = millis();
  
  //We assume the serial receive part is finished when we have not received something for 3 seconds
  while(Serial.available() || lastReceiveTime + 3000 > millis()){
    uint16_t available = Serial.readBytes(usbBuffer, USB_BUFFER_SIZE);
    if (available) {
      lastReceiveTime = millis();
    }

    for (uint16_t usbBufferIndex = 0; usbBufferIndex < available; usbBufferIndex++){
      uint8_t b = usbBuffer[usbBufferIndex];
      
      if (state == STATE_START){
        //Start byte.  Repeat start is fine.
        if (b == BYTE_START){
          for (uint8_t i = 0; i < FILENAME_STRING_SIZE; i++){
            filename[i] = 0x00;
          }
          filenameIndex = 0;
        }
        //Valid characters are A-Z, 0-9, comma, period, colon, dash, underscore
        else if ((b >= 'A' && b <= 'Z') || (b >= '0' && b <= '9') || b == '.' || b == ',' || b == ':' || b == '-' || b == '_'){
          filename[filenameIndex++] = b;
          if (filenameIndex >= FILENAME_STRING_SIZE){
            //Error name too long
            flushError();
            return;
          }
        }
        //Filename end character
        else if (b == BYTE_SEPARATOR){
          if (filenameIndex == 0){
            //Error empty filename
            flushError();
            return;
          }
          
          //Change state
          state = STATE_SIZE;
          fileSizeIndex = 0;
          fileSize = 0;
          
        }
        //Invalid character
        else {
          //Error bad filename
          flushError();
          return;
        }
      }
      //We read 4 bytes as a uint32_t for file size
      else if (state == STATE_SIZE){
        if (fileSizeIndex < 4){
          fileSize = (fileSize << 8) + b;
          fileSizeIndex++;
        }
        else if (b == BYTE_SEPARATOR){
          state = STATE_CONTENT;
          flashBufferIndex = 0;
          escape = 0;
          
          if (SerialFlash.exists(filename)){
            SerialFlash.remove(filename);  //It doesn't reclaim the space, but it does let you create a new file with the same name.
          }
          
          //Create a new file and open it for writing
          if (SerialFlash.create(filename, fileSize)) {
            flashFile = SerialFlash.open(filename);
            if (!flashFile) {
              //Error flash file open
              flushError();
              return;
            }
          }
          else {
            //Error flash create (no room left?)
            flushError();
            return;
          }
        }
        else {
          //Error invalid length requested
          flushError();
          return;
        }
      }
      else if (state == STATE_CONTENT){
        //Previous byte was escaped; unescape and add to buffer
        if (escape){
          escape = 0;
          flashBuffer[flashBufferIndex++] = b ^ 0x20;
        }
        //Escape the next byte
        else if (b == BYTE_ESCAPE){
          //Serial.println("esc");
          escape = 1;
        }
        //End of file
        else if (b == BYTE_START){
          //Serial.println("End of file");
          state = STATE_START;
          flashFile.write(flashBuffer, flashBufferIndex);
          flashFile.close();
          flashBufferIndex = 0;
        }
        //Normal byte; add to buffer
        else {
          flashBuffer[flashBufferIndex++] = b;
        }
        
        //The buffer is filled; write to SD card
        if (flashBufferIndex >= FLASH_BUFFER_SIZE){
          flashFile.write(flashBuffer, FLASH_BUFFER_SIZE);
          flashBufferIndex = 0;
        }
      }
    }
  }

  //Success!  Turn the light off.
  digitalWrite(7, LOW);
}

void loop(){
  //Do nothing.
}

void flushError(){
  uint32_t lastReceiveTime = millis();
  char usbBuffer[USB_BUFFER_SIZE];
  //We assume the serial receive part is finished when we have not received something for 3 seconds
  while(Serial.available() || lastReceiveTime + 3000 > millis()){
    if (Serial.readBytes(usbBuffer, USB_BUFFER_SIZE)){
      lastReceiveTime = millis();
    }
  }
}
