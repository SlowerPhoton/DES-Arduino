/**
   @file
   functions used to manipulate with the key
*/

void generateKey() {

  // for each scrambler and the reflector generate a key
  for (int scr = 0; scr < 4; scr++) {

    // fill the array with all possible values
    int toMatch[26];
    for (int i = 0; i < 26; i++)
      toMatch[i] = i;

    // to save the final randomly generated pairs
    int pairs[26];

    // randomly couple (match) numbers from toMatch
    /*
     *    just for 25 letters, it goes from end to beginning, so the letter A is left
     *    it is because there could be just 0 left for A which is also 0, so it would get paired with itself
     *    so we couple it after all other letters are coupled
     */
    for (int i = 25; i > 0; i--) {

      // what number from toMatch will be used to couple
      int a = random(0, i);

      // find a-th unused number different from the letter it represents (so B can't get paired with 1)
      int j;
      for (j = 0; j < a + 1; j++) {
        if (toMatch[j] == -1 || toMatch[j] == i) {
          a++;
        }
      }
      // save this randomly chosen number to pairs (filled from end to beginning)
      pairs[i] = toMatch[j - 1];
      toMatch[j - 1] = -1;
    }

    // find number to match with number that represents A
    for (int j = 0;; j++) {
      if (toMatch[j] != -1) {
        // if there is 0 left for it in order to avoid duplication exchange values with another random number
        if (toMatch[j] == 0) {
          int a = random(1, 25);
          toMatch[j] = pairs[a];
          pairs[a] = 0;
          break;
        }
        else {
          pairs[0] = toMatch[j];
          break;
        }
      }
    }

    // for each letter
    for (int i = 0; i < 26; i++) {

      // find where the letter i stored in pairs is
      for (int j = 0;; j++) {

        if (pairs[j] == i) {

          // somehow works (no idea)
          if (j % 2 == 0) {
            scramblers[scr][i] = pairs[j + 1];
            break;
          }
          //  *** POTENTIALLY INCORRECT PIECE OF CODE ***
          else {
            scramblers[scr][i] = pairs[j - 1];
            break;
          }

        }
      }
    }

  }

  // key was set
  keySet = true;

  displayLong("key generated");
}
