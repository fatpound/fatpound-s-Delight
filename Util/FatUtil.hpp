#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <ranges>
#include <concepts>

namespace fatpound::util
{
    template <class Container>
    void WriteToCout(const Container& container, const char* delimiter = " ")
    {
        std::ranges::copy(container, std::ostream_iterator<typename Container::value_type>(std::cout, delimiter));

        std::cout << '\n';
    }

    void PrintCombinations(const std::string& str, size_t n, const std::string& first = "")
    {
        if (n == 0)
        {
            std::cout << first << '\n';
            return;
        }

        for (size_t i = 0u; i < str.length(); ++i)
        {
            PrintCombinations(str.substr(i + 1, str.length()), n - 1, first + str[i]);
        }
    }
    void PrintPermutations(const std::string& str, size_t n, const std::string& first = "")
    {
        if (n == 0)
        {
            std::cout << first << '\n';
            return;
        }

        for (size_t i = 0u; i < str.length(); ++i)
        {
            PrintPermutations(str.substr(0, i) + str.substr(i + 1, str.length()), n - 1, first + str[i]);
        }
    }
}
