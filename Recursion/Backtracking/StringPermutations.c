#include <stdio.h>
#include <conio.h>
#include <string.h>

#define SWAP_P(x, y) (*(x) == *(y) ? 0 : (*(x) ^= *(y) ^= *(x) ^= *(y)))

void PrintPermutations(char* str, int left, int rite)
{
	if (left == rite)
	{
		printf("%s\n", str);
	}
	else
	{
		int i;
		
		for (i = left; i <= rite; i++)
		{
			SWAP_P(&str[left], &str[i]);
			PrintPermutations(str, left + 1, rite);
			SWAP_P(&str[left], &str[i]);
		}
	}
}

int main()
{
	char str[] = "ABCD";
	
	PrintPermutations(str, 0, strlen(str)  - 1);
	
	return !_getch();
}
