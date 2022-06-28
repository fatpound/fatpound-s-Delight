#define SWAP_P(x, y) (*x == *y ? 0 : (*x ^= *y ^= *x ^= *y))

int Bolum(int *dizi, int left, int right)
{
	int i, pivot = dizi[right], index = left - 1;
	
	for (i = left; i < right; i++)
	{
		if (dizi[i] <= pivot)
		{
			index++;
			SWAP_P(&dizi[i], &dizi[index]);
		}
	}
	
	index++;
	SWAP_P(&dizi[right], &dizi[index]);
	
	return index;
}

void QuickSort(int *dizi, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	
	int v = Bolum(dizi, left, right);
	
	QuickSort(dizi, left, v - 1);
	QuickSort(dizi, v + 1, right);
}
