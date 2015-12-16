#include <conio.h>
#include <stdio.h>
#include <math.h>#include <stdlib.h>


void floatBits3 (float a)
{
	float *p;
	unsigned int *p1, k, b, x;
	int i;

	p = &a;
	p1 = (unsigned int*)p;
	x = *p1;

	b = (x >> 31) & 1;

	printf ("(-1)^(%d)*1.",b);
	k = 1;
	k = k << 22;
	for (i = 22; i >= 0; i--)
 	{
		b = x & k;
    	b = b >> i;
		printf ("%d", b);
    	k = k >> 1;
	}
	printf ("*2^(");
	b = (x >> 23) & 0xff;

	printf ("%d - 127)\n", b);

}

int main()
{
	char buffer[16];
	float a;

	gets (buffer);
	a = atof (buffer);
	floatBits3 (a);
	getch ();
	return 0;
}

