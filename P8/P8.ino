//This is working code for the one-row logic
//The problem is it doesn't overwrite the complete past path

#include <Adafruit_NeoPixel.h>
#define PIN 13
#define NUMPIXELS 49
#define MAX_PATH_LENGTH 49

int arr_row[7] = { 3, 4, 5, 6, 7, 8, 9 };
int arr_col[7] = { A0, A1, A2, A3, A4, A5, 2 };
int IR[7][7] = { 0 };
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Colors
uint32_t colors[7] = {
  pixels.Color(255, 0, 0),    // red
  pixels.Color(0, 255, 0),    // lime
  pixels.Color(0, 0, 255),    // blue
  pixels.Color(255, 255, 0),  // yellow
  pixels.Color(0, 255, 255),  // cyan
  pixels.Color(255, 0, 255),  // magenta
  pixels.Color(255, 165, 0)   // orange
};
uint32_t off = pixels.Color(0, 0, 0);

// Custom mapping array for LEDs
int pixelMap[7][7] = {
  { 0, 1, 2, 3, 4, 5, 6 },
  { 13, 12, 11, 10, 9, 8, 7 },
  { 14, 15, 16, 17, 18, 19, 20 },
  { 27, 26, 25, 24, 23, 22, 21 },
  { 28, 29, 30, 31, 32, 33, 34 },
  { 41, 40, 39, 38, 37, 36, 35 },
  { 42, 43, 44, 45, 46, 47, 48 }
};

// Array to store the color of each pixel
uint32_t pixelColors[7][7] = { 0 };

// Path tracking variables
int path[MAX_PATH_LENGTH][2];
int pathLength = 0;
bool isUserTouching = false;
bool isFirstTouch = true;
uint32_t startColor = off;

// Correct path
int Right_Path[2][14][2] = {
  {{ 6, 0 }, { 5, 0 }, { 4, 0 }, { 3, 0 }, { 2, 0 }, { 1, 0 },{ 0, 0 }},
  {{ 6, 1 }, { 5, 1 }, { 4, 1 }, { 3, 1 }, { 2, 1 }, { 1, 1 },{ 0, 1 }}
};
int correctPathLength = 7;

void setup() {
  Serial.begin(9600);

  // Set all row and column pins as input
  for (int i = 0; i < 7; i++) {
    pinMode(arr_row[i], INPUT);
    pinMode(arr_col[i], INPUT);
  }

  pixels.begin();
  initializeLevel1();
}

void loop() {
  bool currentTouching = false;

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (digitalRead(arr_row[i]) == LOW && digitalRead(arr_col[j]) == LOW) {
        currentTouching = true;
        if (IR[i][j] == 0) {  // Only light up if it was previously off
          IR[i][j] = 1;
          //------------------------------------Changed the line here for the level 1 pixels ----------------------------------------------------------//
          if (isFirstTouch) {
            // Record the color of the starting cell
            startColor = getPixelColor(i, j);
            isFirstTouch = false;
          }
          //-----------------------------------------------I am updating the loop here-----------------------------------------------------------------//
          //   if (!isInInitializeLevel1(row, col)) {
          //   setPixelColor(row, col, off); // Turn off the LED
          // }
          //-----------------------------------------------I am updating the loop here-----------------------------------------------------------------//
          if (startColor != off) {
            setPixelColor(i, j, startColor);  // Light up the touched LED with start color
            pixels.show();
          }

          // Store the path
          if (pathLength < MAX_PATH_LENGTH) {
            path[pathLength][0] = i;
            path[pathLength][1] = j;
            pathLength++;
          }
        }
      }
    }
  }

  // If user was touching but now lifted their finger
  if (isUserTouching && !currentTouching) {
    // Compare user path with the correct path
    if (!comparePaths()) {
      // Turn off the LEDs that were lit during the user's path
      for (int k = 0; k < pathLength; k++) {
        int row = path[k][0];
        int col = path[k][1];
        if (!isInInitializeLevel1(row, col)) {
          setPixelColor(row, col, off);  // Turn off the LED
        }
        initializeLevel1();
      }
      pixels.show();
      Serial.println("Path did not match, LEDs turned off.");
    } else {
      Serial.println("Path matched!");
    }

    // Print the path
    Serial.println("User path:");
    for (int k = 0; k < pathLength; k++) {
      Serial.print("(");
      Serial.print(path[k][0]);
      Serial.print(", ");
      Serial.print(path[k][1]);
      Serial.println(")");
    }
    Serial.println("----");

    // Reset the path for the next touch
    pathLength = 0;
    memset(IR, 0, sizeof(IR));  // Reset IR array
    isFirstTouch = true;        // Allow new path to start
  }

  // Update the user touching status
  isUserTouching = currentTouching;
  delay(300);

  // Debugging output
  Serial.println("-====-====-====-====-");
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      Serial.print(IR[i][j]);
    }
    Serial.println("");
  }
}

void initializeLevel1() {
  for (int i = 0; i < 7; i++) {
    setPixelColor(0, i, colors[i]);  // Set first row colors
    setPixelColor(6, i, colors[i]);  // Set last row colors
  }

  pixels.show();
}

void setPixelColor(int row, int col, uint32_t color) {
  pixels.setPixelColor(pixelMap[row][col], color);
  pixelColors[row][col] = color;  // Update the color array
}

bool comparePaths() {
  if (pathLength != correctPathLength) {
    return false;
  }
  for(int k = 0; k<2;k++){
  for (int i = 0; i < correctPathLength; i++) {
    if (path[i][0] != Right_Path[k][i][0] || path[i][0] != Right_Path[k][i][1]) {
      return false;
    }
  }
  return true;
  }
  //return true;
}

bool isInInitializeLevel1(int row, int col) {
  // Check if the LED is part of the initialized LEDs in initializeLevel1()
  return row == 0 || row == 6;
}

uint32_t getPixelColor(int row, int col) {
  return pixelColors[row][col];
}
