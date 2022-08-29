#include <stdio.h>
#include <conio.h>
#include <string.h>

int main()
{
	int i, key;
	unsigned char text[50];
	
	gets(text);
	strupr(text);
	
	printf("\nlutfen bir sayi giriniz > ");
	scanf("%d", &key);
	
	for (i = 0; i < strlen(text); i++)
	{
		text[i] = (char) ((text[i] - 65 + key) % 26 + 65);
	}
	
	printf("%s", text);
	
	getch();
	return 0;
}
