#include <avr/pgmspace.h>

bool encr = true;
int8_t debug = 0;

void lookUpInSBox(size_t which, byte *address, byte* binaryOutcome, size_t addressFrom){

    size_t* Byte;
    Byte = new size_t {addressFrom/8};
    addressFrom%=8;
    address+=*Byte;
    //if (debug == 0)Serial.println(*Byte);
    delete Byte;

    static const uint8_t SBoxes[8][4][16] PROGMEM = {

                             /*S1*/

   { {14,  4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7},
     { 0, 15,   7,  4,  14,  2,  13,  1,  10,  6,  12, 11,   9,  5,   3,  8},
     { 4,  1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,   3, 10,   5,  0},
     {15, 12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13}    },

                             /*S2*/

   { {15,  1,   8, 14,   6, 11,   3,  4,   9,  7,   2, 13,  12,  0,   5, 10,},
     { 3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5,},
     { 0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15,},
     {13,  8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9}    },

                             /*S3*/

   { {10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8,},
     {13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1,},
     {13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7,},
     { 1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12}     },

                             /*S4*/

   { { 7, 13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15,},
     {13,  8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9,},
     {10,  6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4,},
     { 3, 15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14}     },

                             /*S5*/

   { { 2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9,},
     {14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6,},
     { 4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14,},
     {11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3}     },

                             /*S6*/

   { {12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11,},
     {10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8,},
     { 9, 14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6,},
     { 4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13}     },

                             /*S7*/

   { { 4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1,},
     {13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6,},
     { 1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2,},
     { 6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12}     },

                             /*S8*/

   { {13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7,},
     { 1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2,},
     { 7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8,},
     { 2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11}     }

                        };

    // row corresponds to the binary number consisting of the first and last index of address
    bool *row;
    row = new bool[2];
    row[0] = bitValue( address, 0 + addressFrom );
    row[1] = bitValue( address, 5 + addressFrom );

      
            /*if (debug == 0){
              //debugArray(&answer, 0, 4);
              Serial.println(*address);
              Serial.println(addressFrom);
              Serial.println(row[0]);
              Serial.println(row[1]);
            }debug++;*/

    // column corresponds to the middle 4 bits of address
    bool *column;
    column = new bool[4];
    overwriteBit(column, address, 0, addressFrom + 1, 4);

    uint8_t number = SBoxes[which][toDecimal(row, 2)][toDecimal(column, 4)];
    delete[] row; delete[] column;

    // convert number to binary number saved in answer
    bool answer[4] = {0,0,0,0};
    uint8_t powOf2 = 8;
    for(short i = 0; i < 4; i++){
        if(number >= powOf2){
            answer[i] = 1;
            number -= powOf2;
        }

        powOf2/=2;
    }

    // copy answer to binaryOutcome
    overwriteBit(binaryOutcome, answer, 0, 0, 4);
}

void f(byte R[32/8], byte K[48/8], byte outcome[32/8]){
  Serial.println(F("F"));
    
    // expand each R from 32 to 48 bits to E
    static const uint8_t E_BIT[48] PROGMEM = {
                 32,     1,    2,     3,     4,    5,
                  4,     5,    6,     7,     8,    9,
                  8,     9,   10,    11,    12,   13,
                 12,    13,   14,    15,    16,   17,
                 16,    17,   18,    19,    20,   21,
                 20,    21,   22,    23,    24,   25,
                 24,    25,   26,    27,    28,   29,
                 28,    29,   30,    31,    32,    1
    };

    byte E [48/8];  
    for(size_t i = 0; i < 48; i++){
        insertBit( E, i, bitValue( R, E_BIT[i]-1 ) );
    }
    
    // XOR Kn and  E(Rn-1)
    byte KxorE[48/8]; 
    for (size_t i = 0; i < 48; i++){
        insertBit( KxorE, i, bitValue( K, i ) ^ bitValue( E, i ) );
    }

    // each array of 6 bits from KxorE is used as an address in S boxes, thus obtaining a 4-bit number
    byte S[32/8];
    for(short i = 0; i < 48; i+=6){
        byte answer; // only first 4 bits are always used
        lookUpInSBox(i/6, KxorE, &answer, i); // save what we find in S-boxes into answer (its first 4 bits)  
        overwriteBit(S, &answer, (i/6)*4, 0, 4);
    }
/*
    if (debug == 0){
      debugArray(S, 0, 32);
      debug = 3;
    }*/

    // now we use P to permute S[] to finally create the outcome
    static const uint8_t P[32] PROGMEM = {
                         16,   7,  20,  21,
                         29,  12,  28,  17,
                          1,  15,  23,  26,
                          5,  18,  31,  10,
                          2,   8,  24,  14,
                         32,  27,   3,   9,
                         19,  13,  30,   6,
                         22,  11,   4,  25
    };

    Serial.print("P");
    Serial.println(P[31]);

    for (size_t i = 0; i < 32; i++){
        //outcome[i] = S[P[i]-1];
        insertBit( outcome, i, bitValue( S, P[i]-1 ) );
    }

   // Serial.println(F("E"));
}

