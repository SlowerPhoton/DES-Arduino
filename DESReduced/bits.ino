// the real integer pow
int ipow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

// returns the value of n-th int from an array of bytes
bool bitValue ( byte* bytes, size_t n )
{
  size_t byteNum = n / 8;
  n %= 8;

  byte Byte = *(bytes + byteNum);

  Byte >>= (8-n-1);
  byte mask = 1;
  Byte &= mask;
  return Byte;
}

// inserts a bit at a given position
void insertBit ( byte* bytes, size_t n, bool value )
{
  size_t byteNum = n / 8;
  n %= 8;

  if ( value )
  {
      byte mask = ipow(2, 8-n-1);
      *(bytes+byteNum) |= mask;
  }
  else
  {
      byte mask = 255-ipow(2, 8-n-1);
      *(bytes+byteNum) &= mask;
  }
}

// size of binary is in bytes
void divideBinary(byte binary[], size_t sizeOfBinary, byte LB[], byte RB[]) {
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

// size of binary is in bits
void divideBinaryBit(byte* binary, size_t nmOfBits, byte* LB, byte* RB) {
  size_t half = nmOfBits / 2;

  // LB - first half
  size_t i = 0;
  for (; i < half; i++) {
    bool tmp = bitValue(binary, i);
    insertBit(LB, i, tmp);
  }

  // RB - second half
  for (; i < half * 2; i++) {
    bool tmp = bitValue(binary, i);
    insertBit(LB, i, tmp);
  }
}

void overwrite(byte what[], byte with[], size_t noOfIndexes){
    for (size_t i = 0; i < noOfIndexes; i++)
        what[i] = with[i];
}

void overwriteBit(byte *what, byte *with, size_t fromWhat, size_t fromWith, size_t noOfBits){
    for (size_t i = 0; i < noOfBits; i++)
        insertBit( what, fromWhat + i, bitValue( with, fromWith + i ) );
}

void overwriteBit(bool what[], byte *with, size_t fromWhat, size_t fromWith, size_t noOfBits){
    for (size_t i = 0; i < noOfBits; i++)
        what[i + fromWhat] = bitValue( with, fromWith + i );
}

void overwriteBit(byte *what, bool with[], size_t fromWhat, size_t fromWith, size_t noOfBits){
    for (size_t i = 0; i < noOfBits; i++){
        insertBit( what, fromWhat + i, with[ fromWith + i] );
    }
}

/*void overwriteBit(byte *what, byte *with, size_t fromWhat, size_t fromWith, size_t noOfBits){
    for (size_t i = 0; i < noOfBits; i++)
        insertBit( what, fromWhat + i, with[ fromWith + i] );
}*/


bool XOR(bool a, bool b){
    return a ^ b;
}

/*
void XOR(byte where[], byte arr1[], byte arr2[], size_t noOfBits){
    for(size_t i = 0; i < noOfBits; i++){
        where[i] = arr1[i] ^ arr2[i];
    }
}*/

int toDecimal(bool binary[], int noOfNumbers){
    int powOf2 = 1;
    int decimal = 0;

    for(int i = noOfNumbers-1; i >= 0; i--){
        decimal += powOf2*binary[i];
        powOf2*=2;
    }

    return decimal;
}

