#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

// Define pins for the display
#define TFT_CS    10
#define TFT_RST   8
#define TFT_DC    9
#define ST77XX_GRAY 0x7BEF
// Define pins for the buttons
#define BUTTON_UP    3
#define BUTTON_DOWN  4
#define BUTTON_SELECT 5
#define BUTTON_BACK   6

// Create an instance of the display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Define menu items
const char* mainMenuItems[] = {"Start Game", "Settings", "Levels", "Exit"};
int mainMenuItemsCount = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);

const char* settingsMenuItems[] = {"Mute", "Brightness"};
int settingsMenuItemsCount = sizeof(settingsMenuItems) / sizeof(settingsMenuItems[0]);

const char* levels[] = {"Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Level 6", "Level 7", "Level 8", "Level 9"};
int levelsCount = sizeof(levels) / sizeof(levels[0]);
int currentLevel = 2; // The current level the user is on (0-based index)
int completedLevels = 1; // Number of completed levels (0-based index)

int selectedItem = 0;
bool inSettingsMenu = false;
bool inLevelsMenu = false;

void setup() {
  // Initialize the display
  tft.initR(INITR_BLACKTAB); // Init ST7735S chip, black tab
  tft.setRotation(1); // Rotate display if needed
  displayWelcomeMessage();
  // Initialize the buttons
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);

  // Fill the screen with black
  tft.fillScreen(ST77XX_BLACK);

  // Display the main menu
  displayMainMenu();
}

//---------------------------- Loop --------------------------------------------------// 
void loop() {
  // Check if the up button is pressed
  Up_Button_Press();
  // Check if the down button is pressed
  if (digitalRead(BUTTON_DOWN) == LOW) {
    selectedItem++;
    if (selectedItem >= (inSettingsMenu ? settingsMenuItemsCount : (inLevelsMenu ? levelsCount : mainMenuItemsCount))) {
      selectedItem = 0;
    }
    updateMenu();
    delay(200); // Debounce delay
  }

  // Check if the select button is pressed
  if (digitalRead(BUTTON_SELECT) == LOW) {
    if (!inSettingsMenu && !inLevelsMenu && selectedItem == 1) {
      inSettingsMenu = true;
      selectedItem = 0;
      displaySettingsMenu();
    } else if (!inSettingsMenu && !inLevelsMenu && selectedItem == 2) {
      inLevelsMenu = true;
      selectedItem = 0;
      displayLevelsMenu();
    } else if(!inSettingsMenu && !inLevelsMenu && selectedItem == 3){
        selectedItem = 0;
        turnOffDisplay();
  }
  delay(200);
    
  } // Debounce delay
  // Check if the back button is pressed
  if (digitalRead(BUTTON_BACK) == LOW) {
    if (inSettingsMenu) {
      inSettingsMenu = false;
      selectedItem = 1; // Return to the "Settings" menu item in the main menu
      displayMainMenu();
    } else if (inLevelsMenu) {
      inLevelsMenu = false;
      selectedItem = 2; // Return to the "Levels" menu item in the main menu
      displayMainMenu();
    }
    delay(200); // Debounce delay
  }
}

void Up_Button_Press(){
  
  if (digitalRead(BUTTON_UP) == LOW){
     selectedItem--;
     if(selectedItem < 0){
        if (inSettingsMenu) {
        selectedItem = settingsMenuItemsCount - 1;
      } else if (inLevelsMenu) {
        selectedItem = levelsCount - 1;
      }
      //  else if (inMuteMenu) {
      //   selectedItem = muteMenuItemsCount - 1;
      } else {
        selectedItem = mainMenuItemsCount - 1;
      }
        updateMenu();
         delay(200); // Debounce delay
     }

}
//---------------------------- Update Menu --------------------------------------------------// 
void updateMenu() {
  if (inSettingsMenu) {
    displaySettingsMenu();
  } else if (inLevelsMenu) {
    displayLevelsMenu();
  } else {
    displayMainMenu();
  }
}

//---------------------------- Main Menu --------------------------------------------------// 
void displayMainMenu() {
  // Set text size and color
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);

  // Clear the previous menu
  tft.fillScreen(ST77XX_BLACK);

  // Calculate the spacing and starting y position
  int menuItemHeight = 20; // Height of each menu item
  int spacing = 10; // Space between menu items
  int totalHeight = mainMenuItemsCount * (menuItemHeight + spacing) - spacing; // Total height of the menu
  int startY = (tft.height() - totalHeight) / 2; // Center the menu vertically

  // Display each menu item
  for (int i = 0; i < mainMenuItemsCount; i++) {
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(mainMenuItems[i], 0, 0, &x1, &y1, &w, &h); // Calculate the width of the text
    int x = (tft.width() - w) / 2; // Center the text horizontally
    int y = startY + i * (menuItemHeight + spacing); // Calculate the y position
    tft.setCursor(x, y);

    // Highlight the selected item
    if (i == selectedItem) {
      tft.setTextColor(ST77XX_RED); // Change color to red for the selected item
      tft.print(mainMenuItems[i]);
      tft.setTextColor(ST77XX_WHITE); // Change back to white for other items
    } else {
      tft.print(mainMenuItems[i]);
    }
  }

  // Draw menu bar border
  tft.drawRect(5, 5, tft.width() - 10, tft.height() - 10, ST77XX_WHITE);
}

