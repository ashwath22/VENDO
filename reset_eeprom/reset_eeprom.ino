#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  EEPROM.write(1,0);
  delay(10);
  EEPROM.write(2,0); 
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
