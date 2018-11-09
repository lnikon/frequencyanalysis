#include <iostream>
#include <fstream>
#include <sstream>
#include "freqan.hpp"
#include "caesar.hpp"

int main()
{
    std::fstream messageFile("message.txt");
    if(!messageFile.is_open()) {
        std::cerr << "Can't open message file\n";
        return -1;
    }

    std::stringstream messageStream;
    messageStream << messageFile.rdbuf();
    std::string plainText = messageStream.str();

    messageFile.close();

    CaesarChiper chiper(plainText);
    chiper.generateChipertext();
    std::cout << "Encrypted text: " << chiper.getChipertext() << '\n';
    
    FrequencyAnalizer fan;
    fan.setChipertext(chiper.getChipertext());
    fan.frequencyAnalysis();

    std::cout << "Cracked chipertext: " << fan.getPlaintext() << '\n';

    return 0;
}
