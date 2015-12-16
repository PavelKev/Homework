#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct kvar
{
    unsigned mant: 23;
    unsigned porad: 8;
    unsigned znak: 1;
} KVAR;

union dub
{
	KVAR x;
	float y;
};
typedef union dub DUB;

void floatBits1 (float a)
{
	DUB t;
	unsigned int k, b;
  	int i;

	t.y = a;

	printf ("(-1)^(%d)*1.",t.x.znak);
	k = 1;
	k = k << 22;
	for (i = 22; i >= 0; i--)
 	{
		b = t.x.mant & k;
    	b = b >> i;
		printf ("%d", b);
    	k = k >> 1;
	}
	printf ("*2^(%d - 127)\n", t.x.porad);

}

int main ()
{
	char buffer[16];
	float a;

	gets (buffer);
	a = atof (buffer);
	floatBits1 (a);
	getch ();
	return 0;
}

