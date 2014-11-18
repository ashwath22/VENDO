// VENDOBOT Coin and Panel Controller

#include <EEPROM.h>
#include <ReceiveOnlySoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define PIXELS 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(55, PIXELS, NEO_GRB + NEO_KHZ800);
ReceiveOnlySoftwareSerial mySerial(9);

char inChar;

int coins = 0;
int b1,b2;
int showoption=0, showoption2=0;
int count_1 = 0, count_2 = 0;
int vendMode = 0;
int vended = 0;
int idleCounter = 0;

const int INV_MAX_1 = 9;
const int INV_MAX_2 = 9;

const int BUTTON_1 = 3;
const int BUTTON_2 = 5;
const int BUTTON_RESET = 12;

const int VEND_1 = 10;
const int VEND_2 = 11;

// -----------------------------------------------------------------   

void setup() {
  
  pinMode(BUTTON_1,INPUT);
  pinMode(BUTTON_2,INPUT);
  pinMode(BUTTON_RESET,INPUT);
  
  pinMode(VEND_1,OUTPUT);
  pinMode(VEND_2,OUTPUT);
  pinMode(PIXELS,OUTPUT);
  
  strip.begin();
  strip.show();

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("VENDOBOT ONLINE!");
  mySerial.begin(9600);
  
  idleState();
 
}

// -----------------------------------------------------------------   

void loop() {  
    
  if(mySerial.available()) {
    inChar = (char)mySerial.read();
    Serial.println("*");
    mySerial.end();
    
    updateCoinPixels(strip.Color(0,30,0));
    
    increase();
  }
  
  if(vendMode == 2) {
        
    while(vended == false) {
      
      Serial.println("Waiting for button press...");
      
      ring_1(strip.Color(0,30,0));
      ring_2(strip.Color(0,30,0));
      delay(100);
      ring_1(strip.Color(0,0,0));
      ring_2(strip.Color(0,0,0));
      delay(100);
      
      b1 = digitalRead(BUTTON_1);
      b2 = digitalRead(BUTTON_2);

      if(b1 == HIGH)
        vend_1();
      if(b2 == HIGH)
        vend_2();
      
    }
    
    // reset this to false after the while loop exits
    vended = false;
  
  }
 
  // button to reset vend counts
  int r = digitalRead(BUTTON_RESET);
  if (r == HIGH) {
    resetVendCounts();
  }
       
}

// ----------------------------------------------------------------- 

void increase() 
{
  if(coins < 3) 
  {
    coins++;
    Serial.print("A new coin: ");
    Serial.print(coins);
    Serial.println("/4");
    vendMode = 1;
  } 
  else
  {  
    vendMode = 2;
  } 
  
  mySerial.begin(9600);
}

// -----------------------------------------------------------------   

void vend_1() {
  Serial.print("VENDING ITEM 1 ---------------------------------------");
  
  digitalWrite(VEND_1, HIGH);
  delay(5000);
  Serial.println("DONE");
  
  vended = true;

  count_1 = EEPROM.read(1);
  count_1++;
  EEPROM.write(1, count_1);
  
  resetAfterVend();
}

void vend_2() {
  Serial.print("VENDING ITEM 2 ---------------------------------------");

  digitalWrite(VEND_2, HIGH);
  delay(5000);
  Serial.println("DONE");
  
  vended = true;
  
  count_2 = EEPROM.read(2);
  count_2++;
  EEPROM.write(2, count_2);
  
  resetAfterVend();  
}

// -----------------------------------------------------------------   

void updateCoinPixels(uint32_t c) {

  for(uint16_t i=0; i<=coins; i++) 
  {
      strip.setPixelColor(i, c);
      strip.show();
  }

}

// -----------------------------------------------------------------

void ring_1(uint32_t c) {
  
  for(int i=4; i<=27; i++) 
  {
    strip.setPixelColor(i, c);
    strip.show();
  }
  
}

void ring_2(uint32_t c) {
  
  for(int i=28; i<=51; i++) 
  {
      strip.setPixelColor(i, c);
      strip.show();
  }
  
}

// -----------------------------------------------------------------   

void resetAfterVend() {
  
  Serial.println("\nReseting after vend");
  
  vendMode = 0;
  coins = 0;
  
  for(uint16_t i=0; i<=52; i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
      strip.show();
  }
  
  idleState();
}


// -----------------------------------------------------------------   

void idleState() {
    
    Serial.print("EEPROM - Vend Port 1: ");
    Serial.println(EEPROM.read(1));
    
    Serial.print("EEPROM - Vend Port 2: ");
    Serial.println(EEPROM.read(2));
    
    if(EEPROM.read(1) < INV_MAX_1) {
      ring_1(strip.Color(0,30,0));    
    }else {
      ring_1(strip.Color(0,0,0));    
    }

    if(EEPROM.read(2) < INV_MAX_2) {
      ring_2(strip.Color(0,30,0));    
    }else {
      ring_2(strip.Color(0,0,0));    
    } 
  
}


// -----------------------------------------------------------------   

void resetVendCounts() {
  
  EEPROM.write(1,0);
  delay(10);
  EEPROM.write(2,0); 
  delay(10);
  
  Serial.print("EEPROM - Vend Port 1: ");
  Serial.println(EEPROM.read(1));
    
  Serial.print("EEPROM - Vend Port 2: ");
  Serial.println(EEPROM.read(2));
   
}
