void SqrKokDisi(int x)
{
    int i, k = 1;

    for (i = 2; i < x / 2; i++)
    {
        if (x % (i * i) == 0)
        {
            while (x % (i * i) == 0)
            {
                x /= i * i;
                k *= i;
            }
        }
    }

    printf("%i * kok(%i)", k, x);
}

void PrintRational(double x)
{
	int i = 2;
	
	if (x == (int) x) printf("\n%g", x);
	else
	{
		while (x * i != (int)(x * i))
		{
			++i;
		}
		
		printf("\n%g\n/\n%d", x * i, i);
	}
}