#pragma once

#include <vector>
#include <string>

namespace fatpound::automata
{
    class CFG
    {
    public:
        static std::vector<std::pair<std::string, std::vector<std::string>>> ParseFromFile(const std::string& input_filename);

        static void Print(const std::vector<std::string>& results);
        static void Print(const std::vector<std::pair<std::string, bool>>& results);


    protected:


    private:
    };
}