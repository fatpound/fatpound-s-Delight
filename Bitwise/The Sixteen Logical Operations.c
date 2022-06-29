#include <stdio.h>
#include <conio.h>

int main()
{
	unsigned int x, y, cycle = 0;
	
	// printf("                      y           y  \n          y   y       | y   y   y &  \n        y !   &   y y x =   !   | x  \n        & &   x   ^ |   = y | x x    \nx y   0 x x x ! y x x ! x ! x ! ! ! 1\n-------------------------------------\n");
	
	printf("                      y           y  \n");
	printf("          y   y       | y   y   y &  \n");
	printf("        y !   &   y y x =   !   | x  \n");
	printf("        & &   x   ^ |   = y | x x    \n");
	printf("x y   0 x x x ! y x x ! x ! x ! ! ! 1\n");
	printf("-------------------------------------\n");
	
	for (x = 0, y = 0; x < 2; x++, cycle++)
	{
		printf("%u %u | 0 %u %u %u %u %u %u %u %u %u %u %u %u %u %u 1", x, y, (x & y), (x & !y), x, (!x & y), y, (x ^ y), (x | y), !(x | y), (x == y), !y, (x | !y), !x, (!x | y), !(x & y));
		
		if (y != 1)
		{
			y++;
			x--;
		}
		else if (x) 
		{
			if(y) y = 0;
			else y++;
			
			x--;
		}
		else y--;
		
		if (cycle < 3) printf("\n");
		else break;
	}
	
	getch();
	return 0;
}