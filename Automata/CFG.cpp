#include "CFG.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace rn = std::ranges;

namespace fatpound::automata
{
    auto CFG::ParseFromFile(const String& filename) -> Vector<Pair<String, Vector<String>>>
    {
        std::ifstream input_file(filename);

        if ( ! input_file.is_open())
        {
            throw std::runtime_error("Input file cannot be opened for [InputtingCFG]!");
        }

        /////////////
        Vector<char> alphabet;

        {
            std::stringstream ss;

            String str;
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

        /////////////////////////////////////////
        Vector<Pair<String, Vector<String>>> cfgs;

        {
            const String arrow = "-->";
            String str;

            while (std::getline(input_file, str, ','))
            {
                const auto it = rn::remove_if(str, [](const auto& ch) -> bool { return std::isspace(ch); });

                str.erase(it.begin(), it.end());

                const std::size_t index = str.find(arrow);

                if (index != String::npos)
                {
                    String word(str.cbegin(), str.cbegin() + index);

                    str.erase(0, index + arrow.length());

                    Vector<String> leaves;

                    std::istringstream iss(str);

                    String tempstr;

                    while (std::getline(iss, tempstr, '|'))
                    {
                        if (rn::find(leaves, tempstr) == leaves.cend())
                        {
                            for (const auto& ch : tempstr)
                            {
                                if (std::islower(ch) && rn::find(alphabet, ch) == alphabet.cend())
                                {
                                    throw std::runtime_error("The letter " + String{ ch } + " is not in the alphabet!");
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

    void CFG::Print(const Vector<String>& results)
    {
        Vector<String> finals;
        Vector<String> repeaters;

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
    void CFG::Print(const Vector<Pair<String, bool>>& results)
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