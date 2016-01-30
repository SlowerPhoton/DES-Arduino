/* represents the settings of scramblers, the last index represents the settings of the reflector */
int scramblers[3 + 1][26];

/* used to save the shift of scramblers */
int shift[3] = {0, 0, 0};

/* used to save the initial shift of rotors */
int rotor[3] = {0, 0, 0};

/* used to remember whether the key was set already */
bool keySet = false;

/* used to store the text to encrypt */
char openText[256] = "Fuck there is shit on my face";

/* used to store the encrypted message */
char encrypted[256];

void encrypt() {
  // check whether the key was set
  if (keySet == false) {
    displayMess(F("There is no key"));
    return;
  }

  // fill the openText
  getOpenText();

  // for each character of openText cypher
  for (int i = 0, n = strlen(openText); i < n; i++) {

    // make the current character of openText upper and save it to c
    int c = openText[i];
    c = toupper(c);

    // if the character is a letter otherwise do not change it and do not shift scramblers
    if (c >= 'A' and c <= 'Z') {

      // shift ('rotate') scramblers
      shift[0]++;
      if (shift[0] == 26) {
        shift[1]++;
        shift[0] = 0;

        if (shift[1] == 26) {
          shift[2]++;
          shift[1] = 0;

          if (shift[2] == 26) {
            shift[2] = 0;
          }
        }
      }


      // turn c into number - how far it is from 'A' in ASCII
      c = c - 'A';

      /*
         c now need to get through all 3 scramblers
         'reflect' from the reflector
         and go back through all the 3 scramblers again
      */
      // the trip to the reflector
      for (int j = 0; j < 3; j++)
      {

        // encrypt the letter according to the key in the j-th srambler
        if (c + shift[j] + rotor[j] >= 26)
        {
          // add shift to the number (made from the letter currently being encrypted), find it in the key in the current scrambler, change it according to it and subtract shift
          c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
        }
        else
          c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

        // if c is after subtracting shift less then 0 add 26 to return it back through 'Z'
        if (c < 0)
          c += 26;

      }

      // encrypt through the reflector
      c = scramblers[3][c];

      // the way back
      for (int j = 2; j >= 0; j--)
      {
        if (c + shift[j] + rotor[j] >= 26)
        {
          c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
        }
        else
          c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

        if (c < 0)
          c += 26;

      }

      // turn c back into a letter
      c += 'A';
    }


    // print the (possibly) encrypted character
    Serial.print((char) c);
    encrypted[i] = (char) c;
  }
  encrypted[strlen(openText)] = NULL;

  displayLong(encrypted);
}

void resetShift() {
  // reset shift to {0, 0, 0}
  for (int i = 0; i < 3; i++) {
    shift[i] = 0;
  }

  displayMess(F("reset done"));
}

