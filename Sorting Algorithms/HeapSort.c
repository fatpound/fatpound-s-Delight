#define SWAP_P(x, y) (*x == *y ? 0 : (*x ^= *y ^= *x ^= *y))

int i, greater;

void Heapify(int *d, int index, int n)
{
	greater = index;
	
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
	for (i = (n - 1) / 2; i >= 0; i--)
	{
		Heapify(d, i, n);
	}
}

void HeapSort(int *d, int n)
{
	while (n >= 2)
	{
		BuildHeap(d, n - 1);
		SWAP_P(&d[n - 1], &d[0]);
		n--;
	}
}