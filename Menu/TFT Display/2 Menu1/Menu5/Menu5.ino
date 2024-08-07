//Working Code upto Mute-> Sound ON and OFF
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
#define BUTTON_LEFT 1
#define BUTTON_RIGHT 0


// Create an instance of the display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Define menu items
const char* mainMenuItems[] = {"Start Game", "Settings", "Levels", "Exit"};
int mainMenuItemsCount = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);
static int secondsRemaining = 10; // Start countdown from 10 seconds

const char* PauseMenuItems[] = {"Continue", "Exit"};
int PauseMenuItemsCount = sizeof(PauseMenuItems) / sizeof(PauseMenuItems[0]);

const char* settingsMenuItems[] = {"Mute", "Brightness"};
int settingsMenuItemsCount = sizeof(settingsMenuItems) / sizeof(settingsMenuItems[0]);

const char* muteMenuItems[] = {"Sound On", "Sound Off"};
int muteMenuItemsCount = sizeof(muteMenuItems) / sizeof(muteMenuItems[0]);

const char* levels[] = {"Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Level 6", "Level 7", "Level 8", "Level 9"};
int levelsCount = sizeof(levels) / sizeof(levels[0]);


int selectedItem = 0;
bool inSettingsMenu = false;
bool inLevelsMenu = false;
bool inMuteMenu = false;
bool inMainMenu = true;
bool isSoundOn = false;
bool isSoundOff = true;
bool selectedlevelx = false;
bool timecompleted = false;
bool pause = false;

int currentLevel = 7; // The current level the user is on (0-based index)
int completedLevels = 6; // Number of completed levels (0-based index)
int selectedLevel = currentLevel; // Start with the current level selected

void setup() {
  // Initialize the display
  tft.initR(INITR_BLACKTAB); // Init ST7735S chip, black tab
  tft.setRotation(1); // Rotate display if needed
  displayWelcomeMessage();
  // Initialize the buttons
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);

    // Initialize analog pins
  pinMode(BUTTON_LEFT, INPUT_PULLUP); // Initialize left button
  pinMode(BUTTON_RIGHT, INPUT_PULLUP); // Initialize right button
  

  // Fill the screen with black
  tft.fillScreen(ST77XX_BLACK);

  // Display the main menu
  displayMainMenu();
}

void handleUp(){
      selectedItem--;
    if (selectedItem < 0) {
      if (inSettingsMenu) {
        selectedItem = settingsMenuItemsCount - 1;
      } else if (inMuteMenu) {
        selectedItem = 1;
      } 
      // else if (inLevelsMenu) {
      //   inLevelsMenu = true;
      //   displayLevelsMenu();
      // } 
      else if(inLevelsMenu){
      byte store;
      store = selectedLevel;
      selectedLevel = selectedLevel-3;
      if(selectedLevel < 0){
        selectedLevel = store;
      }
      }else {
        inMainMenu = true;
        inLevelsMenu = false;
        inMuteMenu = false;
        inSettingsMenu = false;
        selectedItem = mainMenuItemsCount - 1;
      }
    }
    updateMenu();
    delay(200); // Debounce delay
}

