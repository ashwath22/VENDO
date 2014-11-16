//  GO GO VENDO

#include <AFMotor.h>
#include <ReceiveOnlySoftwareSerial.h>

ReceiveOnlySoftwareSerial mySerial(10);
AF_Stepper motor(48, 2);
char inChar;
int coins = 0;
int b1,b2;
int showoption=0, showoption2=0;
int count1=0,count2=0;
#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(55, PIN, NEO_GRB + NEO_KHZ800);

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

void loop() 
{
  if(mySerial.available()) 
  {
    inChar = (char)mySerial.read();
    Serial.println("*");
    mySerial.end(); 
    colorWipe(strip.Color(0,30,0)); // Blue
    increase();
  }
  
//  Buttons1();
  
  b1 = digitalRead(3);
  b2 = digitalRead(9);
  
  if(b1 == HIGH && showoption == 1)
    {
      scoot1();
      count1++;
    }
  if(b2 == HIGH && showoption == 1)
    {
      scoot2();
      count2++;
    }
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

void scoot1() 
{
    Serial.println("!!!!!!!!!!!!!!!VENDING souvanier!!!!!!!!!!!!!!!");
    
    motor.step(100, FORWARD, DOUBLE);
}

void scoot2() 
{
    Serial.println("!!!!!!!!!!!!!!!VENDING designKit!!!!!!!!!!!!!!!");
    motor.step(100, BACKWARD, DOUBLE);
}

void colorWipe(uint32_t c) 
{
  strip.setPixelColor(0,c);
  
  if(coins<4 && count1==19)
  {
    for(int i=4;i<28;i++)
    { 
      strip.setPixelColor(i, 0);
      delay(10);
    }
  }
  
  if(coins<4 && count2==19)
  {
    for(int i=29;i<52;i++)
    { 
      strip.setPixelColor(i, 0);
      delay(10);
    }
  }
  
  while(coins<4)
  {
  }
  
  for(uint16_t i=1; i<=coins; i++) 
  {
      strip.setPixelColor(i, c);
      strip.show();
      delay(1000);
  }
  if(coins==4 && count1==19)
  buttonCase1(strip.Color(0,30,0));
  if(coins==4 && count2==19)
  buttonCase2(strip.Color(0,30,0));
  if(coins==4)
  {
    strip.setPixelColor(5, c);
  }


}

void buttonCase1(uint32_t c) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=4, p=29; i < 28; i=i+3, p=p+3) {
        strip.setPixelColor(i+q, c);
        strip.setPixelColor(p+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(100);
     
      for (int i=4,p=29; i < 28; i=i+3, p=p+3) {
        strip.setPixelColor(i+q, 0);
        strip.setPixelColor(p+q, 0); 
        //turn every third pixel off
      }
    }
  }
}
void buttonCase2(uint32_t c) {
  for (int j=0; j<10; j++) 
  {
    for (int q=0; q < 3; q++) 
    {
      for (int i=4; i < 28; i=i+3) 
      {
        strip.setPixelColor(i+q, c);
        
      }
      strip.show();
     
      delay(100);
     
      for (int i=4,p=29; i < 28; i=i+3, p=p+3) 
      {
        strip.setPixelColor(i+q, 0);
      }
    }
  }
}

void buttonCase3(uint32_t c) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=4, p=29; i < 28; p=p+3) {
        strip.setPixelColor(p+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(100);
     
      for (int p=29; p < 52; p=p+3) 
      {
        strip.setPixelColor(p+q, 0); 
        //turn every third pixel off
      }
    }
  }
}


