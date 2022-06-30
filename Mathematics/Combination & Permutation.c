int Factorial(int x)
{
	return (x ? x * Factorial(x - 1) : 1);
}

int Combination1(int x, int y)
{
	return (Factorial(x) / (Factorial(y) * Factorial(x - y)));
}

// shoutout to Weylyn...
double Combination2(double x, double y)
{
	if (x == y || x == 0 || y == 0) return 1;
	if (y == 1 || y == x - 1) return x;
	
	return ((x / y) * Combination2(--x, --y));
}

int Combination3(int n, int k)
{
	if (k == 0 || k == n) return 1;
	if (k < 0 || k > n) return -1;

	return (Combination3(n - 1, k) + Combination3(n - 1, k - 1));
}

int Permutation1(int x, int y)
{
	return (Factorial(x) / Factorial(x - y));
}

int Permutation2(int x, int y)
{
	return (Factorial(y) * Combination1(x, y));
}

double Permutation3(double x, double y)
{
	if (x == y || x == 0 || y == 0) return 1;
	if (y == 1) return x;
	
	return ((x / y) * y * Permutation3(--x, --y));
}

int Permutation4(int n, int k)
{
	if (k == 0) return 1;
	if (k < 0 || k > n) return -1;

	return (n * Permutation4(n - 1, k - 1));
}
