int BinarySearch(int *d, int size, int n)
{
	int i, start = 0, end = size - 1;
	
	while (start <= end)
	{
		i = (start + end) / 2;
		
		if (d[i] == n)
		{
			return i;
		}
		else if (d[i] < n)
		{
			start = i + 1;
		}
		else
		{
			end = i - 1;
		}
	}
	
	return -1;
}
