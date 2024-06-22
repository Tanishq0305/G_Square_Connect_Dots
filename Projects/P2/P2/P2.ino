//------------------------------------------------Headers--------------------------------------------------//
#include <Adafruit_NeoPixel.h>
#define PIN 13
#define NUMPIXELS 49
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

//------------------------------------------------Colors--------------------------------------------------//
uint32_t redcolor(255,0,0);
uint32_t limecolor(0,255,0);
uint32_t bluecolor(0,0,255);

uint32_t yellowcolor(255,255,0);
uint32_t cyancolor(0,255,255);
uint32_t magentacolor(255,0,255);
uint32_t orangecolor(255,165,0);

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

  for (i = 0; i < 7; i++) {
    for (j = 0; j < 7; j++) {
      if (digitalRead(arr_row[i]) == 0 && digitalRead(arr_col[j]) == 0) { 
        IR[i][j] = 0;
         pixels.setPixelColor(pixelMap[i][j], pixels.Color(144, 238, 144));
      } else {
        IR[i][j] = 1;
        pixels.setPixelColor(pixelMap[i][j], pixels.Color(0, 0, 0));
      } 
    }
  }
  
  pixels.show();

  Serial.println("--====-=============");
  for (i = 0; i < 7; i++) {
    for (j = 0; j < 7; j++) {
      Serial.print(IR[i][j]);
    }
    Serial.println("");
  }
 // delay(1000);
}

void Level1()
{
pixels.setPixelColor(pixelMap[0][0], pixels.Color(144, 238, 144)); //(0,0)
pixels.setPixelColor(pixelMap[1][0], pixels.Color(144, 238, 144)); //(1,0)
pixels.setPixelColor(pixelMap[2][0], pixels.Color(144, 238, 144)); //(2,0)
pixels.setPixelColor(pixelMap[3][0], pixels.Color(144, 238, 144)); //(3,0)
pixels.setPixelColor(pixelMap[4][0], pixels.Color(144, 238, 144)); //(4,0)
pixels.setPixelColor(pixelMap[5][0], pixels.Color(144, 238, 144)); //(5,0)
pixels.setPixelColor(pixelMap[6][0], pixels.Color(144, 238, 144)); //(6,0)

pixels.setPixelColor(pixelMap[0][6], pixels.Color(144, 238, 144)); //(0,6)
pixels.setPixelColor(pixelMap[1][6], pixels.Color(144, 238, 144)); //(1,6)
pixels.setPixelColor(pixelMap[2][6], pixels.Color(144, 238, 144)); //(2,6)
pixels.setPixelColor(pixelMap[3][6], pixels.Color(144, 238, 144)); //(3,6)
pixels.setPixelColor(pixelMap[4][6], pixels.Color(144, 238, 144)); //(4,6)
pixels.setPixelColor(pixelMap[5][6], pixels.Color(144, 238, 144)); //(5,6)
pixels.setPixelColor(pixelMap[6][6], pixels.Color(144, 238, 144)); //(6,6)

pixels.show();


}