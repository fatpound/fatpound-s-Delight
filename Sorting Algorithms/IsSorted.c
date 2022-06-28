int IsSorted(int *d, int n)
{
	int i, count[2] = { 0, 0 };
	
	for (i = 0; i < n - 1; i++)
	{
		if (d[i] == d[i + 1])
		{
			count[0]++;
			count[1]++;
		}
		else count[(d[i] < d[i + 1] ? 0 : 1)]++;
	}
	
	return (count[0] == n - 1 ? -1 : (count[1] == n - 1 ? 1 : 0));
}
