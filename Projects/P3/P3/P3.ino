#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUMPIXELS 49

// IR sensor pins
int arr_row[7] = {3, 4, 5, 6, 7, 8, 9};
int arr_col[7] = {A0, A1, A2, A3, A4, A5, 2};
int IR[7][7];
int selected[7][7] = {0}; // 0: not selected, 1: selected

// NeoPixel setup
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 100; // timing delay

// Colors
uint32_t red = pixels.Color(255, 0, 0);
uint32_t lime = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t cyan = pixels.Color(0, 255, 255);
uint32_t magenta = pixels.Color(255, 0, 255);
uint32_t orange = pixels.Color(255, 165, 0);
uint32_t off = pixels.Color(0, 0, 0);

// Custom mapping array for LEDs
int pixelMap[7][7] = {
  {0, 1, 2, 3, 4, 5, 6},
  {13, 12, 11, 10, 9, 8, 7},
  {14, 15, 16, 17, 18, 19, 20},
  {27, 26, 25, 24, 23, 22, 21},
  {28, 29, 30, 31, 32, 33, 34},
  {41, 40, 39, 38, 37, 36, 35},
  {42, 43, 44, 45, 46, 47, 48}
};

int currentCellRow = -1;
int currentCellCol = -1;
int lastCellRow = -1;
int lastCellCol = -1;
int movesCount = 0;
bool isGameActive = true;

void setup() {
  Serial.begin(9600);

  // Initialize row and column pins as input
  for (int i = 0; i < 7; i++) {
    pinMode(arr_row[i], INPUT);
    pinMode(arr_col[i], INPUT);
  }

  pixels.begin();
  pixels.show();
  initializeLevel1();
}

void loop() {
  if (isGameActive) {
    checkIRSensors();
    pixels.show();

    if (checkGameComplete()) {
      isGameActive = false;
      displayGameOver();
    }
  }
  delay(100);
}

void checkIRSensors() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int rowVal = digitalRead(arr_row[i]);
      int colVal = digitalRead(arr_col[j]);
      if (rowVal == LOW && colVal == LOW) { // Assuming LOW means pressed
        handleCellInput(i, j);
        delay(40); // Debounce delay
      }
    }
  }
}

void handleCellInput(int row, int col) {
  if (currentCellRow == -1 && currentCellCol == -1) {
    // Start new line
    if (col == 0 || col == 6) 
    {
    currentCellRow = row;
    currentCellCol = col;
    lastCellRow = row;
    lastCellCol = col;
    //selected[row][col] = 1;
    //setPixelColor(row, col, orange); // Use any color to mark the start
    movesCount++;
    }else{
      Serial.println("Error1");
    }
  } else {
    if (isNeighbor(currentCellRow, currentCellCol, row, col)) {
      // Continue the line
      selected[row][col] = 1;
      setPixelColor(row, col, orange); // Use the same color for the line
      lastCellRow = currentCellRow;
      lastCellCol = currentCellCol;
      currentCellRow = row;
      currentCellCol = col;
    } else {
      // Invalid move
      currentCellRow = -1;
      currentCellCol = -1;
    }
  }
  displayGameState();
}

bool isNeighbor(int row1, int col1, int row2, int col2) {
  return (abs(row1 - row2) == 1 && col1 == col2) || (abs(col1 - col2) == 1 && row1 == row2);
}

bool checkGameComplete() {
  
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (!selected[i][j]) {
        return false;
      }
    }
  }
  
  /*
    for (int i = 0; i < 7; i++) {
    // for (int j = 0; j < 7; j++) {
      if (!selected[1][i] && !selected[6][i]) {
        return false;
         // }
        }
      }
      */
  return true;
}

void displayGameState() {
  Serial.print("Moves: ");
  Serial.println(movesCount);

  Serial.println("Cells:");
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      Serial.print(selected[i][j] ? "1 " : "0 ");
    }
    Serial.println();
  }
}

void displayGameOver() {
  Serial.println("Game Over!");
  // Add any other game over logic here
}

void initializeLevel1() {
  setPixelColor(0, 0, red);
  setPixelColor(1, 0, lime);
  setPixelColor(2, 0, blue);
  setPixelColor(3, 0, yellow);
  setPixelColor(4, 0, cyan);
  setPixelColor(5, 0, magenta);
  setPixelColor(6, 0, orange);

  setPixelColor(0, 6, red);
  setPixelColor(1, 6, lime);
  setPixelColor(2, 6, blue);
  setPixelColor(3, 6, yellow);
  setPixelColor(4, 6, cyan);
  setPixelColor(5, 6, magenta);
  setPixelColor(6, 6, orange);

  pixels.show();
}

void setPixelColor(int row, int col, uint32_t color) {
  pixels.setPixelColor(pixelMap[row][col], color);
}