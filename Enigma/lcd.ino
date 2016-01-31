/**
    @file
    functions related to the lcd's input and output
*/

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  delay(5); //switch debounce delay. Increase this delay if incorrect switch selections are returned.
  int k = (analogRead(0) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
  if (5 < abs(k)) return btnNONE;  // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}

/*
   uses read_LCD_buttons() to determine input @n
   if none button is selected, do nothing
   if UP, DOWN, RIGHT or LEFT button is selected, change lcdRow accordingly
   if the button SELECT was pressed, call callFunction()
*/
bool getInput() {
  int input = read_LCD_buttons();

  if (input == btnNONE) {
    return false;
  }

  if (input == btnDOWN) {
    lcdRow = (lcdRow + 1) % NUMBER_OF_COMMANDS;
    return true;
  }

  if (input == btnUP) {
    lcdRow = (NUMBER_OF_COMMANDS + lcdRow - 1) % NUMBER_OF_COMMANDS;
    return true;
  }

  if (input == btnRIGHT) {
    lcdRow = (lcdRow + 2) % NUMBER_OF_COMMANDS;
    return true;
  }

  if (input == btnLEFT) {
    lcdRow = (NUMBER_OF_COMMANDS + lcdRow - 2) % NUMBER_OF_COMMANDS;
    return true;
  }

  // otherwise the button pressed had to be SELECT
  callFunction();
  return true;
}

/*
   looks up the character in special morse alphabet by its number
   when there is no character corresponding to the number, return '#'
*/
char lookUpMorse(int inpSum) {
  switch (inpSum) {
    case 0:
      return ' ';
    case 100:
      return 'A';
    case 4:
      return 'B';
    case 300:
      return 'C';
    case 3:
      return 'D';
    case 1:
      return 'E';
    case 120:
      return 'F';
    case 201:
      return 'G';
    case 101:
      return 'H';
    case 20:
      return 'I';
    case 13:
      return 'J';
    case 400:
      return 'K';
    case 30:
      return 'L';
    case 102:
      return 'M';
    case 200:
      return 'N';
    case 2:
      return 'O';
    case 111:
      return 'P';
    case 31:
      return 'Q';
    case 110:
      return 'R';
    case 11:
      return 'S';
    case 10:
      return 'T';
    case 12:
      return 'U';
    case 40:
      return 'V';
    case 21:
      return 'W';
    case 103:
      return 'X';
    case 210:
      return 'Y';
    case 130:
      return 'Z';
    default:
      return '#';
  }
}
/*
   calls lookUpMorse
   when button SELECT pressed returns chosen character
   if the user presses LEFT when there is nothing written, return ' '
   if the user presses SELECT when there is nothing written, return '@'
*/
char getChar() {

  int last = 0;
  int morse = 0;

  int input;
  do {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(lookUpMorse(morse));

    delay(200);

    // wait for user to press a button
    do {
      input = read_LCD_buttons();
    }
    while (input == btnNONE);

    if (input == btnUP) {
      last = 1;
      morse += last;
      continue;
    }
    if (input == btnRIGHT) {
      last = 10;
      morse += last;
      continue;
    }
    if (input == btnDOWN) {
      last = 100;
      morse += last;
      continue;
    }

    if (input == btnLEFT) {
      if (last == 0) {
        morse = 0;
        break;
      }
      morse -= last;
      last = 0;
      continue;
    }

  } while (input != btnSELECT);

  // if the loop ended by pressing SELECT and morse is 0, return '@'
  if (input == btnSELECT && morse == 0)
    return '@';

  // else return chosen character
  return lookUpMorse(morse);
}

/*
   calls function getChar() to obtain openText
   is user presses SELECT when nothing is written, the function returns
*/
void getOpenText() {

  int i = 0;
  while (i < 256) {
    char c = getChar();
    if (c == '@') // if the user pressed SELECT when nothing written, end
      break;
    openText[i] = c;
    i++;
  }

  openText[i] = NULL;
}

int getInt(String mess) {

  int input;
  int num = 0;
  int last = 0;

  do {
    delay(200);
    input = read_LCD_buttons();

    switch (input) {
      case btnNONE:
        continue;
      case btnUP:
        last = 1;
        num += last;
        break;
      case btnRIGHT:
        last = 5;
        num += last;
        break;
      case btnDOWN:
        last = 10;
        num += last;
        break;
      case btnLEFT:
        num -= last;
        last = 0;
        break;
      case btnSELECT:
        break;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(mess);
    lcd.setCursor(0, 1);
    lcd.print(num);

  }
  while (input != btnSELECT);

  return num;
}

