#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class CaesarChiper final
{
    public:
    CaesarChiper() = default;
    CaesarChiper(const std::string& plaintext)
        : m_plaintext(plaintext) {}

    void setPlaintext(const std::string& plaintext) { m_plaintext = plaintext; }
    std::string getPlaintext() const { return m_plaintext; }

    void generateChipertext(std::string plaintext)
    {
        if(plaintext.size() <= 0) 
        {
            std::cerr << "Zero-length plaintext has been passed\n";
            return;
        }

        makeStringUpper(plaintext);

        const std::size_t plaintextSize = plaintext.size();
        m_chipertext.resize(plaintextSize);
        for(std::size_t i = 0; i < plaintextSize; i++)
        {
            m_chipertext[i] = (char)(plaintext[i] - 'A' + 3) % 26 + 'A';
        }
    }

    void generateChipertext()
    {
        generateChipertext(m_plaintext);
    }
    
    std::string getChipertext() const { return m_chipertext; }

    private:
        std::string m_plaintext;
        std::string m_chipertext;

        void makeStringUpper(std::string& str)
        {
            for(std::size_t i = 0; i < str.size(); i++)
            {
                std::toupper(str[i]);
            }
        }
};
