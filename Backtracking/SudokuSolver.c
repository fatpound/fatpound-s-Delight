#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int s[9][9] =
{
	{0, 0, 0,   0, 0, 1,   5, 0, 0},
	{0, 0, 8,   7, 9, 0,   0, 0, 0},
	{4, 0, 0,   0, 0, 6,   8, 0, 0},
	
	{0, 0, 0,   1, 0, 8,   0, 0, 3},
	{0, 0, 6,   0, 0, 5,   0, 0, 0},
	{0, 2, 0,   4, 0, 0,   0, 0, 6},
	
	{7, 0, 3,   0, 0, 0,   0, 4, 5},
	{0, 4, 0,   0, 0, 0,   0, 0, 1},
	{0, 0, 9,   3, 7, 0,   0, 0, 0}
};

int IsAvailable(int row, int col, int n)
{
	int i = -1, flag = 1;
	
	while (++i < 9)
	{
		if (i != (flag ? row : col) && s[flag ? i : row][flag ? col : i] == n)
		{
			return 0;
		}
		
		if (i == 8 && flag)
		{
			flag = 0;
			i = -1;
		}
	}
	
	int j;
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (s[i + row - row % 3][j + col - col % 3] == n)
			{
				return 0;
			}
		}
	}
	
	return 1;
}

int solve(int row, int col)
{
	if (col == 9)
	{
		if (row == 8)
		{
			return 1;
		}
		
		row++;
		col = 0;
	}
	
	if (s[row][col])
	{
		return solve(row, col + 1);
	}
	
	int n;
	
	for (n = 1; n < 10; s[row][col] = 0, n++)
	{
		if (IsAvailable(row, col, n))
		{
			s[row][col] = n;
			
			if (solve(row, col + 1))
			{
				return 1;
			}
		}
	}
	
	return 0;
}

int main()
{
	int i, j;
	
	solve(0, 0);
	
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("%d %s", s[i][j], j && (j + 1) % 3 == 0 ? "  " : "");
		}
		
		printf("\n%s", i && i != 8 && (i + 1) % 3 == 0 ? "\n" : "");
	}
	
	return (!getch());
}
