#pragma once

#include <vector>
#include <string>

namespace fatpound::automata
{
    class CFG final
    {
    public:
        /*
        The input file should be in the following format :

        1st line: The languages' acceptable letters seperated by spaces
        2nd line: The languages are sepeareted by commas and are defined by their names followed by an arrow which is like this "-->"
                  and followed by the symbols of the language (terminals and non-terminals) seperated by a pipe character '|'

        Example:
        a b  c   d e
        S-->aa|bX|aXX,   X-->ab|b
        */
        static std::vector<std::pair<std::string, std::vector<std::string>>> ParseFromFile(const std::string& input_filename);

        static void Print(const std::vector<std::string>& results);
        static void Print(const std::vector<std::pair<std::string, bool>>& results);


    protected:


    private:
    };
}