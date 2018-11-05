#include <iostream>
#include "freqan.hpp"
#include "caesar.hpp"

int main()
{
    CaesarChiper chiper("please encrypt me!");
    chiper.generateChipertext();
    std::cout << "Encrypted text: " << chiper.getChipertext() << '\n';
    
    FrequencyAnalizer fan;
    fan.setChipertext(chiper.getChipertext());
    fan.frequencyAnalysis();

    std::cout << "Cracked chipertext: " << fan.getPlaintext() << '\n';

    return 0;
}
