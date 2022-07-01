#define SWAP_P(x, y) (*x == *y ? 0 : (*x ^= *y ^= *x ^= *y))

int Div(int *d, int left, int right)
{
	int i, pivot = d[right], index = left - 1;
	
	for (i = left; i < right; i++)
	{
		if (dizi[i] <= pivot)
		{
			index++;
			SWAP_P(&d[i], &d[index]);
		}
	}
	
	index++;
	SWAP_P(&dizi[right], &d[index]);
	
	return index;
}

void QuickSort(int *d, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	
	int v = Div(dizi, left, right);
	
	QuickSort(d, left, v - 1);
	QuickSort(d, v + 1, right);
}
