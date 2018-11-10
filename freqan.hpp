#pragma once

#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <utility>
#include <tuple>

class FrequencyAnalizer final
{
    public:
        FrequencyAnalizer()
        {
            m_freq_vec = convert_map_to_vector(FREQ_MAP);
        }
        ~FrequencyAnalizer() = default;
        FrequencyAnalizer(const FrequencyAnalizer&) = default;
        FrequencyAnalizer& operator=(const FrequencyAnalizer&) = default;
        FrequencyAnalizer(FrequencyAnalizer&&) = default;
        FrequencyAnalizer& operator=(FrequencyAnalizer&&) = default;

        FrequencyAnalizer(const std::string& chipertext)
            : m_chipertext(chipertext) 
        {
            m_freq_vec = convert_map_to_vector(FREQ_MAP);
        }

        auto getChipertext() { return m_chipertext; }
        void setChipertext(const std::string& chipertext) { m_chipertext = chipertext; }

        auto getPlaintext() { return m_plaintext; }
        void setPlaintext(const std::string& plaintext) 
        {
            m_plaintext = preprocessPlaintext(plaintext);
        }

        auto getAnalyzedtext() { return m_analyzedtext; }
        void setAnalyzedtext(const std::string& analyzedtext) { m_analyzedtext = analyzedtext; }

        void frequencyAnalysis()
        {
            auto chipertextFreqMap = generate_freq_map();
            auto chipertextFreqVec = convert_map_to_vector(chipertextFreqMap);            

            std::string resultOfAnalysis;
            resultOfAnalysis.resize(m_chipertext.size());
            
            auto it = std::begin(m_freq_vec);
            for(const auto& [letter, freq] : chipertextFreqVec)
            {
                for(std::size_t i = 0; i < resultOfAnalysis.size(); i++)
                {
                    if(m_chipertext[i] == letter)
                    {
                        resultOfAnalysis[i] = it->first;
                    }
                }

                it++;
            }

            m_analyzedtext = resultOfAnalysis;
        }

        std::tuple<bool, std::size_t> compareResults()
        {
            if(m_analyzedtext.empty())
            {
                std::cerr << "Can't find results of frequency analysis\n";
                return std::make_tuple(false, 0);
            }

            if(m_plaintext.empty())
            {
                std::cerr << "No plaintext specified\n";
                return std::make_tuple(false, 0);
            }

            std::size_t diffNum = 0;
            for(std::size_t i = 0; i < m_plaintext.size(); i++)
            {
                if(m_plaintext[i] != m_analyzedtext[i])
                {
                    diffNum++;
                }
            }
            
            bool isValid = true;
            if(diffNum > 0)
            {
                isValid = false;
            }

            return std::make_tuple(isValid, diffNum);
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
        std::vector<std::pair<char, double>> m_freq_vec;
        std::string m_chipertext;
        std::string m_plaintext;
        std::string m_analyzedtext;

        std::map<char, double> generate_freq_map() const
        {
            if(m_chipertext.empty())
            {
                std::cerr << "Empty chipertext specified\n";
                return std::map<char, double>();
            }

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

            if(chipertextLen == 0)
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

        std::vector<std::pair<char, double>> convert_map_to_vector(const std::map<char, double>& mapToConvert)
        {
            std::vector<std::pair<char, double>> freq_vec;
            std::copy(std::begin(mapToConvert), std::end(mapToConvert), 
                    std::back_inserter<decltype(freq_vec)>(freq_vec));

            std::sort(std::begin(freq_vec), std::end(freq_vec), [](auto& left, auto& right) { return left.second > right.second; });

            return freq_vec; 
        }

        std::string preprocessPlaintext(std::string dirtytext)
        {
            if(dirtytext.empty())
            {
                // This function is a internal part
                // of our implementation, so it shouldn't 
                // pass any info about preprocessiong to
                // the outside
                // Just return :)
                return std::string("");
            }

            std::string plaintext;
            for(std::size_t i = 0; i < dirtytext.size(); i++)
            {
                if(isalpha(dirtytext[i]))
                {
                    char ch = std::toupper(dirtytext[i]);
                    plaintext.append(1, ch);
                }
            }

            return plaintext;
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
