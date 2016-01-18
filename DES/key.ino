/**
    @file
    functions used to get and prepare the key
*/

/**
    converts a string to 8-byte key
    @param keyWord the string to be converted
    @param key array of 8 bytes to save the key
*/
void keyTo8Bytes(String keyWord, int key[8]){
  
   // prepare array S with numbers from 0 to 255
    int S[256];
    for(int i = 0; i < 256; i++){
        S[i] = i;
    }

    // shuffle S
    int j = 0;
    size_t lng = keyWord.length();
    for(int i = 0; i < 256; i++){
        j = (j + S[i] + keyWord[i % lng])%256;
        int pom = S[j];
        S[j] = S[i];
        S[i] = pom;
    }

    // use first 8 indexes from S (and shuffle them again)
    int i = 0;
    j = 0;
    for(int a = 0; a < 8; a++){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        int pom = S[i];
        S[i] = S[j];
        S[j] = pom;
        int keyByte = S[(S[i] + S[j]) % 256];
        key[a] = keyByte;
    }

}

/**
    gets string from the user and calls keyTo8Bytes to convert it into key
    @n calls keyTo8Bytes
    @param key array to save the key  
*/
void getKey(int key[8]){
    
    // prompt user to type in the key
    /* TODO */
    String keyWord = "Ubung macht den Meister.";

    // call keyTo8Bytes to fill key[]
    keyTo8Bytes(keyWord, key);
}

