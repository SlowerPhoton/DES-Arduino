/**
    @file
    functions used to manipulate with binary data
*/

/**
    divides a binary array into halves
    @param LB first half
    @param RB second half
*/
void divideBinary(bool binary[], size_t sizeOfBinary, bool LB[], bool RB[]) {
  size_t half = sizeOfBinary / 2;

  // LB - first half
  size_t i = 0;
  for (; i < half; i++) {
    LB[i] = binary[i];
  }

  // RB - second half
  for (; i < half * 2; i++) {
    RB[i - half] = binary[i];
  }
}

/**
    overwrites one array with another
    @param what what you want to overwrite
    @param with what you want to overwrite it
    @param noOfIndexes how many indexes you want to overwrite
*/
void overwrite(bool what[], bool with[], size_t noOfIndexes) {
  for (size_t i = 0; i < noOfIndexes; i++)
    what[i] = with[i];
}

