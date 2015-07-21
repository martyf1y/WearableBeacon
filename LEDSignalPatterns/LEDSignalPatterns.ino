
// LED signal patterns
// Code created by Matthew Martin, July 2015. <http://www.creativematterz.com>
// Created for an LED shirt made of 1056 LEDs making a glow signal (AKA bird) every 10 seconds with a total of 8.
// You will need the modified adafruit library that I have provided
// For more info like video of it working, go to <http://www.martyf1y.tumblr.com/>
// If you have any questions or have a way to better implement it, please send me an email at martyfly.ta@gmail.com

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6

const int maxLEDs = 1056;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxLEDs, PIN, NEO_GRB + NEO_KHZ800);


int brightness[maxLEDs];
int LEDsArray[] = {24,25,26,27,38,40,40,40,40,37,36,35,35,34,34,34,34,34,35,35,36,37,40,40,40,40,38,27,26,25,24}; // This says how large each column of LEDs are
int stripNum; // This is which strip the LED is on
int rowNum; //This is how far up the LED is
int LEDNum; // This is the LED ID Num
const int birdNum = 8; // Total number of Birds capable of flying
int birdDisplay = 0; // Birds being checked  
bool shineAgain = false;
bool beginCheck = false;

class BirdObject {
  public:
  float posX;
  float posY;
  float speeds = random(6,10);
  int r,g,b;
  void Move();
  BirdObject();
  void Begin(float inX, float inY, int _r, int _g, int _b);
 
  private:
  float moveStepX = 0;
  float moveStepY = 1;
  float dir = 0;
  float ranWave = random(20, 30); // This is the speed it spirals at left to right, lower is slower
  float ranWaveWidth = random(5, 20); // This is the width between each spiral side, larger is wider
};
 
 
BirdObject::BirdObject(){} 

void BirdObject::Begin(float inX, float inY, int _r, int _g, int _b){
    posX = inX;
    posY = inY; 
    r = _r;
    g = _g;
    b = _b;
  }

void BirdObject::Move() {
 
    float wave = sin(radians(millis()*(ranWave*0.1)));

    moveStepX = dir + wave * ranWaveWidth;
    moveStepY = moveStepY * speeds;
    posX += moveStepX;
    posY += moveStepY;
  
    // check border condition
    if (posX<0) posX += 320;
    if (posX>=320) posX -= 320;
    if (posY<0) {
      posY+=410;
    }
    
    if (posY>=410){ // We randomise its location and speed every time the bird reaches the top
    posY -= 410;
    speeds = random(6,10);
    posX = random(0,310); 
    }

    // We randomise everything else every loop making it look like it is finding its way to the top
    ranWave = random(20, 30);
    ranWaveWidth = random(5, 20);
    dir = cos(degrees(random(20, 120)));
    speeds += 0.15; // Speeds up as it gets higher
  }

BirdObject *Birdy[birdNum];

void setup()
{
  Serial.begin(9600);           // start serial for output
  
  randomSeed(analogRead(0));

 for(int i = 0; i < maxLEDs; i++){ // Initiate all leds as off
   brightness[i] = 0;
 }
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
   if(millis() > 200*birdDisplay && birdDisplay < birdNum){ // Never go above birdNum, otherwise out of bounds
    Birdy[birdDisplay] = new BirdObject(); // Create a new bird
    Birdy[birdDisplay]->Begin(random(0, 310), 0, int(random(255)), int(random(255)), int(random(255))); // Give it values
    birdDisplay ++; // Make sure it fits in the for loops
  }
  for (int i=0; i<birdDisplay; i++) {
     Birdy[i]->Move(); // Update the birds position
     initiateShine(Birdy[i]->posX, Birdy[i]->posY, Birdy[i]->r, Birdy[i]->g, Birdy[i]->b); //Set the colour for the pixel 
}

  //////////// This updates the LEDs ////////////
 for (int i=0; i< maxLEDs; i++) {
  if(brightness[i] != 0){

   ShineOn(i, 3); //Get the right ID, brightness to update LED
    }
  }
  strip.show();
}

void ShineOn(int ID, int thisSpeed){
 
  ///// Make sure to get LED brightness before we go any further!
 
  int red = strip.getRedColor(ID); // Had to mess with the library but was able to gather rgb, sets it to the old one
  int blue = strip.getGreenColor(ID);
  int green = strip.getBlueColor(ID);

  brightness[ID] -= 1*thisSpeed;
   
  if(brightness[ID] <= 0){
    brightness[ID] = 0;
  }

   int arr = red*brightness[ID]/255;
   int gee = blue*brightness[ID]/255;
   int bee = green*brightness[ID]/255;
   ///// For really cool effect just use this //////
    // int bee = 255*brightness[ID];
    // int arr = 0;
    // int gee = 0;
  strip.setPixelColor(ID, arr, gee, bee);
  }
 
void initiateShine(float pX, float pY, int red, int green, int blue){
     stripNum = (int)(map(pX, 0, 320, 0, 31)); // We map the points to the LED strips IDs
     rowNum = (int)(map(pY, 0, 410, 0, 40));
     LEDNum = 0;
 for(int n = 0; n < stripNum; n++){
    LEDNum += LEDsArray[n];
  }
    LEDNum += rowNum;
   if(rowNum < LEDsArray[stripNum]){
    brightness[LEDNum] = 255;
    strip.setPixelColor(LEDNum, red, green, blue); /// I set the initial value here, so it can be taken by the led.
    LEDNum = 0;
   }
}
