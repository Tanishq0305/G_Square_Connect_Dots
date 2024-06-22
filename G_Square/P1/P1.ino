#include <Adafruit_NeoPixel.h>

#define PIN 13
#define NUMPIXELS 49

int arr_row[7] = {3, 4, 5, 6, 7, 8, 9};
int arr_col[7] = {A0, A1, A2, A3, A4, A5, 2};
int IR[7][7];
const int threshold = 480; // Adjust this threshold based on your IR sensors
int i, j;
int redColor = 144;
int greenColor = 238;
int blueColor = 144;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // timing delay

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

// Initial points to connect on the same horizontal line
int startX = 3, startY = 1;
int endX = 3, endY = 5;
bool pathConnected[7][7] = {false};
bool pointsConnected = false;

void setup() {
  Serial.begin(9600);

  // Set all row and column pins as input
  for (int i = 0; i < 7; i++) {
    pinMode(arr_row[i], INPUT);
    pinMode(arr_col[i], INPUT);
  }

  pixels.begin();

  // Initialize start and end points
  pixels.setPixelColor(pixelMap[startX][startY], pixels.Color(redColor, greenColor, blueColor));
  pixels.setPixelColor(pixelMap[endX][endY], pixels.Color(redColor, greenColor, blueColor));
  pixels.show();
}

void loop() {
  if (!pointsConnected) {
    for (i = 0; i < 7; i++) {
      for (j = 0; j < 7; j++) {
        // Keep initial points lit
        if ((i == startX && j == startY) || (i == endX && j == endY)) {
          pixels.setPixelColor(pixelMap[i][j], pixels.Color(redColor, greenColor, blueColor));
        } else if (pathConnected[i][j]) {
          // If the point is part of the path, keep it lit
          pixels.setPixelColor(pixelMap[i][j], pixels.Color(redColor, greenColor, blueColor));
        } else {
          // Check IR sensor status
          if (i == startX && digitalRead(arr_row[i]) == 0 && digitalRead(arr_col[j]) == 0) {
            IR[i][j] = 1;
            pathConnected[i][j] = true;
            pixels.setPixelColor(pixelMap[i][j], pixels.Color(redColor, greenColor, blueColor));
          } else {
            IR[i][j] = 0;
            pixels.setPixelColor(pixelMap[i][j], pixels.Color(0, 0, 0));
          }
        }
      }
    }

    pixels.show();

    // Check if a valid horizontal line path is completed
    if (isHorizontalLineConnected()) {
      pointsConnected = true;
      delay(500); // Short delay before turning all LEDs red

      // Turn all LEDs red
      for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
          pixels.setPixelColor(pixelMap[i][j], pixels.Color(255, 0, 0));
        }
      }
      pixels.show();
    }

    // Print IR array for debugging
    Serial.println("--====-=============");
    for (i = 0; i < 7; i++) {
      for (j = 0; j < 7; j++) {
        Serial.print(IR[i][j]);
      }
      Serial.println("");
    }
  }

  delay(100);
}

bool isHorizontalLineConnected() {
  // Check if start and end points are on the same row
  if (startX == endX) {
    // Check horizontal line
    for (int j = min(startY, endY); j <= max(startY, endY); j++) {
      if (!pathConnected[startX][j]) return false;
    }
    return true;
  }
  return false;
}
