#pragma once

#include "../Math/Arithmetic.hpp"

#include <print>
#include <random>

using namespace fatpound::math;

namespace fatpound::cryptography
{
    void TestRSA(int64_t M)
    {
        int64_t r1;
        int64_t r2;

        int64_t P;
        int64_t Q;

        std::default_random_engine drng(std::random_device{}());
        std::uniform_int_distribution<int> idist(0, 13);

        do
        {
            r1 = idist(drng);
            P = NextPrime(r1);

            r2 = idist(drng);
            Q = NextPrime(r2);
        }
        while (P == Q);

        int64_t    N =  P * Q;
        int64_t fi_N = (P - 1) * (Q - 1);

        std::uniform_int_distribution<int> idist1(0, fi_N - 3);

        int64_t E;

        do
        {
            E = rand() % (fi_N - 2);
        }
        while (GCD(E + 2, fi_N) != 1);

        int64_t D = MMI(E, fi_N, 1, 0);

        std::println("r1 = {}", r1);
        std::println("r2 = {}", r2);
        std::println("P  = {}", P);
        std::println("Q  = {}", Q);
        std::println("(P * Q) = N = {}", N);
        std::println("(P - 1) * (Q - 1) = fi(N) = {}", fi_N);

        std::println("1 < E < fi(N) = {}", E);
        std::println("1 < {0} < {1}", E, fi_N);
        std::println("GCD({0}, {1}) = 1", E, fi_N);
        std::println("D = {}", D);

        bool flag = false;

        int64_t temp;
        int64_t product = 1i64;

        temp = M;

        while (E > 4)
        {
            if (E % 2 == 1)
            {
                product *= temp;

                if (flag = !flag)
                {
                    product %= N;
                }
            }

            E /= 2;
            temp = (temp * temp) % N;
        }

        int64_t C = (static_cast<int64_t>(std::pow(temp, E)) * product) % N;
        
        flag = false;
        temp = C;

        while (D > 4)
        {
            if (D % 2 == 1)
            {
                product *= temp;

                if (flag = !flag)
                {
                    product %= N;
                }
            }

            D /= 2;
            temp = (temp * temp) % N;
        }

        M = (static_cast<int64_t>(std::pow(temp, D)) * product) % N;

        std::println("");
        std::println("C = {}", C);
        std::println("M = {}", M);
    }
}