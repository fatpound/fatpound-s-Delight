#include <iostream>
#include <string>

using namespace std;

void permute(string first, string str, int n)
{
	if (n == 0)
	{
		cout << first << endl;
	}
	else
	{
		for (int i = 0; i < str.length(); i++)
		{
			permute(first + str[i], str.substr(0, i) + str.substr(i + 1, str.length()), n - 1);
		}
	}
}

int main()
{
	permute("", "abcde", 2);

	return 0;
}