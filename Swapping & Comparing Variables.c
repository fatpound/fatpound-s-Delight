#define MIN(x, y) (x > y ? y : x)
#define MAX(x, y) (x > y ? x : y)
#define MINYZ(x, y, z) (x > y ? (y > z ? z : y) : (y > z ? (x > z ? z : x) : x))
#define MIDYZ(x, y, z) (x > y ? (y > z ? y : (x > z ? z : x)) : (y > z ? (x > z ? x : z) : y))
#define MAXYZ(x, y, z) (x > y ? (y > z ? x : (x > z ? x : z)) : (y > z ? y : z))
#define MINYZT(x, y, z, t) (x > y ? (y > z ? (z > t ? t : z) : (z > t ? (y > t ? t : y) : (x > t ? y : (x > y ? (y > z ? z : y) : (y > z ? (x > z ? z : x) : x))))) : (y > z ? (y > t ? (x > z ? (z > t ? t : z) : (z > t ? (x > t ? t : x) : x)) : (x > z ? z : x)) : (y > t ? (x > t ? t : x) : x)))

#define SWAP1(x, y) (x == y ? x = y : x ^= y ^= x ^= y)
#define SWAP2(x, y) (x -= y = (x += y) - y)
#define SWAP3(x, y) (x /= y = (x *= y) / y)
#define SWAP4(x, y) (x = x + y - (y = x))
#define SWAP_P(x, y) (*(x) == *(y) ? 0 : (*(x) ^= *(y) ^= *(x) ^= *(y)))

void XorSwap(int *x, int *y)
{
	(*x != *y) ? (*x ^= *y ^= *x ^= *y) : (*x = *y);
}

void AddSwap(int *x, int *y)
{
	*x -= *y = (*x += *y) - *y;
}

void ProductSwap(int *x, int *y)
{
	*x /= *y = (*x *= *y) / *y;
}

void Swap(int *x, int *y)
{
	*x = *x + *y - (*y = *x);
}