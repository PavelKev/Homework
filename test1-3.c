#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define N 7

void unique (char **t, char *b)
{
	int i, j = 0, k, sum;
	size_t xlen = 0;

	k = 2 * N + 1;

	for (i = 0; i < k; i++)
	{
		xlen ^= strlen (t[i]);
	}

	for (j=0; j < xlen; j++)
	{
		b[j] = 0;
		for (i = 0; i < k; i++)
		{
			if (strlen (t[i]) == xlen)
			{
				b[j] ^= t[i][j];
			}
		}
	}
	b[xlen] ='\0';
}

void clear (char **t)
{
	int i, k;

	k = 2 * N + 1;
	for (i = 0; i < k; i++)
	{
		if (t[i] != NULL)
		{
			free (t[i]);
		}
	}
	free (t);
}


int main(void)

{
	char **spis, buf[255];
	int i, k, l = 0;
	size_t len;

	k = 2 * N + 1;
	spis = (char**)malloc (k * sizeof (char*));
	for (i = 0; i < k; i++)
	{
		spis[i] = NULL;
	}

	if (spis != NULL)
	{
		for (i = 0; i < N; i++)
		{
			gets (buf);
			puts (buf);
			len = strlen (buf);
			spis[2*i] = (char*)malloc (len * sizeof (char));
			if (spis[2*i] == NULL)
			{
				l = 1;
			}
			else
			{
				strcpy(spis[2*i], buf);
			}
			spis[2*i+1] = (char*)malloc (len * sizeof (char));
			if (spis[2*i+1] == NULL)
			{
				l = 1;
			}
			else
			{
				strcpy(spis[2*i+1], buf);
			}
		}
		gets (buf);
		len = strlen (buf);
		spis[2*N] = (char*)malloc (len * sizeof (char));
		if (spis[2*N] == NULL)
		{
			l = 1;
		}
		else
		{
			strcpy(spis[2*N], buf);
		}
		if (l)
		{
			puts ("Not enough memory");
		}
		else
		{
			unique (spis, buf);
			printf ("\n\n");
			puts (buf);

		}

		getch();
		clear (spis);
	}
	else
	{
		puts ("Not enough memory");
		getch();
	}
	return 0;
}
