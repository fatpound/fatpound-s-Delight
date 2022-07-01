#include <stdio.h>
#include <conio.h>

#define PI 3.141592

#define U64 unsigned long long
#define islem(x) (Power(aci, x == 1 ? us1 : us2) / Factorial(x == 1 ? us1 : us2))

double Power(double x, U64 int n)
{
	return (n ? (x * Power(x , n - 1)) : 1);
}

U64 int Factorial(U64 int x)
{
	return (x > 2 ? (x * Factorial(x - 1)) : 2);
}

int main()
{
	U64 int us1 = 1, us2 = 2, i;
	double sinx = 0, cosx = 1, aci;
	char *w[3] = { "sinus", "tanjant", "sekant" };
	
	printf("acinizi giriniz > ");
	scanf("%lf", &aci);
	
	aci = ((U64 int) aci % 360) + (aci - (U64 int) aci); // double variable Mod 360
	aci *= PI / 180; // to Radian
	
	for (i = 0; i < 10; us1 += 2, us2 += 2)
	{
		sinx += (i & 1)   ? (-islem(1)) :  (islem(1));
		cosx += (i++ & 1) ?  (islem(2)) : (-islem(2));
	}
	
	for (i = 0; i < 6; i++)
	{
		printf("%s%s%s%s(%g) %s = %g%s", i ? "" : "\n", i ? (i < 3 ? "  " : (i == 4 ? "   " : (i != 5 ? "" : " "))) : "    ", i & 1 ? "co" : "", w[i >> 1], aci * 180 / PI, aci * 180 / PI < 10 ? "  " : (aci * 180 / PI < 100 ? " " : ""), i ? (i == 1 ? cosx : (i == 2 ? sinx / cosx : (i == 3 ? 1 / (sinx / cosx) : (i == 4 ? 1 / cosx : 1 / sinx)))) : sinx, i != 5 ? "\n" : "");
	}
	
	getch();
	return 0;
}
