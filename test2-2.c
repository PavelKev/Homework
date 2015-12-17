#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


int cmp_mas(char* a, char* b)// 0 => a = b; 1 => a > b; -1 => a < b;
{
	int i = 31, res = 0;

	while ((i >=0) && (!res))
	{
		if (a[i] > b[i])
		{
			res = 1;
		}
		if (a[i] < b[i])
		{
			res = -1;
		}
		i--;
	}
	return res;
}

char *vvod_mas(char* a)
{
	char hod;
	char l;
	int i, j;

	l = 1;
	j =31;
	while ((j >= 0) && (l))
	{
		hod = getch ();
		switch (hod)
		{
		case '1':
			a[j] = 1;
			printf ("%d", 1);
			j--;
		break;
		case '0':
			a[j] = 0;
			printf ("%d", 0);
			j--;
		break;
		case '\r':
			l = 0;
		break;
		}
	}
	for (i = j+1; i < 32; i++)
	{
		a[i - j - 1] = a[i];
	}
	for (i = 31; i > 30 - j; i--)
	{
		a[i] = 0;
	}

	return a;
}

int main(void)
{
	char *a, *b;
	int i;

	a = (char*)malloc (32);
	b = (char*)malloc (32);

	if ((a != NULL)&&(b != NULL))
	{

		for (i = 0; i < 32; i++)
		{
			a[i] = b[i] = 0;
		}
		printf ("a = ");
		a = vvod_mas (a);
		printf ("\n");
		printf ("b = ");
		b = vvod_mas (b);
		printf ("\n");


		i = cmp_mas (a, b);
		switch (i)
		{
		case -1:
			printf ("a < b\n");
		break;
		case 1:
			printf ("a > b\n");
		break;
		case 0:
			printf ("a = b\n");
		break;
		}
	}
	else
	{
		puts("Not enough memory");
	}

	if (a != NULL)
	{
		free (a);
	}
	if (b != NULL)
	{
		free (b);
	}

	return 0;
}
