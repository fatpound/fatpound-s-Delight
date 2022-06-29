#include <stdio.h>

// As seen in Sebastian Lague's Digital Logic Sim.exe file > https://github.com/SebLague/Digital-Logic-Sim

int main()
{
	unsigned int z = 0;
  
	while (1)
	{
		printf("%u\n", !(0 | (z = !(0 | z))));
	}
  
	return 0;
}
