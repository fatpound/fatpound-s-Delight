#include <iostream>
#include <string>

void combine(std::string str, std::string first, int n)
{
    if (n == 0)
    {
        std::cout << first << '\n';
        return;
    }

    for (int i = 0; i < str.length(); i++)
    {
        combine(str.substr(i + 1, str.length()), first + str[i], n - 1);
    }
}

void permute(std::string str, std::string first, int n)
{
    if (n == 0)
    {
        std::cout << first << '\n';
        return;
    }

    for (int i = 0; i < str.length(); i++)
    {
        permute(str.substr(0, i) + str.substr(i + 1, str.length()), first + str[i], n - 1);
    }
}

int main()
{
    combine("abcde", "", 3);
    std::cout << '\n';
    permute("abcde", "", 3);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 0;
}
