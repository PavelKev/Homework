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
  	int i, if0 = 0, z;

	t.y = a;
	b = (t.x >> 31) & 1;
	z = b;

	printf ("(-1)^(%d)*1.", b);
	k = 1;
	k = k << 22;
	for (i = 22; i >= 0; i--)
 	{
		b = t.x & k;
		b = b >> i;
		printf ("%d", b);
		k = k >> 1;
		if0 += b;
	}
	printf ("*2^(");
	b = (t.x >> 23) & 0xff;

	printf ("%d - 127)", b);

	if ((z == 0) && (if0 == 0) && (b == 0))
	{
		printf(" = +0");
	}
	if ((z == 1) && (if0 == 0) && (b == 0))
	{
		printf(" = -0");
	}
	if ((if0 != 0) && (b == 255))
	{
		printf(" = NaN");
	}
	if ((z == 0) && (if0 == 0) && (b == 255))
	{
		printf(" = +inf");
	}
	if ((z == 1) && (if0 == 0) && (b == 255))
	{
		printf(" = -inf");
	}
	printf("\n");
}

int main ()
{
	char buffer[16], buf[16];
	float a, b;
	int i, j;

	gets (buffer);
	i = 0;
	a = 0;
	b = 1;
	while ((buffer [i] != '/') && (buffer[i] != '\0'))
	{
		buf[i] = buffer[i];
		i++;
	}
	buf[i] = '\0';
	a = atof (buf);
	if (buffer [i] == '/')
	{
		j = 0;
		i++;
		while (buffer[i] != '\0')
		{
			buf[j] = buffer[i];
			i++;
			j++;
		}
		buf[j] = '\0';
		b = atof (buf);
		a = a / b;
	}
	floatBits1 (a);
	getch ();
	return 0;
}


