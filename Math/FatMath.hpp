#pragma once

#include <cmath>
#include <cassert>

#include <limits>
#include <numeric>
#include <numbers>
#include <concepts>

namespace fatpound::math
{
    template <typename T>
    concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <std::signed_integral T>
    T GCD(T x, T y)
    {
        while (y != 0)
        {
            const T temp = x % y;
            x = y;
            y = temp;
        }

        return x;
    }
    template <std::signed_integral T>
    T LCM(T x, T y)
    {
        return (x * y) / GCD<T>(y, x % y);
    }
    template <std::signed_integral T>
    T MMI(T a, T b, T s0, T s1)
    {
        return (b ? MMI<T>(b, a % b, s1, s0 - s1 * (a / b)) : s0);
    }

    template <typename T>
    inline auto sq(const T& x)
    {
        return x * x;
    }

    template <std::signed_integral T>
    inline bool IsPowerOf2(const T n)
    {
        return ! (n & (~-n));
    }

    template <std::signed_integral T>
    bool IsPrime(const T& n)
    {
        if (n < static_cast<T>(4))
        {
            return n > 1;
        }

        if (n % 2 == 0 || n % 3 == 0)
        {
            return false;
        }

        const T m = n + 1;

        for (T i = 5; sq(i) < m; i += 6)
        {
            if ((n % i == 0) || (n % (i + 2) == 0))
            {
                return false;
            }
        }

        return true;
    }
    template <std::signed_integral T>
    T NextPrime(T n)
    {
        if (n % 2 == 0)
        {
            ++n;
        }

        while ( ! IsPrime<T>(n) )
        {
            n += 2;
        }

        return n;
    }
    template <std::signed_integral T>
    T PrevPrime(T n)
    {
        if (n % 2 == 0)
        {
            --n;
        }

        while ( ! IsPrime<T>(n) )
        {
            n -= 2;
        }

        return n;
    }
    template <std::signed_integral T>
    T NthPrime(T n)
    {
        assert(n > 0);

        if (n == 1)
        {
            return 2;
        }

        T i = 3;
        T counter = 1;

        while (true)
        {
            if (IsPrime(i))
            {
                if (++counter == n)
                {
                    break;
                }
            }

            i += 2;
        }

        return i;
    }

    template <std::floating_point T>
    inline T wrap_angle(T theta)
    {
        const T twoPi = 2 * std::numbers::pi_v<T>;

        const T modded = std::fmod(theta, twoPi);

        return modded > std::numbers::pi_v<T>
            ? modded - twoPi
            : modded
            ;
    }
}