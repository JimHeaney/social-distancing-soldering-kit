#include <HCSR04.h>

//Social Distancing Soldering Kit, Version 1.5
//By: Jim Heaney, March 2021
//CC-BY-SA-NC

//Settings:
const int mode = 1; //Set Display Mode, 0 for cathide, 1 for anode.
const int bright = 20; //Increases display brightness but may introduce flickering
float cal1 = 16.3; //The coarse calibration value for the sensor. Raw measuremrent is multiplied by cal1
float cal2 = 2; //The fine calibration value for the sensor. Cal1-corrected measurement is summed with cal2. 
int average = 50; //The number of measurements to average together before updating the screen. Higher values are more accurate and reduce screen jitters, but are slower to respond. 

//Arduino Pins
const int A = 8;
const int B = 6;
const int C = 3;
const int D = 4;
const int E = 5;
const int F = 7;
const int G = 2;
const int dot = 9;
const int dig1 = 10;
const int dig2 = 11;
const int dig3 = 12;
const int tog = A2;
const int tri = A3;
const int ech = A5;

HCSR04 hc(tri, ech);

int spacing = 0;
int len = 0;
int spacing1 = 0;
int spacing2 = 0;
int spacing3 = 0;
long summed = 0;
int x = 1;
int spacingraw = 0;
bool umode = 0;
int spacingcm = 0;

void setup() {
  // put your setup code here, to run once:

  //Declare all the pin modes
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(dot, OUTPUT);
  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
  pinMode(tog, INPUT);
  pinMode(tri, OUTPUT);
  pinMode(tog, INPUT);

  if (mode == 1){
    digitalWrite(dot, HIGH);
  }
  else {
    digitalWrite(dot, LOW);
  }

  spacing = (hc.dist() * cal1) + cal2;

}

void loop() {
  // put your main code here, to run repeatedly:
    
  //Read the distance from the sensor
  spacingraw = (hc.dist() * cal1) + cal2;

  //Average a bunch of values together before updating the screen. Until then, keep displaying the old value.
  if (x <= average){
    x = x + 1;
    summed = summed + spacingraw;
  } else {
    x = 1;
    spacing = summed / average;
    spacingcm = spacing;
    if (digitalRead(tog) == 1){
      spacing = spacing / 2.54;
    }
    summed = 0;
  }

  //Check if the distance measurement is too high or low. If so, display an error and measure again. If not, continue. 
  if ((spacingcm < 5) || (spacingcm > 390)){
     if (mode == 0){
      seg(10);
      digitalWrite(dig1, LOW);
      delayMicroseconds(bright);
      digitalWrite(dig1, HIGH);
      seg(10);
      digitalWrite(dig2, LOW);
      delayMicroseconds(bright);
      digitalWrite(dig2, HIGH);
      seg(10);
      digitalWrite(dig3, LOW);
      delayMicroseconds(bright);
      digitalWrite(dig3, HIGH);
    }
    if (mode == 1){
      seg(10);
      digitalWrite(dig1, HIGH);
      delayMicroseconds(bright);
      digitalWrite(dig1, LOW);
      seg(10);
      digitalWrite(dig2, HIGH);
      delayMicroseconds(bright);
      digitalWrite(dig2, LOW);
      seg(10);
      digitalWrite(dig3, HIGH);
      delayMicroseconds(bright);
      digitalWrite(dig3, LOW);
    }
  }
  else{

    //Multiply the number by 100, then mod split it into 3 characters.
    spacing1 = (spacing / 100) % 10;
    spacing2 = (spacing / 10) % 10;
    spacing3 = spacing % 10;
  
    //Write each character to the right value. When appropriate, write the dot point too.
    if (mode == 0){
      seg(spacing1);
      digitalWrite(dig1, LOW);
      delayMicroseconds(bright);
      digitalWrite(dig1, HIGH);
      seg(spacing2);
      delayMicroseconds(bright);
      digitalWrite(dig2, HIGH);
      seg(spacing3);
      digitalWrite(dig3, LOW);
      delayMicroseconds(bright);
      digitalWrite(dig3, HIGH);
    }
    if (mode == 1){
      seg(spacing1);
      digitalWrite(dig1, HIGH);
      delayMicroseconds(bright);
      digitalWrite(dig1, LOW);
      seg(spacing2);
      digitalWrite(dig2, HIGH);
      delayMicroseconds(bright);
      digitalWrite(dig2, LOW);
      seg(spacing3);
      digitalWrite(dig3, HIGH);
      delayMicroseconds(bright);
      digitalWrite(dig3, LOW);
    }
  } 
}

void seg(int count){
  if (mode == 0){
    if (count == 0)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
    }
    else if (count == 1)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
    }
    else if (count == 2)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
    }
    else if (count == 3)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
    }
    else if (count == 4)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
    }
    else if (count == 5)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
    }
    else if (count == 6)
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
    } 
    else if (count == 7)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
    }
    else if (count == 8)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
    }
    else if (count == 9)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
    }
    else {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
    }
  }
  if (mode == 1){
    if (count == 0)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
    }
    else if (count == 1)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
    }
    else if (count == 2)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
    }
    else if (count == 3)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
    }
    else if (count == 4)
      {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
    }
    else if (count == 5)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
    }
    else if (count == 6)
    {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
    } 
    else if (count == 7)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
    }
    else if (count == 8)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
    }
    else if (count == 9)
      {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
    }
    else {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
    }
  } 
}
