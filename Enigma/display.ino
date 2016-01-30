/**
   @file
   Functions used to display commands
*/

#include <avr/pgmspace.h>

#define NUMBER_OF_COMMANDS 5

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

extern int shift[3];

void displayCommands(int fromPosition) {

  const String commands[NUMBER_OF_COMMANDS] PROGMEM = {
    "generate key",
    "encrypt",
    "reset shift",
    "print shift",
    "set shift"
  };

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(commands[fromPosition % NUMBER_OF_COMMANDS]);

  lcd.setCursor(0, 1);
  lcd.print(commands[(fromPosition + 1) % NUMBER_OF_COMMANDS]);
}

////// TO BE DELETED //////
void displayMess(String mess) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mess);

  lcd.setCursor(0, 1);
  lcd.print(F("PressAButToContinue"));

  // wait until user presses a button
  delay(200);
  int input;
  do {
    input = read_LCD_buttons();
  }
  while (input == btnNONE);

}

/*
   displays message on lcd display
   RIGHT and LEFT buttons are used to move the line of text
   other buttons will terminate the function
*/
void displayLong(char* mess) {

  // current position of text displayed
  int firstChar = 0;
  int len = strlen(mess);

  lcd.clear();

  const char downLine[] PROGMEM = "Press L or R to move, D or U to exit";
  lcd.setCursor(0, 1);
  lcd.print(downLine);

  lcd.setCursor(0, 0);
  lcd.print(mess);

  while (true) {
    delay(200);

    int input = read_LCD_buttons();

    if (input == btnNONE)
      continue;

    if (input == btnRIGHT) {
      firstChar = (firstChar + 1) % len;
      goto updateMessage;
    }

    if (input == btnLEFT) {
      firstChar = (len + firstChar - 1) % len;
updateMessage:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print((char*) (mess + firstChar));
      lcd.setCursor(0, 1);
      lcd.print((char*) (downLine + firstChar));
      continue;
    }

    // if other button then LEFT or RIGHT was selected, escape the loop - and thus the function
    break;
  }

}

/*
   prints the current shift's settings
*/
void printShift() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("current shift:"));

  lcd.setCursor(0, 1);
  lcd.print(shift[0]);
  lcd.print(' ');
  lcd.print(shift[1]);
  lcd.print(' ');
  lcd.print(shift[2]);
  lcd.print(' ');

  // wait until user presses a button
  delay(200);
  int input;
  do {
    input = read_LCD_buttons();
  }
  while (input == btnNONE);

}

