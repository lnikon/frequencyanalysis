#include <iostream>
#include "freqan.hpp"

int main()
{
    FrequencyAnalizer anz;
    anz.setChipertext("Abrakadabra is still here! Please, call Dumbledore");
    std::cout << anz.getChipertext() << '\n';

    anz.frequencyAnalysis();
    return 0;
}
