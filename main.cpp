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
    std::string plaintext = messageStream.str();

    messageFile.close();

    CaesarChiper chiper(plaintext);
    chiper.generateChipertext();
    std::cout << "Encrypted text: " << chiper.getChipertext() << '\n';
    
    FrequencyAnalizer fan;

    fan.setPlaintext(plaintext);
    fan.setChipertext(chiper.getChipertext());

    fan.frequencyAnalysis();

    std::cout << "\n\nCracked chipertext: " << fan.getAnalyzedtext() << '\n';
    std::cout << "\n\nPlaintext is: " << fan.getPlaintext() << std::endl;

    const auto& [isValid, diffNum] = fan.compareResults();
    std::cout   << std::boolalpha
                << "Is analysis correct: " << isValid
                << "\nNumber of differences between positions: " << diffNum << std::endl;

    return 0;
}
