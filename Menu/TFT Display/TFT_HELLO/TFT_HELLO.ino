#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// Define the pins for the display
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

// Create an instance of the display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Initialize the display
  tft.initR(INITR_BLACKTAB); // Initialization for ST7735R

  // Set the rotation
  tft.setRotation(1);

  // Fill the screen with black color
  tft.fillScreen(ST77XX_BLACK);

  // Set text color and size
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  // Set the cursor position
  tft.setCursor(20, 30);

  // Display the text
  tft.println("Hello");
}

void loop() {
  // Nothing to do here
}
