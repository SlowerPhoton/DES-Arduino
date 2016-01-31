#include<LiquidCrystal.h>

#define SCRAMBLERS 3

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcdRow = 0;

void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);

//  randomSeed(analogRead(0));
randomSeed(111);
  
  displayCommands(0);
}

void loop() {
  
  if (getInput())
    displayCommands(lcdRow);  
  delay(200);
  
}
