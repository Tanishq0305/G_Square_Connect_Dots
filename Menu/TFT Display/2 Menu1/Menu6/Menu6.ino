//Working code with specific timer to respective level and display remaining timinig on 1.8tft Display
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    8
#define TFT_DC     9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const int buttonPin = 3; // Pin where the user button is connected
bool levelCompleted = false; // Flag to track if the level is completed
unsigned long previousMillis = 0; // Stores the last time the interval was checked
unsigned long interval = 5000; // Initial interval set to 5 seconds
int currentLevel = 1; // Start at level 1

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up resistor
  tft.initR(INITR_BLACKTAB);   // Initialize TFT
  tft.setRotation(1); // Rotate display by 90 degrees
  tft.fillScreen(ST7735_BLACK); // Clear screen
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);

  startLevel();
}

void loop() {
  checkElapsedTime();
  checkUserInput();
}

void checkElapsedTime() {
  unsigned long currentMillis = millis();
  unsigned long remainingTime = (interval - (currentMillis - previousMillis)) / 1000;

  // Display the remaining time on the TFT
  tft.fillRect(0, 0, 128, 20, ST7735_BLACK); // Clear the time area
  tft.setCursor(0, 0);
  tft.print("Time: ");
  tft.print(remainingTime);

  // Check if the specified interval has passed
  if (currentMillis - previousMillis >= interval) {
    if (!levelCompleted) {
      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(0, 30);
      tft.setTextColor(ST7735_RED);
      tft.print("Time's up!");
      delay(2000); // Wait for 2 seconds
      startLevel(); // Restart the level
    }
  }
}

void checkUserInput() {
  if (digitalRead(buttonPin) == LOW) { // Button pressed (LOW due to pull-up)
    levelCompleted = true;
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 30);
    tft.setTextColor(ST7735_GREEN);
    tft.print("Level ");
    tft.setCursor(0, 60);
    tft.print("completed! ");
    delay(2000); // Wait for 2 seconds
    nextLevel();
  }
}

void startLevel() {
  levelCompleted = false;
  previousMillis = millis(); // Reset the timer

  // Set the interval based on the current level
  switch (currentLevel) {
    case 1:
      interval = 5000; // 5 seconds for level 1
      break;
    case 2:
      interval = 10000; // 10 seconds for level 2
      break;
    case 3:
      interval = 15000; // 15 seconds for level 3
      break;
    default:
      interval = 5000; // Default back to 5 seconds for any other levels
      break;
  }

  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST7735_WHITE);
  tft.print("Starting ");
  tft.setCursor(0, 60);
 tft.print("level: ");
  tft.print(currentLevel);
}

void nextLevel() {
  currentLevel++;
  startLevel(); // Call startLevel() to initialize the new level
}
