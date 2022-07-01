int IsPrime(int x)
{
	if (x < 2) return 0;
	
	int i;
	
	for (i = 2; i <= x / 2; i++)
	{
		if (x % i == 0)
		{
			return 0;
		}
	}
	
	return 1;
}

int IsPrime2(int x)
{
	if (x == 2 || x == 5) return 1;
	if (x < 2 || (x % 10) & 1 == 0 || x % 10 == 5 || ISPOWOF2(x)) return 0;
	if (x % 3 == 0) return (x == 3);
	
	int i;
	
	for (i = 7; i * i < x + 1; i++)
	{
		if (x % i == 0)
		{
			return 0;
		}
	}
	
	return 1;
}

int k = 2; // Veya IsPrime4 fonksiyonuna TestPrime bağlanıp Global Değişkenden kurtarabiliriz
int IsPrime3(int value)
{
	if (k < value / 2)
	{
		return ((value % k++ != 0) & IsPrime3(value));
	}
	
	return 1;
}

int IsPrime4(int value, int k)
{
	if (k < value / 2)
	{
		return ((value % k) & IsPrime4(value, k + 1));
	}
	
	return 1;
}

int TestPrime(int x)
{
	return (IsPrime4(x, 2));
}

int IsPrime5(int n)
{
	if (n < 2) return 0;
	if (n % 2 == 0) return (n == 2);
	if (n % 3 == 0) return (n == 3);
	
	int i = 5, h = Floor(1 + sqrt(n));
	
	for (i = 7; i * i <= h; i++)
	{
		if (h % i == 0)
		{
			return 0;
		}
	}
	
	return 1;
}

int IsPrime6(int n)
{
	if (n < 4) return (n > 1);
	if (n % 2 == 0 || n % 3 == 0) return 0;
	
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

int NextPrime(int x)
{
	int i, t = 0;
	
	for (i = 2; i < x; i++)
	{
		if (x % i == 0)
		{
			t = i = 1;
			x++;
		}
	}
	
	return (t ? x : NextPrime(++x));
}

int PrevPrime(int x)
{
	int i, t = 0;
	
	for (i = 2; i < x; i++)
	{
		if (x % i == 0)
		{
			t = i = 1;
			x--;
		}
	}
	
	return (t ? x : PrevPrime(--x));
}

int ClosestPrime(int x)
{
	int a = x - PrevPrime(x), b = NextPrime(x) - x;
	
	return (a > b ? NextPrime(x) : (a < b ? PrevPrime(x) : 0));
}

int ClosestPrimeLocation(int x)
{
	int a = x - PrevPrime(x), b = NextPrime(x) - x;
	
	if (a < b) return -1;
	if (a == b) return 0;
	if (a > b) return 1;
}

int NthPrime(int n)
{
	int i = 0, j = 0;
	
	while (++i)
	{
		if (IsPrime(i)) j++;
		if (j == n) break;
	}
	
	return (i);
}

int NthPrime2(int value)
{
	int n = 0, c = 2;
	
	while (c < value)
	{
		n += 6;
		
		if (IsPrime(n + 1))
		{
			c++;
		}
		
		if (IsPrime(n - 1))
		{
			c++;
		}
	}
	
	return (n + 1);
}

int SumOfPrimeDivs(int x)
{
	int i, sop = 0;
	
	for (i = 3; i <= x; i += (i != 2 ? 2 : 1))
	{
		if (IsPrime(i))
		{
			while ((x % i) == 0)
			{
				sop += i;
				x /= i;
			}
		}
	}
	
	return (sop);
}

int SumOfPrimeDivsDigits(int x)
{
	int i, sopd = 0;
	
	for (i = 2; i <= x; i += (i != 2 ? 2 : 1))
	{
		if (IsPrime(i))
		{
			while ((x % i) == 0)
			{
				sopd += (DigitCount(i) != 1 ? DigitSum(i) : i);
				x /= i;
			}
		}
	}
	
	return (sopd);
}
