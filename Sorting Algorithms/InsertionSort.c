#define SWAP_P(x, y) (*x == *y ? 0 : (*x ^= *y ^= *x ^= *y))

void InsertionSort(int *d, int n)
{
	int i, j;
	
	for (i = 1; i < n; i++)
	{
		for (j = i; (j - 1 >= 0) && (d[j] <= d[j - 1]); j--)
		{
			SWAP_P(&d[j], &d[j - 1]);
		}
	}
}
