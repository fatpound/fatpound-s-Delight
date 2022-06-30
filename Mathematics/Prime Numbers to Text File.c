#include <stdio.h>
#include <conio.h>

int IsPrime(int n)
{
	if (n < 4) return (n > 1);
	if (!(n & 1) || n % 3 == 0) return 0;
	
	int i;
	
	for (i = 5; i * i < n + 1; i += 6)
	{
		if (n % i == 0 || n % (i + 2) == 0)
		{
			return 0;
		}
	}
	
	return 1;
}

int main()
{
	FILE *fp = fopen("primes.txt", "w");
	int i;
	
	fprintf(fp, "2\n");
	
	for (i = 3; i < 1000000; i += 2)
	{
		if (IsPrime(i))
		{
			fprintf(fp, "%d\n", i);
		}
	}
	
	return 0;
}