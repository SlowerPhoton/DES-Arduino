void debugArray(byte *arr, size_t from, size_t to){
    for (size_t i = from; i < to; i++){
      Serial.print('\t');
      Serial.print(i);
      Serial.print(": ");
      Serial.println(bitValue(arr, i));
    }
}
