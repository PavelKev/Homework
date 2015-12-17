#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Element
{
	char *str;
	int val;
	struct Element *next;
}element;

void clear(element *t)
{
	element *p;

	p = t;
	while (p != NULL)
	{
		p = p->next;
		free(t);
		t = p;

	}

}
void vivod(element *t)
{
	element *p;

	p = t;
	while (p != NULL)
	{
		printf ("%d - ", p->val);
		puts (p->str);
		p = p->next;

	}

}

int add_el (element **t, char *b)
{
	int l = 1, er = 0;
	size_t len;
	element *p1, *p2;


	len = strlen(b);
	if (*t == NULL)
	{
		*t = (element*)malloc (sizeof(element));
		if (t != NULL)
		{
			(*t)->str = (char*)malloc (len + 1);
			if ((*t)->str != NULL)
			{
				(*t)->next = NULL;
				(*t)->val = 1;
				strcpy((*t)->str, b);

			}
			else
			{
				free (*t);
				*t = NULL;
				er = 1;
			}

		}
		else
		{
			er = 1;
		}
	}
	else
	{
		p1 = (*t);

		do
		{
			if(!strcmp (b, p1->str))
			{
				p1->val++;
				l = 0;
			}
			else
			{
				p2 = p1;
				p1 = p1->next;
			}
		}while ((p1 != NULL) && (l));
		if (l)
		{
			p2->next = (element*)malloc (sizeof(element));
			if (p2->next != NULL)
			{
				p2->next->str = (char*)malloc (len + 1);
				if (p2->next->str != NULL)
				{
					p2->next->next = NULL;
					p2->next->val = 1;
					strcpy(p2->next->str, b);
				}
				else
				{
					free (p2->next);
					p2->next = NULL;
					er = 1;
				}
			}
			else
			{
				er = 1;
			}

		}
	}

	return er;
}


int main(void)
{
	char buf[255];
	element *spis = NULL;


	gets (buf);
	while (strlen (buf))
	{
		add_el (&spis, buf);
		gets (buf);
	}

	vivod (spis);

	_getch();
	clear (spis);
	return 0;
}
