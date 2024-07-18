#include <SPI.h>

// Pin definitions
const int CS_PIN = 10; // CS (Chip Select) pin for AT25F2048

// AT25F2048 Commands
const byte WREN = 0x06;
const byte WRDI = 0x04;
const byte RDSR = 0x05;
const byte WRSR = 0x01;
const byte READ = 0x03;
const byte PROGRAM = 0x02;
const byte SECTOR_ERASE = 0x52;
const byte CHIP_ERASE = 0x62;
const byte RDID = 0x9F;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize SPI
  SPI.begin();
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Disable chip select

  // Enable write operations
  writeEnable();

  // Write "Hi" to address 0x0000
  writeData(0x0000, "Hi", 2);

  // Read and print the data back to verify
  char data[3];
  readData(0x0000, data, 2);
  data[2] = '\0'; // Null-terminate the string
  Serial.print("Read data: ");
  Serial.println(data);
}

void loop() {
  // Nothing to do here
}

void writeEnable() {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(WREN);
  digitalWrite(CS_PIN, HIGH);
}

void writeData(unsigned int address, const char *data, byte length) {
  // Enable write operations before programming
  writeEnable();

  digitalWrite(CS_PIN, LOW);
  SPI.transfer(PROGRAM);
  SPI.transfer((address >> 8) & 0xFF); // Address MSB
  SPI.transfer(address & 0xFF);        // Address LSB

  for (byte i = 0; i < length; i++) {
    SPI.transfer(data[i]);
  }
  digitalWrite(CS_PIN, HIGH);

  waitForWriteCompletion(); // Wait for the write operation to complete
}

void readData(unsigned int address, char *data, byte length) {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(READ);
  SPI.transfer((address >> 8) & 0xFF); // Address MSB
  SPI.transfer(address & 0xFF);        // Address LSB

  for (byte i = 0; i < length; i++) {
    data[i] = SPI.transfer(0x00);
  }
  digitalWrite(CS_PIN, HIGH);
}

byte readStatusRegister() {
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(RDSR);
  byte status = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  return status;
}

void waitForWriteCompletion() {
  while (readStatusRegister() & 0x01) {
    delay(1); // Wait for the write cycle to complete
  }
}
