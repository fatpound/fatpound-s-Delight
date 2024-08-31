#pragma once

#include <cmath>

#include <limits>
#include <numeric>
#include <numbers>
#include <concepts>

namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> or std::floating_point<T>;

    template <typename T>
    inline auto Square(const T& x)
    {
        return x * x;
    }
}