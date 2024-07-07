#pragma once

#include <vector>
#include <string>

namespace fatpound::automata
{
    /// <summary>
    /// Context-free Grammar parser and word generator
    /// </summary>
    class CFG final
    {
        template <typename T>
        using Vector = std::vector<T>;

        template <typename T1, typename T2>
        using Pair = std::pair<T1, T2>;

        using String = std::string;

    public:
        /// <summary>
        /// The input file should be in the following format :
        ///
        /// 1st line : The languages' acceptable letters seperated by spaces
        /// 2nd line : The languages are sepeareted by commas and are defined by their names followed by an arrow which is like this "-->"
        /// and followed by the symbols of the language(terminals and non - terminals) seperated by a pipe character '|'
        ///
        /// Example :
        /// a b  c   d e
        /// S --> aa | bX | aXX, X --> ab | b
        /// </summary>
        static auto ParseFromFile(const String& filename) -> Vector<Pair<String, Vector<String>>>;

        static void Print(const Vector<String>& results);
        static void Print(const Vector<Pair<String, bool>>& results);


    protected:


    private:
    };
}
