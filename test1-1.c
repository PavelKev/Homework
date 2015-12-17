#include <stdio.h>
#include <conio.h>

unsigned int my_strlen (char *buf)
{
	unsigned int i = 0;

	while (buf[i] != '\0')
	{
		i++;
	}
	return i;
}
int my_strcmp (char *buf1, char *buf2)

{
	unsigned int i = 0;
	int res = 0;

	while ((buf1[i] != '\0') && (buf2[i] != '\0') && (!res))
	{
		if (buf1[i] > buf2[i])
		{
			res = 1;
		}
		if (buf1[i] < buf2[i])
		{
			res = -1;
		}
		i++;
	}
	if (!res)
	{
		if ((buf1[i] == '\0') && (buf2[i] != '\0'))
		{
			res = -1;
		}
		if ((buf1[i] != '\0') && (buf2[i] == '\0'))
		{
			res = 1;
		}
	}
	return res;
}

char *my_strcpy (char *buf1, const char *buf2)
{
	unsigned int i = 0;

	while (buf2[i] != '\0')
	{
		buf1[i] = buf2[i];
		i++;
	}
	buf1[i] = '\0';

	return buf1;
}

char *my_strcat (char *buf1, const char *buf2)
{
	unsigned int i = 0, j = 0;

	while (buf1[i] != '\0')
	{
		i++;
	}
	while (buf2[j] != '\0')
	{
		buf1[i] = buf2[j];
		j++;
		i++;
	}

	buf1[i] = '\0';

	return buf1;
}

int main(void)
{
	int len;
	char buf1 [255], buf2[255], buf3[255], *buf4;

	printf ("char buf1 [255], buf2[255], buf3[255], *buf4;\n\n");
	printf ("buf1: ");
	gets(buf1);
	printf ("my_strlen (buf1) = %u\n\n", my_strlen (buf1));
	printf ("buf2: ");
	gets(buf2);
	printf ("my_strlen (buf2) = %u\n\n", my_strlen (buf2));

	printf ("my_strcmp (buf1, buf2) = %d\n\n", my_strcmp (buf1, buf2));

	printf ("buf4 = my_strcpy (buf3, buf1)\n");
	buf4 = my_strcpy (buf3, buf1);

	printf ("buf3 = ");
	puts (buf3);
	printf ("buf4 = ");
	puts (buf4);

	printf ("\nbuf4 = my_strcat (buf1, buf2)\n");
	buf4 = my_strcat (buf1, buf2);

	printf ("buf1 = ");
	puts (buf1);
	printf ("buf4 = ");
	puts (buf4);






	_getch();
	return 0;
}
