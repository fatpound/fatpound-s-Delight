int IsLeapYear(int value)
{
	while (value % 100 == 0)
	{
		value /= 100;
	}

	return (value % 4 == 0);
}

int IsLeapYear2(int y)
{
	return ((y % 4 == 0 && y % 100) || y % 400 == 0);
}