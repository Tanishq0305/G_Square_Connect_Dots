#include <Adafruit_NeoPixel.h>
#define PIN 13
#define NUMPIXELS 49

//------------------------------------------------Variables--------------------------------------------------//
int arr_row[7] = {3, 4, 5, 6, 7, 8, 9};
int arr_col[7] = {A0, A1, A2, A3, A4, A5, 2};
int IR[7][7];
const int threshold = 480; // Adjust this threshold based on your IR sensors
int i, j;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 100; // timing delay

//------------------------------------------------Colors--------------------------------------------------//
uint32_t red = pixels.Color(255, 0, 0);
uint32_t lime = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t cyan = pixels.Color(0, 255, 255);
uint32_t magenta = pixels.Color(255, 0, 255);
uint32_t orange = pixels.Color(255, 165, 0);

//------------------------------------------------pixelMap--------------------------------------------------//
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

//------------------------------------------------Connection Tracking--------------------------------------------------//
bool connections[7][7] = {false}; // To track connections between dots

//------------------------------------------------Code--------------------------------------------------//
void setup() {
  Serial.begin(9600);

  // Set all row and column pins as input
  for (int i = 0; i < 7; i++) {
    pinMode(arr_row[i], INPUT);
    pinMode(arr_col[i], INPUT);
  }

  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'

  // Set initial level
  Level1();
}

void loop() {
  // Detect and process connections
  checkConnections();

  // Update the LEDs based on connections
  updateLEDs();

  delay(100); // Short delay for debounce
}

void Level1() {
  // Set initial colors for the dots
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

// Detect connections between dots based on user input
void checkConnections() {
  for (int row = 0; row < 7; row++) {
    for (int col = 0; col < 7; col++) {
      if (digitalRead(arr_row[row]) == LOW && digitalRead(arr_col[col]) == LOW) {
        if (!connections[row][col]) {
          connections[row][col] = true;
          lightPath(row, col);
        }
      }
    }
  }
}

// Light up the path between connected dots
void lightPath(int row, int col) {
  uint32_t color = pixels.getPixelColor(pixelMap[row][col]);

  // Check adjacent pixels in 4 directions and light up the path if the colors match
  if (row > 0 && pixels.getPixelColor(pixelMap[row - 1][col]) == color) {
    setPixelColor(row - 1, col, color);
  }
  if (row < 6 && pixels.getPixelColor(pixelMap[row + 1][col]) == color) {
    setPixelColor(row + 1, col, color);
  }
  if (col > 0 && pixels.getPixelColor(pixelMap[row][col - 1]) == color) {
    setPixelColor(row, col - 1, color);
  }
  if (col < 6 && pixels.getPixelColor(pixelMap[row][col + 1]) == color) {
    setPixelColor(row, col + 1, color);
  }
}

// Update the LEDs based on the connections
void updateLEDs() {
  for (int row = 0; row < 7; row++) {
    for (int col = 0; col < 7; col++) {
      if (connections[row][col]) {
        uint32_t color = pixels.getPixelColor(pixelMap[row][col]);
        setPixelColor(row, col, color);
      } else {
        setPixelColor(row, col, pixels.Color(0, 0, 0)); // Turn off LED if not connected
      }
    }
  }
  pixels.show();
}
