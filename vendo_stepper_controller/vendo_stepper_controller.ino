// VENDOBOT Stepper Contoller

#include <AFMotor.h>

int t = 0;

AF_Stepper motor(48, 2);

int CCW_pin = 2;
int CW_pin = 13;

void setup()
{
  Serial.begin(9600);
  
  motor.setSpeed(350);
  
  pinMode(CCW_pin, INPUT);
  pinMode(CW_pin, INPUT);
  
}

void loop()
{
  
  int x,y;
  
  x = digitalRead(CCW_pin);
  y = digitalRead(CW_pin);
  
  if(x == HIGH && y == HIGH && t == 0) {
    
    motor.step(920, BACKWARD, SINGLE);
    delay(2000);
    motor.step(920, FORWARD, SINGLE);
    delay(2000);
    
  } else if(x == LOW && y == LOW) {
    Serial.println("LOW");
    t = 0;
  }  
  
//  if(x == HIGH && t==0) {
//
//    CW();
//    CCW();
//    
//    t = 1;
//    
//  } else if(y == HIGH && t==0) {
//  
//    CCW();
//    CW();
//    t = 1;
//    
//  } else if(x == LOW && y == LOW) {
//    Serial.println("LOW");
//    t = 0;
//  }
  
}

void CCW() {
  Serial.println("LEFT!"); 
  motor.step(920, BACKWARD, DOUBLE);
  delay(2000);
}

void CW() {
  Serial.println("RIGHT!"); 
  motor.step(920, FORWARD, DOUBLE);
  delay(2000);
}
