/*******************************************************************************/
/*                                                                             */
/*             >::     ::<                                                     */
/*            :+:     :+:                                                      */
/*           +:+     +:+                                                       */
/*          ##+###+##+                                                         */
/*         #+     +#+                                                          */
/*        #+#     #+#                                                          */
/*   RSA.###     ###                                                           */
/*                                                                             */
/*                                                                             */
/*   By: fatpound                                                              */
/*                                                                             */
/*   Created: 29/05/2022 19:08:52 by fatpound                                  */
/*   Updated: 09/06/2022 19:27:06                                              */
/*                                                                             */
/*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y) (x == y ? 0 : (x ^= y ^= x ^= y))

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x > y ? y : x)

#define U64 unsigned long long

U64 int Power(U64 int x, U64 int y)
{
	U64 int p = 1;
	
	while (y--)
	{
		p *= x;
	}
	
	return (p);
}

U64 int GCD(U64 int x, U64 int y)
{
	return (y ? GCD(y, x % y) : x);
}

U64 int MMI(U64 int a, U64 int b, U64 int s0, U64 int s1)
{
	return (b ? MMI(b, a % b, s1, s0 - s1 * (a / b)) : s0);
}

U64 int IsPrime(U64 int n)
{
	if (n < 4) return (n > 1);
	if (!(n & 1) || n % 3 == 0) return 0;
	
	U64 int i;
	
	for (i = 5; i * i < (n + 1); i += 6)
	{
		if (n % i == 0 || n % (i + 2) == 0)
		{
			return 0;
		}
	}
	
	return 1;
}

U64 int NextPrime(U64 int x)
{
	while (!IsPrime(x++));
	
	return (--x);
}

void RSA(U64 int M)
{
	U64 int i = 0, C, E, D, P, Q, t, flag = 0, product = 1, r1, r2;
	
	// rand() % 14 because the pow function cannot be applied to large powers in the C language. For now, 14 is enough
	while ((P = NextPrime(r1 = (U64 int) rand() % 14)) == (Q = NextPrime(r2 = (U64 int) rand() % 14)));
	U64 int N = P * Q, fi_N = (P - 1) * (Q - 1);
	
	while (GCD(E = (rand() % (fi_N - 2)) + 2, fi_N) != 1);
	D = MMI(E, fi_N, 1, 0);
	
	printf("\n  r1  = %2llu      P = %2llu\n  r2  = %2llu      Q = %2llu\n\n(P * Q)           =    N  = %llu\n(P - 1) * (Q - 1) = fi(N) = %llu\n\n1 <   E < fi(N)\n1 < %3llu < %llu\n\nGCD(%llu, %llu) = 1\n\nD = %llu", r1, P, r2, Q, N, fi_N, E, fi_N, E, fi_N, D);
	
	for (; i < 2; i++, flag = 0, product = 1)
	{
		t = (i ? C : M);
		
		while ((i ? D : E) > 4)
		{
			if ((i ? D : E) & 1)
			{
				product *= t;
				
				if (flag = !flag)
				{
					product %= N;
				}
			}
			
			i ? (D >>= 1) : (E >>= 1);
			
			t = (t * t) % N;
		}
		
		if (!product)
		{
			product = 1;
		}
		
		i ? (M = (Power(t, D) * product) % N) : (C = (Power(t, E) * product) % N);
	}
	
	printf("\n\nC = %llu\nM = %llu", C, M);
}