void handleDown(){
      selectedItem++;
    if (inSettingsMenu && selectedItem >= settingsMenuItemsCount) {
      selectedItem = 0;
    } else if (inMainMenu && selectedItem >= mainMenuItemsCount) {
      selectedItem = 0;
    } else if (inMuteMenu && selectedItem >= muteMenuItemsCount) {
      selectedItem = 0;
    }else if(inLevelsMenu){
      byte store;
      store = selectedLevel;
      selectedLevel = selectedLevel+3;
      if(selectedLevel < 0){
        selectedLevel = store;
      }
    }else if(selectedlevelx && selectedItem >= PauseMenuItemsCount){
      selectedItem = 0;
    }
    updateMenu();
    delay(200); // Debounce delay
}
//---------------------------- Loop --------------------------------------------------// 
void loop() {

  if (digitalRead(BUTTON_UP) == LOW) {
    handleUp();
  }

  if (digitalRead(BUTTON_DOWN) == LOW) {
    handleDown();
  }
  //------------------------------------------- DOWN Button Ends ------------------------------------------- //

  //------------------------------------------- LEFT Button Starts ------------------------------------------- //
  if (digitalRead(BUTTON_LEFT) == LOW && inLevelsMenu) {
    if (selectedLevel % 3 > 0) { // Check if not at leftmost column
      selectedLevel--; // Move left
      updateLevelsMenu();
    }
    delay(200); // Debounce delay
  }
  //------------------------------------------- LEFT Button Ends ------------------------------------------- //

  //------------------------------------------- RIGHT Button Starts ------------------------------------------- //
  if (digitalRead(BUTTON_RIGHT) == LOW && inLevelsMenu) {
    if (selectedLevel % 3 < 2) { // Check if not at rightmost column
      selectedLevel++; // Move right
      updateLevelsMenu();
    }
    delay(200); // Debounce delay
  }
  //------------------------------------------- RIGHT Button Ends ------------------------------------------- //

  //------------------------------------------- SELECT Button Starts ------------------------------------------- //
  if (digitalRead(BUTTON_SELECT) == LOW) {
    if (!inSettingsMenu && !inLevelsMenu && !inMuteMenu && inMainMenu && selectedItem == 1) {
      inSettingsMenu = true;
      inMainMenu = false;
      selectedItem = 0;
      displaySettingsMenu();
    } else if (!inSettingsMenu && !inLevelsMenu && !inMuteMenu && inMainMenu && selectedItem == 2) {
      inLevelsMenu = true;
      inMainMenu = false;
      selectedItem = 0;
      displayLevelsMenu();
    } else if (!inSettingsMenu && !inLevelsMenu && !inMuteMenu && inMainMenu && selectedItem == 3) {
      inMainMenu = false;
      selectedItem = 0;
      turnOffDisplay();
    } else if (inSettingsMenu && !inLevelsMenu && !inMuteMenu && !inMainMenu && selectedItem == 0) {
      inSettingsMenu = false;
      inMuteMenu = true;
      selectedItem = 0;
      displayMuteMenu();
    } else if (!inSettingsMenu && !inLevelsMenu && inMuteMenu && !inMainMenu && selectedItem == 0) {
      inSettingsMenu = false;
      inMuteMenu = true;
      selectedItem = 0;
      sound_on();
    } else if (!inSettingsMenu && !inLevelsMenu && inMuteMenu && !inMainMenu && selectedItem == 1) {
      inSettingsMenu = false;
      inMuteMenu = true;
      selectedItem = 1;
      sound_off();
    }else if(!inSettingsMenu && inLevelsMenu && !inMuteMenu && !inMainMenu && selectedLevel==0){
      inLevelsMenu = false;
      selectedlevelx = true;
      timecompleted = true;
      selectedItem = 0;
      while(timecompleted){
        Level1();
        delay(1000);
        if(digitalRead(BUTTON_BACK) == LOW)
        {
           pause = true;
           ContinueExit();
           delay(5000);
           if(timecompleted == false){
            break;
           }
           pause = false;
        }
      
      }
     timecompleted = false;
     levelCompleted();
     secondsRemaining = 10; // Start countdown from 10 seconds
    }else if(!inSettingsMenu && !inLevelsMenu && !inMuteMenu && pause && selectedLevel==1){
       timecompleted = false;
       secondsRemaining = 10; // Start countdown from 10 seconds
       pause = false;
    }
    delay(200);
  }
  //------------------------------------------- SELECT Button Ends ------------------------------------------- //

  //------------------------------------------- BACK Button Starts ------------------------------------------- //
  if (digitalRead(BUTTON_BACK) == LOW) {
    if (inSettingsMenu) {
      inSettingsMenu = false;
      inMainMenu = true;
      selectedItem = 1; // Return to the "Settings" menu item in the main menu
      displayMainMenu();
    } else if (inLevelsMenu) {
      inLevelsMenu = false;
      inMainMenu = true;
      selectedItem = 2; // Return to the "Levels" menu item in the main menu
      displayMainMenu();
    } else if (inMuteMenu) {
      inMuteMenu = false;
      inSettingsMenu = true;
      selectedItem = 0;
      displaySettingsMenu();
    }else if(selectedlevelx){
      selectedlevelx = false;
      inLevelsMenu = true;
      displayLevelsMenu();
    }
    delay(200); // Debounce delay
  }
  //------------------------------------------- BACK Button Ends ------------------------------------------- //
}


