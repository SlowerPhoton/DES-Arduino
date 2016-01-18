extern LiquidCrystals lcd;
void enOrDecrypt() {
    encr = false;
    std::cout << "Would you like to encrypt or decrypt? [E/D] ";
    char answer;
    std::cin >> answer;
    answer = toupper(answer);

    if(answer == 'E')
        encr = true;
}
