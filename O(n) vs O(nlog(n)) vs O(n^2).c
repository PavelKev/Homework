#include <cstdio>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define POTOLOK 100000

unsigned long kvanto;

int slu (int ra)
{
	int i;

	i = rand();
	i = i % ra;
	return i;
}

void zap (int *p, int *p1, int *p2, unsigned long k)
{
	int i;
	time_t t;

	t = time (NULL);
	srand (t);

for (i = 0; i < k; i++)
	{
		 p2[i] = p1[i] = p[i] = slu (POTOLOK);
	}
}


void puzyrok (int *p, unsigned long k)
{
	int i, j, b;
	char bol;

	j = k;
	do
	{
		bol = 0;
		for (i = 1; i < j; i++)
		{
			if(p[i-1] > p[i])
			{
				b = p[i];
				p[i] = p[i-1];
				p[i-1] = b;
				bol = 1;
			}
		}
		j--;
} while (bol);

}

void rascheska (int *p, unsigned long k)
{
	int i, b, l,ste;

	ste = k;

	do
	{
		ste = floor((double)ste/1.247 + 0.5);
		l = k - ste;
		for (i = 0; i < l; i++)
		{
			if(p[i] > p[i + ste])
			{
				b = p[i];
				p[i] = p[i + ste];
				p[i+ste] = b;
			}
		}
	} while (ste > 2);
	puzyrok (p, k);

}

void podschet(int *p, unsigned long k)
{
	int i, j, l, pp[POTOLOK];

	for (i = 0; i < POTOLOK; i++)
	{
		pp[i] = 0;
	}
	for (i = 0; i < k; i++)
	{
		pp[p[i]]++;
	}
	l = 0;
	for (i = 0; i < POTOLOK; i++)
	{
		for (j = 0; j < pp[i]; j++)
		{
			p[l+j] = i;
		};
		l = l + j;

	}
}


int main ()
{
	int *p, *p1, *p2, i;
	clock_t cl_start, cl_finish;
	double sek;

	p = NULL;
	p1 = NULL;
	p2 = NULL;
	scanf ("%d", &kvanto);

 	p = (int*) malloc(kvanto * sizeof(int));
 	p1 = (int*) malloc(kvanto * sizeof(int));
	p2 = (int*) malloc(kvanto * sizeof(int));

	if ((p != NULL)&&(p1 != NULL)&&(p2 != NULL))
	{
		zap(p,p1,p2,kvanto);

		cl_start = clock();
		podschet(p,kvanto);
		cl_finish = clock();
		sek = cl_finish - cl_start;
		sek = sek / CLOCKS_PER_SEC;
		printf("%f\n",sek);

		cl_start = clock();
		rascheska(p1,kvanto);
		cl_finish = clock();
		sek = cl_finish - cl_start;
		sek = sek / CLOCKS_PER_SEC;
		printf("%f\n",sek);

		cl_start = clock();
		puzyrok(p2,kvanto);
		cl_finish = clock();
		sek = cl_finish - cl_start;
		sek = sek / CLOCKS_PER_SEC;
		printf("%f\n",sek);

	}

	if (p != NULL)
	{
		free(p);
	}

	if (p1 != NULL)
	{
		free(p1);
	}

	if (p2 != NULL)
	{
		free(p2);
	}

	getch();
	return 0;
}
