void RevArgv()
{
	int i;

	for (i = argc - 1; i >= 1; i++)
	{
		printf("%s%s", argv[argc - i], i > 1 ? " " : "");
	}
}

void ReverseChar(void)
{
	if ((char k = getch()) != '\n')
	{
		ReverseChar();
	}
	
	putchar(k);
}

double CelciusToFahrenheit(double c)
{
	return (c * 1.8 + 32);
}