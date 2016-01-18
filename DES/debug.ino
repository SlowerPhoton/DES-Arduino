void debugArray(int arr[], size_t arrSize, int lom) {
  int i = 0;
  while (i < arrSize) {
    Serial.print(arr[i]);Serial.flush();
    Serial.print('\t');Serial.flush();
    if ((i + 1) % lom == 0)
      Serial.print("\n");Serial.flush();

    i++;
  }
  Serial.println();
}

void debugArray(bool arr[], size_t arrSize, int lom) {
  int i = 0;
  while (i < arrSize) {
    Serial.print(arr[i]);Serial.flush();
    Serial.print('\t');Serial.flush();
    if ((i + 1) % lom == 0)
      Serial.println();Serial.flush();

    i++;
  }
  Serial.println();
}

void debugArray(char arr[], int lom, bool character) {
  unsigned int i = 0;
  while (i < strlen(arr)) {
    if (character == true)Serial.print(arr[i] + "\t");
    else Serial.print((int) arr[i] + "\t");
    Serial.flush();

    if ((i + 1) % lom == 0)
      Serial.println();
      Serial.flush();
    i++;
  }
  Serial.println();
  Serial.flush();
}

void debugSubkeys(bool subKeys[16][48]){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 48; j++){
            Serial.print(subKeys[i][j]);
            Serial.flush();
            if((j+1)%6==0)
                Serial.print("\t");
                Serial.flush();
        }
        Serial.println();
        Serial.flush();
    }
}

