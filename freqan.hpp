#pragma once

#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <utility>

class FrequencyAnalizer final
{
    public:
        FrequencyAnalizer() = default;
        ~FrequencyAnalizer() = default;
        FrequencyAnalizer(const FrequencyAnalizer&) = default;
        FrequencyAnalizer& operator=(const FrequencyAnalizer&) = default;
        FrequencyAnalizer(FrequencyAnalizer&&) = default;
        FrequencyAnalizer& operator=(FrequencyAnalizer&&) = default;

        FrequencyAnalizer(const std::string& chipertext)
            : m_chipertext(chipertext) 
        {
            std::vector<std::pair<char, double>> vec;

            std::copy(std::begin(FREQ_MAP), std::end(FREQ_MAP), 
                    std::back_inserter<decltype(vec)>(vec));

            std::sort(std::begin(vec), std::end(vec), [](auto& left, auto& right) {
                    return left.second > right.second; });

            for(const auto& [word, freq] : vec)
            {
                std::cout << "{ " << word << " : " << freq << " }\n";
            }
        }

        auto getChipertext() { return m_chipertext; }
        void setChipertext(const std::string& chipertext) { m_chipertext = chipertext; }

        auto getPlaintext() { return m_plaintext; }
        void setPlaintext(const std::string& plaintext) { m_plaintext = plaintext; }

        void frequencyAnalysis()
        {
            auto chipertextFreqMap = generate_freq_map();
            printFreqMap(chipertextFreqMap);
            printFreqMap();
        }

        void printFreqMap() const
        {
            std::cout << '\n';
            for(const auto& item : FREQ_MAP)
            {
                std::cout << "{ " << item.first << " : " << item.second << "}\n";
            }
            std::cout << '\n';
        }

        void printFreqMap(std::map<char, double> freq_map) const
        {
            std::cout << '\n';
            for(const auto& cit : freq_map)
            {
                std::cout << "{ " << cit.first << " : " << cit.second << "}\n";
            }
            std::cout << '\n';
        }

    private:
        static const std::map<char, double> FREQ_MAP; 
        std::string m_chipertext;
        std::string m_plaintext;

        std::map<char, double> generate_freq_map() const
        {
            std::map<char, double> freq_map;

            std::size_t chipertextLen = 0;
            for(auto ch : m_chipertext) 
            {
                if(isalpha(ch))
                {
                    freq_map[std::toupper(ch)]++;    
                    chipertextLen++;
                }
            }

            if(chipertextLen <= 0)
            {
                std::cerr << "Empty chipertext specified\n";
                return decltype(freq_map)();
            }

            for(auto& [letter, count] : freq_map)
            {
                count = count / static_cast<double>(chipertextLen);
            }

            return freq_map;
        }
};

const std::map<char, double> FrequencyAnalizer::FREQ_MAP = 
{
    {'A', 0.0817}, {'N', 0.0675},
    {'B', 0.0150}, {'O', 0.0751},
    {'C', 0.0278}, {'P', 0.0193},
    {'D', 0.0425}, {'Q', 0.0010},
    {'E', 0.1270}, {'R', 0.0599},
    {'F', 0.0223}, {'S', 0.0633},
    {'G', 0.0202}, {'T', 0.0906},
    {'H', 0.0609}, {'U', 0.0276},
    {'I', 0.0697}, {'V', 0.0098},
    {'J', 0.0015}, {'W', 0.0236},
    {'K', 0.0077}, {'X', 0.0015},
    {'L', 0.0403}, {'Y', 0.0197},
    {'M', 0.0241}, {'Z', 0.0007}
};
