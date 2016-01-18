#include <LiquidCrystal.h>
#include <Console.h>

extern bool encr;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
String message = "A";

void setup() {
  Serial.begin( 9600 );

  lcd.begin(16, 2);
  Serial.println("ready");
  enOrDecrypt();
  //  Serial.println("enordec behind");
  //  Serial.flush();
  //  Serial.println("after while");
  //  Serial.flush();
  //  delay(2000);
  //  Serial.end();

  messageExpand(&message);
  bool binaryMessage[message.length() * 8];

  messageToBinary(message, binaryMessage);
  //  Serial.println("after message to binary");
  //  Serial.flush();
  int key[8];
  getKey(key);

  //  Serial.println("before debug key");
  //  Serial.flush();

  debugArray(key, 8, 8);

  bool binaryKey[8 * 8];
  toBinary(key, binaryKey, 8);

//  Serial.println("after key to binary");
//  Serial.flush();

  // Step 1: Create 16 subkeys, each of which is 48-bits long.
  bool subkeys[16][48];
  createSubkeys(binaryKey, subkeys);

  // debugSubkeys(subkeys);


}

void loop() {
  // put your main code here, to run repeatedly:
//  lcd.setCursor(0, 0);
//  lcd.print(millis());
}