void encodeMessage(byte binaryMessage[64/8], byte encrypted[64/8]){
    // permute binaryMessage by IP to permutedMessage
    static const uint8_t IP[64] PROGMEM = {
            58,    50,   42,    34,    26,   18,    10,    2,
            60,    52,   44,    36,    28,   20,    12,    4,
            62,    54,   46,    38,    30,   22,    14,    6,
            64,    56,   48,    40,    32,   24,    16,    8,
            57,    49,   41,    33,    25,   17,     9,    1,
            59,    51,   43,    35,    27,   19,    11,    3,
            61,    53,   45,    37,    29,   21,    13,    5,
            63,    55,   47,    39,    31,   23,    15,    7
    };

    byte permutedMessage[64/8];

    for(int i = 0; i < 64; i++){
        insertBit( permutedMessage, i, bitValue( binaryMessage, IP[i]-1 ) );
    }
    delete[] binaryMessage;

    // create L0 and R0 by dividing permutedMessage, the second index represents L [0] for first 4 bytes and  R for last 4
    //byte LR[17][64/8]; // gonna be saved on EEPROM from index 96 to 17*64/8+96 = 232
    for (size_t address = 96; address < 96+8; address++){
      EEPROM.write( address, *(permutedMessage + address - 96) );
    }
    
    for(short i = 1; i <= 16; i++){
      Serial.println(i);

        // subkeys are on EEPROM (first 16*48/8 bytes that is first 96) so we need to load the current row first
        byte subkeys[48/8];
        if (encr)
          for (size_t address = (i-1)*6; address < (i-1)*6+6; address++){
            subkeys[address%6] = EEPROM.read( address );
          }
        else
          for (size_t address = (16-i)*6; address < (16-i)*6+6; address++){
            subkeys[address%6] = EEPROM.read( address );
          }

         // LR is on EEPROM so we need to load it first (begins at index 96, size is [17][64/8] bytes)
         byte LR[2][8];
         for (size_t address = 96+((i-1)*8); address < 96+((i-1)*8) + 16; address++){
           *(LR[0]+address-96) = EEPROM.read( address );
         } 
      
        overwrite(LR[1], LR[0]+4, 64/8/2); // Ln = Rn-1
        // Rn = Ln-1 + f(Rn-1,Kn):
        byte outcome[32/8];
        if(encr == true) // according to the choice of the user: encrypt or decrypt
            f(LR[0]+4, subkeys, outcome); // call the function f for Rn-1,Kn
        else
            f(LR[0]+4, subkeys, outcome); // call the function f for Rn-1,Kn
        //if (i == 1) debugArray(outcome, 0, 32);

        //XOR(addition, LR[0][i-1], outcome, 32);
        for (size_t i = 0; i < 32; i++){
            insertBit( outcome, i, bitValue( LR[0], i ) ^ bitValue( outcome, i ) );
        }

        // addition, which correspond to Ln-1 + f(Rn-1,Kn) is now copied to Rn
        overwrite(LR[1]+4, outcome, 32/8);

        // update LR on EEPROM
        for (size_t address = 96+(i-1)*8; address < 96+(i-1)*8+16; address++){
          EEPROM.write( address, *(LR[0] + address - 96) );
        }
        
    }
    //debugArray(LR[16], 0, 64);
    Serial.println(F("End of encr"));

    /*// R16L16 after the permutation by IP-1 corresponds to the encrypted/decrypted message C

    int IP_1[64] = {
            40,     8,   48,    16,    56,   24,    64,   32,
            39,     7,   47,    15,    55,   23,    63,   31,
            38,     6,   46,    14,    54,   22,    62,   30,
            37,     5,   45,    13,    53,   21,    61,   29,
            36,     4,   44,    12,    52,   20,    60,   28,
            35,     3,   43,    11,    51,   19,    59,   27,
            34,     2,   42,    10,    50,   18,    58,   26,
            33,     1,   41,     9,    49,   17,    57,   25
    };

    bool R16L16[64];
    overwrite(R16L16, LR[1][16], 32); // R16
    overwrite(R16L16 + 32, LR[0][16], 32); // L16

    bool C[64];
    permutation(IP_1, R16L16, C, 64);

    overwrite(encrypted, C, 64);*/
}