//---------------------------- Settings Menu --------------------------------------------------// 
void displaySettingsMenu() {
  // Set text size and color
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);

  // Clear the previous menu
  tft.fillScreen(ST77XX_BLACK);

  // Calculate the spacing and starting y position
  int menuItemHeight = 20; // Height of each menu item
  int spacing = 10; // Space between menu items
  int totalHeight = settingsMenuItemsCount * (menuItemHeight + spacing) - spacing; // Total height of the menu
  int startY = (tft.height() - totalHeight) / 2; // Center the menu vertically

  // Display each menu item
  for (int i = 0; i < settingsMenuItemsCount; i++) {
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(settingsMenuItems[i], 0, 0, &x1, &y1, &w, &h); // Calculate the width of the text
    int x = (tft.width() - w) / 2; // Center the text horizontally
    int y = startY + i * (menuItemHeight + spacing); // Calculate the y position
    tft.setCursor(x, y);

    // Highlight the selected item
    if (i == selectedItem) {
      tft.setTextColor(ST77XX_RED); // Change color to red for the selected item
      tft.print(settingsMenuItems[i]);
      tft.setTextColor(ST77XX_WHITE); // Change back to white for other items
    } else {
      tft.print(settingsMenuItems[i]);
    }
  }

  // Draw menu bar border
  tft.drawRect(5, 5, tft.width() - 10, tft.height() - 10, ST77XX_WHITE);
}

//---------------------------- Exit Menu/ turn off --------------------------------------------------// 
void turnOffDisplay() {
  // Fill the screen with black
  tft.fillScreen(ST77XX_BLACK);
  
  // Optionally, you can put the display into sleep mode if supported
  // This depends on the specific display driver; the following line is an example
  tft.writeCommand(ST77XX_SLPIN); // Enter sleep mode
}

//---------------------------- Levels Menu --------------------------------------------------// 
void displayLevelsMenu() {
  // Set text size
  tft.setTextSize(2);

  // Clear the previous menu
  tft.fillScreen(ST77XX_BLACK);

  // Define the dimensions for the level squares
  int borderWidth = tft.width() - 10;
  int borderHeight = tft.height() - 10;
  int squareWidth = (borderWidth - 2 * 10) / 3.5; // Adjust for spacing
  int squareHeight = (borderHeight - 2 * 10) / 3.5; // Adjust for spacing
  int spacing = 10;
  int startX = (tft.width() - borderWidth) / 2 + 9; // Adjust for border
  int startY = (tft.height() - borderHeight) / 2 + 5; // Adjust for border

  // Display each level
  for (int i = 0; i < levelsCount; i++) {
    int row = i / 3;
    int col = i % 3;
    int x = startX + col * (squareWidth + spacing);
    int y = startY + row * (squareHeight + spacing);

    // Draw the rectangle for each level
    if (i == currentLevel) {
      tft.fillRect(x, y, squareWidth, squareHeight, ST77XX_RED); // Red for current level
    } else if (i <= completedLevels) {
      tft.fillRect(x, y, squareWidth, squareHeight, ST77XX_GREEN); // Green for completed levels
    } else {
      tft.fillRect(x, y, squareWidth, squareHeight, ST77XX_GRAY); // Gray for remaining levels
    }

    // Draw the border around the rectangle
    tft.drawRect(x, y, squareWidth, squareHeight, ST77XX_WHITE);

    // Set the text color to white for better visibility
    tft.setTextColor(ST77XX_WHITE);

    // Calculate the text position
    char levelText[10];
    sprintf(levelText, "%d", i + 1); // Display level number
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(levelText, 0, 0, &x1, &y1, &w, &h);
    int textX = x + (squareWidth - w) / 2;
    int textY = y + (squareHeight - h) / 2;

    // Set the cursor and print the level number
    tft.setCursor(textX, textY);
    tft.print(levelText);
  }

  // Draw menu bar border
  tft.drawRect(5, 5, borderWidth, borderHeight, ST77XX_WHITE);
}


//---------------------------- Welcome Message --------------------------------------------------// 
void displayWelcomeMessage() {
  // Fill the screen with black
  tft.fillScreen(ST77XX_BLACK);

  // Set text color and size
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  // Display "Welcome to Dot Knot"
  tft.setCursor(10, 30); // Adjust the cursor position as needed
  tft.print("Welcome to");

  tft.setCursor(10, 60); // Adjust the cursor position as needed
  tft.print("Dot Knot");

  // Display "By Toyo India"
  tft.setCursor(10, 100); // Adjust the cursor position as needed
  tft.setTextSize(1); // Smaller text size for the subtitle
  tft.setTextColor(ST77XX_YELLOW);
  tft.print("By ");

  tft.setTextColor(ST77XX_BLUE);
  tft.print("Toy");
 
  tft.setTextColor(ST77XX_RED);
  tft.print("oz ");

  tft.setTextColor(ST77XX_YELLOW);
  tft.print("India");
    // Wait for 3 seconds
  delay(3000);

  // Clear the screen (optional)
  tft.fillScreen(ST77XX_BLACK);
}