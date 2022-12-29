#define SWAP_P(x, y) (*x == *y ? 0 : (*x ^= *y ^= *x ^= *y))

void Heapify(int *d, int index, int n)
{
	int greater = index;
	
	if ((2 * index + 1 <= n) && (d[index] < d[2 * index + 1]))
	{
		greater = 2 * index + 1;
	}
	
	if ((2 * (index + 1) <= n) && (d[greater] < d[2 * (index + 1)]))
	{
		greater = 2 * (index + 1);
	}
	
	if (greater != index)
	{
		SWAP_P(&d[index], &d[greater]);
		Heapify(d, greater, n);
	}
}

void BuildHeap(int *d, int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		Heapify(d, i, n);
	}
}

void HeapSort(int *d, int n)
{
	while (n >= 2)
	{
		n--;
		BuildHeap(d, n);
		SWAP_P(&d[n], &d[0]);
	}
}
