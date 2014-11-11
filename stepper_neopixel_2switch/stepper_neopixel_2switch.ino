
#include <AFMotor.h>
#include <ReceiveOnlySoftwareSerial.h>
ReceiveOnlySoftwareSerial mySerial(10);
AF_Stepper motor(48, 2);
char inChar;
int coins = 0;
int b1,b2;
int showoption=0, showoption2=0;
#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

// -----------------------------------------------------------------   

void setup() {
  pinMode(3,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(13,INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("VENDO 2.0");
  motor.setSpeed(100); // 10 rpm
  mySerial.begin(9600);
}

// -----------------------------------------------------------------   

void loop() {

  if(mySerial.available()) {
    inChar = (char)mySerial.read();
    Serial.println("*");
    mySerial.end();
    colorWipe(strip.Color(0,30,0)); // Blue
    increase();
  }

  b1 = digitalRead(3);
  b1 = digitalRead(9);
  
  if(b1 == HIGH && showoption == 1)
    scoot1();
  if(b2 == HIGH && showoption == 1)
    scoot2();
    
//  if(showoption==1&&showoption2==1)
//      show();
//      
}

void increase() 
{
  if(coins < 3) 
  {
    coins++;
    Serial.print("A NEW COIN: ");
    Serial.println(coins);
    showoption = 0;
  } 
  else
  {  
    showoption=1; 
  } 
  mySerial.begin(9600);
}

void scoot1() {
Serial.println("!!!!!!!!!!!!!!!VENDING souvanier!!!!!!!!!!!!!!!");
motor.step(100, FORWARD, DOUBLE);
}

void scoot2() {
Serial.println("!!!!!!!!!!!!!!!VENDING designKit!!!!!!!!!!!!!!!");
motor.step(100, BACKWARD, DOUBLE);
}

void colorWipe(uint32_t c) 
{
  for(uint16_t i=0; i<coins; i++) 
  {
      strip.setPixelColor(i, c);
      strip.show();
      delay(1000);
  }
}
