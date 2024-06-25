#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUMPIXELS 49

int arr_row[7] = {3, 4, 5, 6, 7, 8, 9};
int arr_col[7] = {A0, A1, A2, A3, A4, A5, 2};
int IR[7][7] = {0};
const int threshold = 480; // Adjust this threshold based on your IR sensors

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Colors
uint32_t colors[7] = {
  pixels.Color(255, 0, 0),      // red
  pixels.Color(0, 255, 0),      // lime
  pixels.Color(0, 0, 255),      // blue
  pixels.Color(255, 255, 0),    // yellow
  pixels.Color(0, 255, 255),    // cyan
  pixels.Color(255, 0, 255),    // magenta
  pixels.Color(255, 165, 0)     // orange
};
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
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (digitalRead(arr_row[i]) == LOW && digitalRead(arr_col[j]) == LOW) {
        if (IR[i][j] == 0) { // Only light up if it was previously off
          IR[i][j] = 1;
          // Set the pixel color to the same as the first row or last row initialized in Level 1
          if (i == 0) {
            setPixelColor(i, j, colors[j]);
          } else if (i == 6) {
            setPixelColor(i, j, colors[j]);
          } else {
            setPixelColor(i, j, colors[j % 7]);
          }
          pixels.show();
        }
      }
    }
  }

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
    setPixelColor(0, i, colors[i]); // Set first row colors
    setPixelColor(6, i, colors[i]); // Set last row colors
  }

  pixels.show();
}

void setPixelColor(int row, int col, uint32_t color) {
  pixels.setPixelColor(pixelMap[row][col], color);
}
