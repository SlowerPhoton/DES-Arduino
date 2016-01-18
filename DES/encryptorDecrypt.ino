/**
    @file
    functions used to decide whether encrypt or decrypt
*/


bool encr;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

/**
    asks the user whether he wishes to encrypt or decrypt @n
    stores the output in global bool @a encr
*/
void enOrDecrypt() {

    // prompt the user
    lcd.setCursor(0,0);
    lcd.print("UP to encrypt");
    lcd.setCursor(0,1);
    lcd.print("DOWN to decrypt");

    // check the pressed buttons as long as the user doesn't answer the prompt
    int answer = read_LCD_buttons();
    while(answer != btnUP and answer != btnDOWN){
        answer = read_LCD_buttons();
    }

    // set @c encr to the right value
    if (answer == btnUP)
      encr = true;
    else
      encr = false; 
}
