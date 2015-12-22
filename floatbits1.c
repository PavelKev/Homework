#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

union dub
{
	int x;
	float y;
};
typedef union dub DUB;

void floatBits1 (float a)
{
	DUB t;
	unsigned int k, b;
  	int i;

	t.y = a;
	b = (t.x >> 31) & 1;

	printf ("(-1)^(%d)*1.",b);
	k = 1;
	k = k << 22;
	for (i = 22; i >= 0; i--)
 	{
		b = t.x & k;
    	b = b >> i;
		printf ("%d", b);
    	k = k >> 1;
	}
	printf ("*2^(");
	b = (t.x >> 23) & 0xff;

	printf ("%d - 127)\n", b);

}

int main ()
{
	char buffer[16];
	float a;

	gets (buffer);
	if (!strcmp(buffer, "NaN"))
	{
		a = 0.0 / 0;
	}
	else
	{
		if (!strcmp(buffer, "+inf")|| !strcmp(buffer, "+ inf"))
		{
			a = 1.0 / 0;
		}
		else
		{
			if (!strcmp(buffer, "-inf") || !strcmp(buffer, "- inf"))
			{
				a = -1.0 / 0;
			}
			else
			{
				a = atof (buffer);
			}
		}
	}
	floatBits1 (a);
	getch ();
	return 0;
}

