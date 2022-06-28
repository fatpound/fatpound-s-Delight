#define SWAP_P(x, y) (*x == *y ? *x = *y : (*x ^= *y ^= *x ^= *y))

void R_BubbleSort(int *d, int size)
{
	if (size > 1)
	{
		int i;
		
		for (i = 0; i < size - 1; i++)
		{
			if (d[i] > d[i + 1])
			{
				SWAP_P(&d[i], &d[i + 1]);
			}
		}
		
		R_BubbleSort(d, size - 1);
	}
}