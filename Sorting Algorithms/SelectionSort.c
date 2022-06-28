#define SWAP_P(x, y) (*x == *y ? *x = *y : (*x ^= *y ^= *x ^= *y))

void SelectionSort(int *d, int n) // O(n * n)
{
	int index, j, min;
	
	for (index = 0; index < n - 1; index++)
	{
		for (j = index + 1, min = index; j < n; j++)
		{
			if (d[min] > d[j])
			{
				min = j;
			}
		}
		
		SWAP_P(&d[index], &d[min]);
	}
}