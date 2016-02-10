#include <avr/pgmspace.h>

// rotates 28 bits to left
void leftShift(byte *toShift, uint8_t noOfShifts, byte* destination, bool L) {
  size_t fromBit; // because L and R share one byte, we need to consider the initial bit as well
  if (L) fromBit = 0;
  else fromBit = 28%8; // that's 4
  
  for (int i = 0; i < 28; i++) {
    insertBit(destination, fromBit + (i - noOfShifts + 28) % 28, bitValue(toShift, i + fromBit));
  }
}

void createSubkeys(byte *binaryKey) {
  const uint8_t pc_1[56] PROGMEM = {
    57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
  };
  byte* keyPermutation;
  keyPermutation = new byte[56/8];


  // according to pc_1 create from 64-bit key 56-bit keyPermutation
  for (size_t i = 0; i < 56; i++) {
    bool tmp = bitValue(binaryKey, pc_1[i] - 1); 
    insertBit(keyPermutation, i, tmp);
  }
  delete[] binaryKey;
    
  // C and D will be saved here: [index] [7 bytes] - first 28 bits are left part, the rest right part
  byte CD[16 + 1][56 / 8];
  
  // divide keyPermutation into halves to C0 a D0 - each consists of 28 bits
  divideBinaryBit(keyPermutation, 56, CD[0], CD[0]+28);
  delete[] keyPermutation; 
  
  // from C0, D0 and shifts make C1, D1 -> C16, D16
  const uint8_t shifts[16] PROGMEM = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
  for (size_t i = 1; i < 17; i++) {
    leftShift(CD[i - 1], shifts[i - 1], CD[i], true);
    leftShift(CD[i - 1]+3, shifts[i - 1], CD[i]+3, false); // we need to start from the beginning of the right half - that is 3 bytes + 4 bits (shift takes care of the bits)
  }

  // each subKey out of 16 is made from one out of 16 CD with the use of pc_2
  const uint8_t pc_2[48] PROGMEM = {
    14,    17,   11,    24,     1,    5,
    3,    28,   15,     6,    21,   10,
    23,    19,   12,     4,    26,    8,
    16,     7,   27,    20,    13,    2,
    41,    52,   31,    37,    47,   55,
    30,    40,   51,    45,    33,   48,
    44,    49,   39,    56,    34,   53,
    46,    42,   50,    36,    29,   32
  };

  byte subkeys[16][48/8];
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 48; j++) {
      insertBit( subkeys[i], j, bitValue( CD[i+1], pc_2[j] - 1 ) );
    }
  }

  for (size_t address = 0; address < 16*6; address++){
        EEPROM.write( address, *(subkeys[0] + address) );
  } 
}
