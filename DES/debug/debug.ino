void debugArray(int arr[], int arrSize, int lom){
    int i = 0;
    while(i < arrSize){
        std::cout << arr[i] << "\t";
        if((i+1)%lom == 0)
            std::cout << std::endl;

        i++;
    }
    std::cout << std::endl;
}

void debugArray(bool arr[], int arrSize, int lom){
    int i = 0;
    while(i < arrSize){
        std::cout << arr[i] << "\t";
        if((i+1)%lom == 0)
            std::cout << std::endl;

        i++;
    }
    std::cout << std::endl;
}

void debugArray(char arr[], int lom, bool character){
    unsigned int i = 0;
    while(i < strlen(arr)){
        if(character == true)std::cout << arr[i] << "\t";
        else std::cout << (int) arr[i] << "\t";

        if((i+1)%lom == 0)
            std::cout << std::endl;

        i++;
    }
    std::cout << std::endl;
}

void debugSubkeys(bool subKeys[16][48]){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 48; j++){
            std::cout << subKeys[i][j];
            if((j+1)%6==0)
                std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