//---------------------------- Update Menu --------------------------------------------------// 
void updateMenu() {
  if (inSettingsMenu) {
    displaySettingsMenu();
  } else if (inLevelsMenu) {
    displayLevelsMenu();
  } else if(inMuteMenu){
     displayMuteMenu();
  }else if(pause){
    ContinueExit();
  }
  else{
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
void updateLevelsMenu() {
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

    // Draw blue cursor around selected level
    if (i == selectedLevel) {
      tft.drawRect(x - 2, y - 2, squareWidth + 4, squareHeight + 4, ST77XX_BLUE);
    }

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
  tft.print(F("Welcome to"));

  tft.setCursor(10, 60); // Adjust the cursor position as needed
  tft.print(F("Dot Knot"));

  // Display "By Toyo India"
  tft.setCursor(10, 100); // Adjust the cursor position as needed
  tft.setTextSize(1); // Smaller text size for the subtitle
  tft.setTextColor(ST77XX_YELLOW);
  tft.print(F("By "));

  tft.setTextColor(ST77XX_BLUE);
  tft.print(F("Toy"));
 
  tft.setTextColor(ST77XX_RED);
  tft.print(F("oz "));

  tft.setTextColor(ST77XX_YELLOW);
  tft.print(F("India"));
    // Wait for 3 seconds
  delay(3000);

  // Clear the screen (optional)
  tft.fillScreen(ST77XX_BLACK);
}

//---------------------------- Mute Menu  --------------------------------------------------// 
void displayMuteMenu() {
  // Set text size and color
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);

  // Clear the previous menu
  tft.fillScreen(ST77XX_BLACK);

  // Calculate the spacing and starting y position
  int menuItemHeight = 20; // Height of each menu item
  int spacing = 10; // Space between menu items
  int totalHeight = muteMenuItemsCount * (menuItemHeight + spacing) - spacing; // Total height of the menu
  int startY = (tft.height() - totalHeight) / 2; // Center the menu vertically

  // Display each menu item
  for (int i = 0; i < muteMenuItemsCount; i++) {
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(muteMenuItems[i], 0, 0, &x1, &y1, &w, &h); // Calculate the width of the text
    int x = (tft.width() - w) / 2; // Center the text horizontally
    int y = startY + i * (menuItemHeight + spacing); // Calculate the y position
    tft.setCursor(x, y);

    // Highlight the selected item
    if (i == selectedItem) {
      tft.setTextColor(ST77XX_RED); // Change color to red for the selected item
      tft.print(muteMenuItems[i]);
      tft.setTextColor(ST77XX_WHITE); // Change back to white for other items
    } else {
      tft.print(muteMenuItems[i]);
    }
  }

  // Draw menu bar border
  tft.drawRect(5, 5, tft.width() - 10, tft.height() - 10, ST77XX_WHITE);
}
//---------------------------- Sound ON and OFF  --------------------------------------------------// 
void sound_on(){
  digitalWrite(2, HIGH);
}

void sound_off(){
  digitalWrite(2, LOW);
}
//---------------------------- Updated Levels Menu --------------------------------------------------// 
void displayLevelsMenu() {
  updateLevelsMenu();
}
//---------------------------- Level 1 Start --------------------------------------------------// 
void Level1(){
  tft.fillRect(0, 0, tft.width(), 20, ST77XX_BLACK); 
  char timeString[9]; // Buffer to hold the time string in format HH:MM:SS

  // Clear the previous time display
  tft.fillScreen(ST77XX_BLACK); // Clear the area for the time display

  // Display "Time" text
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(0, 0);
  tft.print(F("Level 1"));

  // Convert secondsRemaining to HH:MM:SS format
  int hours = secondsRemaining / 3600;
  int minutes = (secondsRemaining % 3600) / 60;
  int seconds = secondsRemaining % 60;

  snprintf(timeString, sizeof(timeString), "%02d:%02d:%02d", hours, minutes, seconds);

  // Display the time
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(0, 20); // Adjust the cursor position to fit your screen
  tft.print(timeString);

  // Decrement the secondsRemaining
  if (secondsRemaining > 0) {
    secondsRemaining--;
  }else if(secondsRemaining == 0){
    timecompleted = false;
  }
}
//---------------------------- Level 1 END --------------------------------------------------// 

//---------------------------- Message Level Completed --------------------------------------------------// 

void levelCompleted(){
 tft.fillScreen(ST77XX_BLACK);

  // Set text color and size
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);

 
  tft.setCursor(10, 30); // Adjust the cursor position as needed
  tft.print(F("Level 1"));

  tft.setCursor(10, 60); // Adjust the cursor position as needed
  tft.print(F("Completed!!!"));
}
//---------------------------- Message Level Completed --------------------------------------------------// 

//---------------------------- Number of Completed Levels Start --------------------------------------------------// 
void completed()
{
  currentLevel = 7; // The current level the user is on (0-based index)
  completedLevels = 6; // Number of completed levels (0-based index)
  selectedLevel = currentLevel; // Start with the current level selected
}
//---------------------------- Number of Completed Levels End  --------------------------------------------------//
void ContinueExit(){
    // Set text size and color
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);

  // Clear the previous menu
  tft.fillScreen(ST77XX_BLACK);

  // Calculate the spacing and starting y position
  int menuItemHeight = 20; // Height of each menu item
  int spacing = 10; // Space between menu items
  int totalHeight = PauseMenuItemsCount * (menuItemHeight + spacing) - spacing; // Total height of the menu
  int startY = (tft.height() - totalHeight) / 2; // Center the menu vertically

  // Display each menu item
  for (int i = 0; i < PauseMenuItemsCount; i++) {
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(PauseMenuItems[i], 0, 0, &x1, &y1, &w, &h); // Calculate the width of the text
    int x = (tft.width() - w) / 2; // Center the text horizontally
    int y = startY + i * (menuItemHeight + spacing); // Calculate the y position
    tft.setCursor(x, y);

    // Highlight the selected item
    if (i == selectedItem) {
      tft.setTextColor(ST77XX_RED); // Change color to red for the selected item
      tft.print(PauseMenuItems[i]);
      tft.setTextColor(ST77XX_WHITE); // Change back to white for other items
    } else {
      tft.print(PauseMenuItems[i]);
    }
  }

  // Draw menu bar border
  tft.drawRect(5, 5, tft.width() - 10, tft.height() - 10, ST77XX_WHITE);
}