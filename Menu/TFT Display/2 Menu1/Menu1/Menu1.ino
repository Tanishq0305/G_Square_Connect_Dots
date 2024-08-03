#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

// Define pins for the display
#define TFT_CS    10
#define TFT_RST   8
#define TFT_DC    9

// Create an instance of the display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Initialize the display
  tft.initR(INITR_BLACKTAB); // Init ST7735S chip, black tab
  tft.setRotation(1); // Rotate display if needed

  // Fill the screen with black
  tft.fillScreen(ST77XX_BLACK);

  // Display the menu bar
  displayMenuBar();
}

void loop() {
  // Main loop (can be used to navigate the menu)
}

void displayMenuBar() {
  // Define menu items
  const char* menuItems[] = {"Start Game", "Settings", "High Scores", "Exit"};
  int menuItemsCount = sizeof(menuItems) / sizeof(menuItems[0]);

  // Set text size and color
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);

  // Calculate menu bar height
  int menuBarHeight = 25 * menuItemsCount;

  // Display each menu item
  for (int i = 0; i < menuItemsCount; i++) {
    tft.setCursor(10, 10 + i * 20); // Adjust position as needed
    tft.print(menuItems[i]);
  }

  // Draw menu bar border
  tft.drawRect(5, 5, tft.width() - 10, menuBarHeight + 10, ST77XX_WHITE);
}