// VENDOBOT Stepper Contoller

#include <AFMotor.h>

int t = 0;
int d = 0;

AF_Stepper motor(48, 2);

int CCW_pin = 2;
int CW_pin = 13;

void setup()
{
  Serial.begin(9600);
  
  motor.setSpeed(200);
  
  pinMode(CCW_pin, INPUT);
  pinMode(CW_pin, INPUT);
  
}

void loop()
{
  
  int x,y;
  
  x = digitalRead(CCW_pin);
  y = digitalRead(CW_pin);
  
  if(x == HIGH && t==0) {
 
    CCW();
    t = 1;
    
  } else if(y == HIGH && t==0) {
  
    CW();
    t = 1;
    
  } else if(x == LOW && y == LOW) {
    Serial.println("LOW");
    t = 0;
  }
  
}

void CCW() {
  Serial.println("LEFT!"); 
  motor.step(100, BACKWARD, SINGLE);
  delay(2000);
}

void CW() {
  Serial.println("RIGHT!"); 
  motor.step(100, FORWARD, SINGLE);
  delay(2000);
}
