#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define N 3
#define MAX_STRING_SIZE 255


int main(void)

{
	char str[MAX_STRING_SIZE], buf[MAX_STRING_SIZE];
	int i, j, k;
	size_t len;

	for (i = 0; i < MAX_STRING_SIZE; i++)
	{
		str[i] = '\0';
	}

	k = 2 * N + 1;
	printf ("Введите в любом порядке %d строк, 1 уникальную, остальные парами\n", k);

	for (i = 0; i < k; i++)
	{
		gets (buf);
		len = strlen (buf);
		for (j =0; j < len; j++)
		{
			str[j] ^= buf[j];
		}
	}
	printf("\nУникальная: ");
	puts (str);
	return 0;
}
