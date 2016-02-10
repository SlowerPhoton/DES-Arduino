bool encr;

void encodeMessage(bool binaryMessage[64], bool subkeys[16][48], bool encrypted[64]){
    // permute binaryMessage by IP to permutedMessage
    int IP[64] = {
            58,    50,   42,    34,    26,   18,    10,    2,
            60,    52,   44,    36,    28,   20,    12,    4,
            62,    54,   46,    38,    30,   22,    14,    6,
            64,    56,   48,    40,    32,   24,    16,    8,
            57,    49,   41,    33,    25,   17,     9,    1,
            59,    51,   43,    35,    27,   19,    11,    3,
            61,    53,   45,    37,    29,   21,    13,    5,
            63,    55,   47,    39,    31,   23,    15,    7
    };

    bool permutedMessage[64];

    for(int i = 0; i < 64; i++){
        permutedMessage[i] = binaryMessage[IP[i]-1];
    }

    // create L0 and R0 by dividing permutedMessage, the first index represents L [0], or R [1]
    bool LR[2][17][64/2];
    divideBinary(permutedMessage, 64, LR[0][0], LR[1][0]);



    for(int i = 1; i <= 16; i++){

        overwrite(LR[0][i], LR[1][i-1], 64/2); // Ln = Rn-1
        // Rn = Ln-1 + f(Rn-1,Kn):
        bool outcome[32];
        if(encr == true) // according to the choice of the user: encrypt or decrypt
            f(LR[1][i-1], subkeys[i - 1] /* NOTE: in my terminology I count the keys from 0*/, outcome); // call the function f for Rn-1,Kn
        else
            f(LR[1][i-1], subkeys[16-i] /* NOTE: in my terminology I count the keys from 0*/, outcome); // call the function f for Rn-1,Kn
        bool addition[32];
        XOR(addition, LR[0][i-1], outcome, 32);

        // addition, which correspond to Ln-1 + f(Rn-1,Kn) is now copied to Rn
        overwrite(LR[1][i], addition, 32);

    }

    // R16L16 after the permutation by IP-1 corresponds to the encrypted/decrypted message C

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

    overwrite(encrypted, C, 64);
}
