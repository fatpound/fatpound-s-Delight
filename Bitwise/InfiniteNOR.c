#include <stdio.h>

// As seen in Sebastian Lague's Digital Logic Sim.exe file

// https://github.com/SebLague/Digital-Logic-Sim
// https://github.com/fatpound/fatpounds-Delight/blob/main/Bitwise/InfiniteNOR.png

int main()
{
	unsigned int z = 0;
  
	while (1)
	{
		printf("%u\n", !(0 | (z = !(0 | z))));
	}
  
	return 0;
}
