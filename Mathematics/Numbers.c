int DigitCount(int n)
{
	return (n > 0 ? (1 + DigitCount(n / 10)) : 0);
}

int DigitSum(int value)
{
	return (value > 0 ? (value % 10 + DigitSum(value / 10)) : 0);
}

int DigitSumOfRange(int start, int end)
{
	return (start < end ? (DigitSum(start) + DigitSumOfRange(start + 1, end)) : 0);
}

int IsEven(int x)
{
	return (!(x & 1));
}

int IsOdd(int x)
{
	return (x & 1);
}

int IsOppositeSigns(int x, int y)
{
	return ((x ^ y) < 0);
}

int IsSmith(int x)
{
	return (DigitSum(x) == SumOfPrimeDigits(x) ? 1 : 0);
}

int IsMagic(int x)
{
	return  (DigitSum(x) * RevNum(DigitSum(x)) == x ? 1 : 0);
}

int AllDigitsDiffer(int x)
{
	int i, j, count = DigitCount(x);
	int d[count];
	
	for (i = count - 1; i >= 0; i--, x /= 10)
	{
		d[i] = x % 10;
	}
	
	for (i = 0; i < count; i++)
	{
		for (j = i + 1; j < count; j++)
		{
			if (d[i] == d[j])
			{
				return 0;
			}
		}
	}
	
	return 1;
}