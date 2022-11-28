#include <iostream>
#include <string>

using namespace std;

void permutecombine(string str, string first, int n, int mode) /// mode 0 -> combine <#> mode 1 -> permute
{
	if (n == 0)
	{
		cout << first << endl;
	}
	else
	{
		for (int i = 0; i < str.length(); i++)
		{
			permutecombine((mode ? str.substr(0, i) : "") + str.substr(i + 1, str.length()), first + str[i], n - 1, mode);
		}
	}
}

int main()
{
	permutecombine("abcde", "", 3, 1);

	return 0;
}
