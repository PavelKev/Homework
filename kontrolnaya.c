#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define SIZE 9

float k4a (float a, int n)
{
	int i;
	float res = 1;

	if (n < 0)
	{
		a = 1.0 / a;
		n = - n;
	}
	for (i = 0; i < n; i++)
	{
		res *= a;
	}
	return res;
}
float k4b (float a, int n)
{
	int i;
	float res = 1;

	if (n < 0)
	{
		a = 1.0 / a;
		n = - n;
	}
	while (n > 0)
	{
		if (n % 2)
		{
			res *= a;
		}
		n = n >> 1;
		a = a * a;
	}
	return res;
}
float k4c (float a, int n)
{
	int i, du;
	float res = 1;

	if (n < 0)
	{
		a = 1.0 / a;
		n = - n;
	}

	if (n > 0)
	{
		if (n % 2)
		{
			res *= a;
		}
		n = n >> 1;
		a = a * a;
		res *= k4c (a, n);
	}

	return res;
}
int k5 (int *ar)
{
	int i, res = 0;

	for (i = 0; i < SIZE; i++)
	{
		if (!ar[i])
		{
			res++;
		}
	}
	return res;
}

int k6 (int *ar)
{
	int i, res = 1, s;

	s = floor (SIZE / 2);
	for (i = 0; i < s; i++)
	{
		if (ar[i] != ar[SIZE - 1 - i])
		{
			res = 0;
		}
	}
	return res;
}

char downcase (char c)
{
	if ((c >= '€') && (c <= '') || (c >= 'A') && (c <= 'Z'))
	{
		c += 32;
	}
	else
	{
		if ((c >= '') && (c <= 'Ÿ'))
		{
			c += 80;
		}
		else
		{
			if (c == 'ğ')
			{
				c++;
			}
		}
	}
	return c;
}

int k7 (char *str)

{
	size_t len1;
	int i, j, res = 1, s;
	char buf[255];


	len1 = strlen(str);


	for (i = 0; i < len1; i++)
	{
		str[i] = downcase(str[i]);
	}
	j = 0;
	for (i = 0; i < len1; i++)
	{
		if ((str[i] >= 'a') && (str[i] <= 'z') ||
		(str[i] >= ' ') && (str[i] <= '¯') ||
		(str[i] >= 'à') && (str[i] <= 'ï') || (str[i] == 'ñ'))
		{
			buf[j] = str[i];
			j++;
		}
	}
	buf[j] = '\0';
	s = floor (j / 2);
	for (i = 0; i < s; i++)
	{
		if (buf[i] != buf[j - 1 - i])
		{
			res = 0;
		}
	}
	return res;

}
int ifsim(int a)
{
	int i, s, res = 1;

	s = floor (sqrt (a) + 1);
	for (i = 2; i <= s; i++)
	{
		if ((a % i) == 0)
		{
			res = 0;
			break;
		}
	}
	return res;
}

void k8(int n)
{
	int i;

	for (i = 2; i <= n; i++)
	{
		if (ifsim(i))
		{
		 	printf ("%d ", i);
		}
	}
	printf ("\n");
}

int k11 (char *s, char *s1)

{
	size_t len, len1;
	int i, j, n, res = 0;

	len = strlen (s);
	len1 = strlen (s1);
	n = len - len1;

	for (i = 0; i <= n; s++, i++)
	{
		if (s[0] == s1[0])
		{
			if (!strncmp (s, s1, len1))
			{
				res++;
			}
		}
	}
	return res;
}
int k12 (int n)
{
	int res;

	if ((n == 1) || (n == 2))
	{
		res = 1;
	}
	else
	{
		res = k12 (n - 1) + k12 (n - 2);
	}
	return res;
}

int main(void)
{
	float a;
	int n, i, mas[SIZE];
	char buf [255], buf2[255];

    printf ("N 4\na = ");
	scanf ("%f", &a);
	printf ("n = ");
	scanf ("%d", &n);

	printf ("a) a^n = %f\n", k4a (a, n));
	printf ("b) a^n = %f\n", k4b (a, n));
	printf ("c) a^n = %f\n", k4c (a, n));

    printf ("\nN 5\n");

	for (i = 0; i < SIZE; i++)
	{
		printf ("array[%d] = ",i);
		scanf ("%d", &(mas[i]));
	}
	printf ("%d elements are equal 0\n", k5 (mas));

    printf ("\nN 6\n");
	if (k6 (mas))
	{
		printf ("The array is symmetric\n");
	}
	else
	{
		printf ("The array is not symmetric\n");
	}
    printf ("\nN 7\n");
	getchar();
	gets (buf);
	if (k7 (buf))
	{
		printf ("It is a palindrome\n");
	}
	else
	{
		printf ("It is not a palindrome\n");
	}
    printf ("N 8\n");
	printf ("n = ");
	scanf ("%d", &n);
	k8 (n);

    printf ("\nN 11\n");
	printf ("S = ");
	getchar();
	gets (buf);
    printf ("S1 = ");
	gets (buf2);
	printf("%d\n", k11 (buf, buf2));

    printf ("\nN 12\n");
	printf ("n = ");
	scanf ("%d", &n);
	printf ("F(%d) = %d\n", n, k12 (n));

    getch ();
    return 0;
}
