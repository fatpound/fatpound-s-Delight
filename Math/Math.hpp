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
    concept Multiplicable = requires(T var1, T var2)
    {
        { var1 * var2 } -> std::same_as<T>;
    };

    template <typename T>
    concept Multiplicable_Noexcept = Multiplicable<T> and
    requires(T var1, T var2)
    {
        { var1 * var2 } noexcept;
    };

    template <Multiplicable T>
    inline constexpr auto Square(const T& var) noexcept(Multiplicable_Noexcept<T>)
    {
        return var * var;
    }
}
