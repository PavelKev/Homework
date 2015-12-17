#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define NUMSTR 5

void del_a (char** t, char a)
{
	size_t size;
	char buffer[256];
	int i, j, k;

	for (i = 0; i < NUMSTR; i++)
	{
		size = strlen(t[i]);
		k = 0;
		for (j = 0; j < size; j++)
		{
			if (t[i][j] != a)
			{
				buffer[k] = t[i][j];
				k++;
			}
		}
		buffer[k] = '\0';
		strcpy(t[i], buffer);
	}

	return;
}
char **clear (char** t)
{
	int i;
	for (i = 0; i < NUMSTR; i++)
	{
		free (t[i]);
	}
	free (t);
	return NULL;
}
void vivod_text (char** t)
{
	int i;

	printf("------------\n");
	for (i = 0; i < NUMSTR; i++)
	{
		puts(t[i]);
	}
}

char **vvod_text (void)
{
	size_t size;
	char buffer[256], **t;
	int i, j;

	t = (char**) malloc(NUMSTR * sizeof(char*));


	if (t != NULL)
	{
		for (i = 0; i < NUMSTR; i++)
		{
			gets (buffer);
			size = strlen(buffer);
			t[i] = (char*)malloc(size+1);
			if (t[i] != NULL)
			{
				strcpy (t[i], buffer);

				if (t[i] == NULL)
				{
					for (j = 0; j < i; j++)
					{
						free (t[j]);
					}
					free (t);
					return NULL;
				}
			}
			else
			{
				clear(t);
				return t;
			}
		}
	}
	return t;
}

int main(void)
{
	char a, **text = NULL;


	scanf("%c\n", &a);

	text = vvod_text( );
	if (text == NULL)
	{
		printf("no enough memory");
	}
	del_a (text, a);


	vivod_text(text);

    getch();
    if (text != NULL)
    {
		clear (text);
	}
    return 0;
}
