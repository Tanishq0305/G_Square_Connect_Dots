//------------------------------------------------Headers--------------------------------------------------//
#include <Adafruit_NeoPixel.h>
#define PIN 13
#define NUMPIXELS 49
void Level1();
//------------------------------------------------Variables--------------------------------------------------//
int arr_row[7] = {3,4,5,6,7,8,9};
int arr_col[7] = {A0,A1,A2,A3,A4,A5,2};
int IR[7][7];
const int threshold = 480; // Adjust this threshold based on your IR sensors
int i, j;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 100; // timing delay
int selected[7][7]; 
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

//------------------------------------------------Code--------------------------------------------------//
void setup() {
  Serial.begin(9600);

  // Set all row and column pins as input
  for (int i = 0; i < 7; i++) {
    pinMode(A0 + i, INPUT);
    pinMode(3 + i, INPUT);
  }

  pixels.begin();
}

void loop() {
Level1();
  // for (i = 0; i < 7; i++) {
  //   for (j = 0; j < 7; j++) {
  //     if (digitalRead(arr_row[i]) == 0 && digitalRead(arr_col[j]) == 0) { 
  //       IR[i][j] = 0;
  //        pixels.setPixelColor(pixelMap[i][j], pixels.Color(144, 238, 144));
  //     } else {
  //       IR[i][j] = 1;
  //       pixels.setPixelColor(pixelMap[i][j], pixels.Color(0, 0, 0));
  //     } 
  //   }
  // }
  
  // pixels.show();

  // Serial.println("--====-=============");
  // for (i = 0; i < 7; i++) {
  //   for (j = 0; j < 7; j++) {
  //     Serial.print(IR[i][j]);
  //   }
  //   Serial.println("");
  // }
 // delay(1000);



  pixels.show();
 
}

void Level1()
{
pixels.setPixelColor(pixelMap[0][0], red); //(0,0)
pixels.setPixelColor(pixelMap[1][0], lime); //(1,0)
pixels.setPixelColor(pixelMap[2][0], blue); //(2,0)
pixels.setPixelColor(pixelMap[3][0], yellow); //(3,0)
pixels.setPixelColor(pixelMap[4][0], cyan); //(4,0)
pixels.setPixelColor(pixelMap[5][0], magenta); //(5,0)
pixels.setPixelColor(pixelMap[6][0], orange); //(6,0)

pixels.setPixelColor(pixelMap[0][6], red); //(0,6)
pixels.setPixelColor(pixelMap[1][6], lime); //(1,6)
pixels.setPixelColor(pixelMap[2][6], blue); //(2,6)
pixels.setPixelColor(pixelMap[3][6], yellow); //(3,6)
pixels.setPixelColor(pixelMap[4][6], cyan); //(4,6)
pixels.setPixelColor(pixelMap[5][6], magenta); //(5,6)
pixels.setPixelColor(pixelMap[6][6], orange); //(6,6)

pixels.setPixelColor(pixelMap[3][3], pixels.getPixelColor(pixelMap[5][6])); //(6,6)
pixels.show();

// int lighted_arr[][] = {}

}

// void click()
// {
//     for (i = 0; i < 7; i++) {
//     for (j = 0; j < 7; j++) {
//       if (digitalRead(arr_row[i]) == 0 && digitalRead(arr_col[j]) == 0) { 
//         IR[i][j] = 0;
//          pixels.setPixelColor(pixelMap[i][j], pixels.Color(144, 238, 144));
//       } else {
//         IR[i][j] = 1;
//         pixels.setPixelColor(pixelMap[i][j], pixels.Color(0, 0, 0));
//       } 
//     }
//   }

//    pixels.show();
// }

void setPixelColor(int row, int col, uint32_t color) {
  pixels.setPixelColor(pixelMap[row][col], pixels.getPixelColor(pixelMap[row][col]));
}