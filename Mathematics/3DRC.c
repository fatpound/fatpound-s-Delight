#include <complex.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

int main() // works in Visual Studio 2019
{
	double a, b, c, d, p, q, u, v, D, temp, delta;
	_Dcomplex w = { -0.5, (sqrt(3) / 2) };
	
	printf("a, b, c ve d degerlerini giriniz >\n");
	scanf_s("%lf%lf%lf%lf", &a, &b, &c, &d);
	
	p = (c / a) - ((b * b) / (3 * a * a));
	q = (d / a) - ((b * c) / (a * a)) + ((2 * b * b * b) / (27 * a * a * a));
	
	D = ((q / 2) * (q / 2)) + ((p / 3) * (p / 3) * (p / 3));
	temp = sqrt(D);
	
	u = -(q / 2) + temp;
	v = -(q / 2) - temp;
	
	delta = -(108 * D); /* -(4 * p * p * p) - (27 * q * q) */
	
	// printf("w = %g + %gi\n", creal(w), cimag(w)); KARMASIK w SAYIMIZ
	
	_Dcomplex wkare = _Cmulcc(w, w), kupu = { cbrt(u), 0 }, kupv = { cbrt(v), 0 };
	
	_Dcomplex x21 =  _Cmulcc(w, kupu), x22 = _Cmulcc(wkare, kupv);
	_Dcomplex y2 = { creal(x21) + creal(x22), cimag(x21) + cimag(x22) };
	
	_Dcomplex x31 =  _Cmulcc(wkare, kupu), x32 = _Cmulcc(w, kupv);
	_Dcomplex y3 = { creal(x31) + creal(x32), cimag(x31) + cimag(x32) };
	
	double eksi = (b / (3 * a));
	
	printf("x1 = %lf\n", cbrt(u) + cbrt(v) - eksi);
	printf("x2 = %lf + %lfi\n", creal(y2) - eksi, cimag(y2));
	printf("x3 = %lf +%lfi\n", creal(y3) - eksi, cimag(y3));
	
	char cop = _getch();
	return 0;
}
