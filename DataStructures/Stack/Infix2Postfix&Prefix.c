#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP_P(x, y) (*(x) == *(y) ? 0 : (*(x) ^= *(y) ^= *(x) ^= *(y)))

#define YERAYIR ((char*) malloc(sizeof(char) * 100))
// #define String char*

typedef struct STC
{
	char **str;
	int index;
} Stack;

Stack s1;

int values[7][2];
char *valch = "+-*/^()", *inf = "A+B*C-D/E*T+F-G";

int IndexOf(char k)
{
	int i;
	
	for (i = 0; valch[i]; i++)
	{
		if (valch[i] == k)
		{
			return i;
		}
	}
	
	return 0;
}

int Val(char k, int mode)
{
	return values[IndexOf(k)][mode];
}

void Push(char *yazi)
{
	strcpy(s1.str[++s1.index], yazi);
}

char *Pop()
{
	char *gecici = YERAYIR;
	
	strcpy(gecici, s1.str[s1.index]);
	
	s1.str[s1.index--][0] = '\0';
	
	return gecici;
}

char *Infix2Postfix(char *infix)
{
	char k, *postfix = YERAYIR, w[2] = {0, 0};
	int i;
	
	for (postfix[i = 0] = '\0'; infix[i]; i++)
	{
		k = infix[i];
		
		if ((k >= 'A' && k <= 'Z') || (k >= 'a' && k <= 'z'))
		{
			w[0] = k;
			strcat(postfix, w);
		}
		else if (k == '+' || k == '-' || k == '*' || k == '/' || k == '^' || k == '(' || k == ')')
		{
			if (s1.index > -1)
			{
				if ((k == ')') || (Val(k, 0) <= Val(s1.str[s1.index][0], 1)))
				{
					while (k == ')' ? (s1.str[s1.index][0] != '(') : (Val(k, 0) <= Val(s1.str[s1.index][0], 1)))
					{
						strcat(postfix, s1.str[s1.index]);
						s1.str[s1.index--][0] = '\0';
						
						if (s1.index == -1)
						{
							break;
						}
					}
					
					if (k == ')')
					{
						s1.str[s1.index--][0] = '\0';
					}
				}
			}
			
			if (k != ')')
			{
				w[0] = k;
				Push(w);
			}
		}
	}
	
	for (; s1.index > -1; strcat(postfix, Pop()));
	
	return (postfix);
}

char *Infix2Prefix(char *input)
{
	char *prefix = YERAYIR;
	
	int i;
	
	for (strrev(strcpy(prefix, input)), i = 0; prefix[i]; i++)
	{
		if (prefix[i] == '(')
		{
			prefix[i] = ')';
		}
		else if (prefix[i] == ')')
		{
			prefix[i] = '(';
		}
	}
	
	return (strrev(Infix2Postfix(prefix)));
}

int main()
{
	s1.index = -1;
	
	values[6][0] =    values[6][1] = -1; // ) -1 -1
	
	values[0][0] =    values[0][1] =  1; // +  1  1
	values[1][0] =    values[1][1] =  1; // -  1  1
	values[2][0] =    values[2][1] =  2; // *  2  2
	values[3][0] =    values[3][1] =  2; // /  2  2
	values[4][0] = 4; values[4][1] =  3; // ^  4  3
	values[5][0] = 4; values[5][1] =  0; // (  4  0
	
	int i, len = strlen(inf);
	
	s1.str = (char**) malloc(sizeof(char*) * len);
	for (i = 0; i < len; (s1.str[i++] = YERAYIR)[0] = '\0');
	
	printf("%s", Infix2Prefix(inf));
	
	return (!getch());
}
