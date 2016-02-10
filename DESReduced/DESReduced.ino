//#include<LiquidCrystal.h>
#include <EEPROM.h>

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void createSubkeys(byte binaryKey[8]);
void encodeMessage(byte binaryMessage[64/8], byte encrypted[64/8]);
void f(byte R[32/8], byte K[48/8], byte outcome[32/8]);
void lookUpInSBox(size_t which, byte *address, byte *binaryOutcome, size_t addressFrom);

void setup() {
  Serial.begin( 9600 );

  //lcd.begin(16, 2);
  Serial.println(F("ready"));

  // get a key and make subkeys
  byte *binaryKey;
  binaryKey = new byte[8] {155, 100, 30, 0, 25, 222, 25, 25};
  createSubkeys(binaryKey);

  byte binaryMessage[8] = {155, 100, 30, 0, 25, 222, 25, 25};
  byte *C;
  //C = new byte[8]; 
  encodeMessage(binaryMessage, C);
  Serial.println(F("Before loop"));

}

void loop() {
  /*lcd.setCursor(0,0);
  lcd.print(F("fff"));*/
  Serial.println(F("Experiment is over!"));
}
