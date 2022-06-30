void PrintAsBinary(unsigned long long int n)
{
	unsigned long long int i;
	
	for (i = 1ULL << 63; i; i >>= 1)
	{
		printf(n & i ? "1" : "0");
	}
}

int ToBinary(int n)
{
	return (n ? (ToBinary(n >> 1) * 10 + n & 1) : 0);
}

int ToNotBinary(int n)
{
	return (n ? (ToNotBinary(n >> 1) * 10 + (n & 1) ^ 1) : 0);
}

int ToOctal(int n)
{
	return (n ? (ToOctal(n >> 3) * 10 + n % 8) : 0);
}

void ToHex(int n)
{
	if (n > 15)
	{
		ToHex(n / 16);
	}
	
	printf("%c", "0123456789ABCDEF"[n % 16]);
}
