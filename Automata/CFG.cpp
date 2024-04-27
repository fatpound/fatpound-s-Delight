#include "CFG.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <locale>
#include <stdexcept>

namespace rn = std::ranges;

namespace fatpound::automata
{
    std::vector<std::pair<std::string, std::vector<std::string>>> CFG::ParseFromFile(const std::string& input_filename)
    {
        std::ifstream input_file(input_filename);

        if ( ! input_file.is_open() )
        {
            throw std::runtime_error("Input file cannot be opened for [InputtingCFG]!");
        }

        /////////////
        std::vector<char> alphabet;

        {
            std::stringstream ss;

            std::string str;
            std::getline(input_file, str);

            ss << str;

            char ch;

            while (ss >> ch)
            {
                alphabet.emplace_back(ch);
            }

            rn::sort(alphabet);

            auto it = rn::unique(alphabet);
            alphabet.erase(it.begin(), it.end());
        }

        ////////////
        std::vector<std::pair<std::string, std::vector<std::string>>> cfgs;

        {
            const std::string arrow = "-->";
            std::string str;

            while (std::getline(input_file, str, ','))
            {
                const auto it = rn::remove_if(str, [](const auto& ch) -> bool { return std::isspace(ch); });

                str.erase(it.begin(), it.end());

                const std::size_t index = str.find(arrow);

                if (index != std::string::npos)
                {
                    std::string word(str.cbegin(), str.cbegin() + index);

                    str.erase(0, index + arrow.length());

                    std::vector<std::string> leaves;

                    std::istringstream iss(str);

                    std::string tempstr;

                    while (std::getline(iss, tempstr, '|'))
                    {
                        if (rn::find(leaves, tempstr) == leaves.cend())
                        {
                            for (const auto& ch : tempstr)
                            {
                                if (std::islower(ch) && rn::find(alphabet, ch) == alphabet.cend())
                                {
                                    throw std::runtime_error("The letter " + std::string{ ch } + " is not in the alphabet!");
                                }
                            }

                            leaves.push_back(tempstr);
                        }
                    }

                    cfgs.emplace_back(std::move(word), std::move(leaves));
                }
            }
        }

        return cfgs;
    }

    void CFG::Print(const std::vector<std::string>& results)
    {
        std::vector<std::string> finals;
        std::vector<std::string> repeaters;

        for (const auto& str : results)
        {
            if (rn::find(finals, str) == finals.cend())
            {
                finals.push_back(str);
            }
            else if (rn::find(repeaters, str) == repeaters.cend())
            {
                repeaters.push_back(str);
            }
        }

        if (finals.size() > 0u)
        {
            for (const auto& str : finals)
            {
                std::cout << str << '\n';
            }
        }

        if (repeaters.size() > 0u)
        {
            std::cout << "\nRepeaters :\n\n";

            for (const auto& str : repeaters)
            {
                std::cout << str << '\n';
            }
        }

        std::cout << '\n';
    }
    void CFG::Print(const std::vector<std::pair<std::string, bool>>& results)
    {
        for (const auto& item : results)
        {
            if (item.second == true)
            {
                std::cout << item.first << '\n';
            }
        }
    }
}