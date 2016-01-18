/**
    @file
    functions used to get and prepare the message
*/

/**
    counts how many characters we need to add to the message in order to be a multiple of 8 characters long (64 bits)
*/
int padding(int numbersInMessage){
    return (8 - numbersInMessage%8)%8;
}

/**
    expands the message in order to be a multiple of 8 ints (bytes) long
    @n adds @c 0 in the empty indexes
*/
void messageExpand(String *message){

    // count how many characters we will have to add
    int numbersInMessage = message->length();
    int pad = padding(numbersInMessage);

    // append '0'
    for(int i = numbersInMessage; i < pad + numbersInMessage; i++){
        message->concat("0");
    }

}

/** \brief converts the message from string into binary message
 *
 */
void messageToBinary(String message, bool binaryMessage[]){

    unsigned char powOf2;
    size_t noOfNumbers = message.length();
    for(unsigned int i = 0; i < noOfNumbers; i++){
        bool tank[8] = {0,0,0,0,0,0,0,0};
        unsigned char toProcess = message[i];
        // 8 bits -> the biggest possible number (unsigned) is 255
        // the first position represents 128
        int n;
        for(powOf2 = 128, n=0; n<8; powOf2/=2, n++){
            if(powOf2 <= toProcess){
                toProcess -= powOf2;
                tank[n] = 1;
            }
        }

        // copy tank[] to the corresponding position in binaryMessage[]
        for(int j = 0; j < 8; j++)
            binaryMessage[i*8+j] = tank[j];
    }
}


