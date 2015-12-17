#include <stdio.h>
#include <conio.h>
#include <string.h>

int main(void)
{
	FILE  *fp;
	char line[255];
	size_t len;
	int i, l;

	gets (line);
	fp = fopen (line,"r");
	printf ("\n");
	if (fp != NULL)
	{

		while ( !feof(fp) )
		{
			l = 0;
			fgets (line, 255, fp);
			len = strlen (line);
			for (i = 0; i < len; i++)
			{
				if ((l == 0) && (line[i] == '/'))
				{
					l = 1;
				}
				else
				{
					if ((l == 1) && (line[i] != '/'))
					{
						l = 0;
					}
					else
					{
						if ((l == 1) && (line[i] == '/'))
						{
							l =  2;
						}
						else
						if (l == 2)
						{
							printf("%c", line[i]);
						}
					}
				}
			}
			if (l == 2)
			{
				printf("\n");
			}
		}
	fclose (fp);
	}
	else
	{
		printf("File not found\n");
	}

	getch();
	return 0;
}
