#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#define max_string 25
#define TABLE_SIZE 0x10000

typedef struct Element
{
	char *str;
	int val;
	struct Element *next;
}element;

typedef struct Tab
{
	element **list;
	unsigned int (*fptr)(char*, unsigned int);
}tab;

unsigned int constHash (char *str, unsigned int len)
{
	return 153;
}
unsigned int sumHash (char *str, unsigned int len)
{
	unsigned int i = 0;
	unsigned int hash = 0;

	for (i = 0; i < len; i++) {
		hash += (unsigned char)(str[i]);
	}
	return hash;
}
unsigned int faq6Hash (char *str, unsigned int len)
{
	unsigned int hash = 0, i = 0;

	for (i = 0; i < len; i++) {
		hash += (unsigned char)(str[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);

	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

unsigned int ROT13Hash (char *str, unsigned int len)
{
	unsigned int hash = 0, i = 0;

	for (i = 0; i < len; i++) {
		hash += (unsigned char)(str[i]);
		hash -= (hash << 13) | (hash >> 19);
	}

	return hash;
}

char UpCase (char c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}

	return c;
}

int isBukva (char c)
{
	int i = 0;

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		i = 1;
	}
	return i;
}

void create_tab (tab *t, unsigned int (*fptr)(char*, unsigned int))
{
	unsigned int i;

	t->list = (element**)malloc (TABLE_SIZE*sizeof(element*));

	if (t->list != NULL)
	{
		t->fptr = fptr;

		for (i = 0; i < TABLE_SIZE; i++)
		{
			t->list[i] = NULL;

		}
	}

	return;
}
void clear_tab (tab *t)
{
	element *p1, *p2;
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
	{
		p2 = p1 = t->list[i];
		while (p1 != NULL)
		{
			p1 = p1->next;
			free(p2);
			p2 = p1;
		}

	}

	free(t->list);

	return ;
}


int del_el (tab *t, char *b)
{
	int l = 0;
	size_t len;
	unsigned int hash = 0;
	element *p1, *p2;

	len = strlen (b);
	hash = t->fptr (b, len) % TABLE_SIZE;


	if (t->list[hash] != NULL)
	{
		p1 = t->list[hash];
		if (!strcmp (b, p1->str))
		{
			t->list[hash] = p1->next;
			free(p1);
			l = 1;

		}
		else
		{
		do
		{
			if(!strcmp (b, p1->str))
			{
				p2->next = p1->next;
				free (p1);
				l = 1;
			}
			else
			{
				p2 = p1;
				p1 = p1->next;
			}
		}while ((p1 != NULL) && (!l));

		}

	}


	return l;
}
void stat (tab *t, unsigned int *nepust, unsigned int *kolel,
			unsigned int *min, unsigned int *max, double *sred)
{
	size_t len;
	element *p1;
	unsigned int i, val, l = 1;

	*nepust = 0;
	*kolel = 0;
	*max = 0;
	*min = 0;

	for (i = 0; i < TABLE_SIZE; i++)
	{
		if (t->list[i] != NULL)
		{
			*nepust += 1;
			val = 0;
			p1 = t->list[i];
			while (p1 != NULL)
			{
				val++;
				p1 = p1->next;
			}
			if (val > *max)
			{
				*max = val;
			}
			if (l)
			{
				*min = val;
				l = 0;
			}
			if (val < *min)
			{
				*min = val;
			}
			*kolel += val;

		}
	}
	if (*nepust != 0)
	{
		*sred = *kolel;
		*sred = *sred / *nepust;
	}
	else
	{
		sred = 0;
	}

	return ;
}


int get_el (tab *t, char *b)
{
	int val = 0;
	size_t len;
	unsigned int hash = 0;
	element *p1;

	len = strlen (b);
	hash = t->fptr (b, len) % TABLE_SIZE;

	p1 = t->list[hash];

	while (p1 != NULL)
	{
		if(!strcmp (b, p1->str))
		{
			val = p1->val;
			break;
		}
		p1 = p1->next;
	}

	return val;
}
int add_el (tab *t, char *b)
{
	int l = 1, er = 0;
	size_t len;
	unsigned int hash = 0;
	element *p1, *p2;

	len = strlen (b);
	hash = t->fptr (b, len) % TABLE_SIZE;
	if (t->list[hash] == NULL)
	{
		t->list[hash] = (element*)malloc (sizeof(element));
		if (t->list[hash] != NULL)
		{
			t->list[hash]->str = (char*)malloc (len + 1);
			if (t->list[hash]->str != NULL)
			{
				t->list[hash]->next = NULL;
				t->list[hash]->val = 1;
				strcpy(t->list[hash]->str, b);
			}
			else
			{
				free (t->list[hash]);
				t->list[hash] = NULL;
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
		p1 = t->list[hash];
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


void zap (tab *t)
{
	int i, j;
	size_t len;
	FILE  *fp;
	char line[255], buffer[max_string];
	element *p1, *p2;

	fp = fopen ("output.txt","w");

	if (fp != NULL)
	{

		for (i = 0; i < TABLE_SIZE; i++)
		{
			if (t->list[i] != NULL)
			{
				p1 = t->list[i];
				while (p1 != NULL)
				{
					fputs(p1->str, fp);
					fputc(' ',fp);
					sprintf(buffer, "%d", p1->val);
					fputs(buffer, fp);
					fputc ('\x0A', fp);
					p1 = p1->next;
				}
			}
		}
	fclose (fp);
	}
}


int gruz (tab *t)
{
	int i, j, l = 0;
	size_t len;
	FILE  *fp;
	char line[255], buffer[max_string];

	fp = fopen ("input.txt","r");
	if (fp != NULL)
	{

		while (fgets (line,255,fp)!=NULL)
		{
//			puts (line);
			len = strlen (line);
			j = 0;
			for (i = 0; i < len; i++)
			{
				if (isBukva (line[i]))
				{
					buffer[j] = UpCase (line[i]);
					j++;
				}
				else
				{
					if(j)
					{
						buffer[j] = '\0';
						l = l | add_el (t, buffer);
						//puts(buffer);
						//getch();
						j = 0;
					}
				}
			}

		}
		fclose (fp);

	}
	return l;
}

int main(void)
{
	tab TAB;
	unsigned int (*hf)(char*, unsigned int) = NULL;
	char buffer[max_string];
	size_t len;
	int hod, bol = 1, gr;
	unsigned int nepust, kolel, min, max;
	double sred;
	clock_t cl_start,cl_finish;
	double sek;
	FILE  *fp;
	char line[255];

	fp = fopen ("help2.txt", "r");
	if (fp != NULL)
	{
		while (fgets (line,255,fp)!=NULL)
		{
		puts (line);
		}
		fclose(fp);
	}

	TAB.list = NULL;
	hf = ROT13Hash;

	do
	{
		hod = getch();
		switch (hod)
		{
		case '1':
			if (TAB.list == NULL)
			{
				hf = constHash;
				printf("const\n");
			}
		break;
		case '2':
			if (TAB.list == NULL)
			{
				hf = sumHash;
				printf("sum\n");
			}
		break;
		case '3':
			if (TAB.list == NULL)
			{
				hf = faq6Hash;
				printf("faq6\n");
			}
		break;
		case '4':
			if (TAB.list == NULL)
			{
				hf = ROT13Hash;
				printf("rot13\n");
			}
		break;
		case 'q':
			if (TAB.list != NULL)
			{
				clear_tab (&TAB);
				puts("The table is deleted");
			}
			else
			{
				puts("The table not created yet");
			}
			bol = 0;
		break;
		case 'c':
			if (TAB.list == NULL)
			{
				create_tab (&TAB, hf);
				if (TAB.list != NULL)
				{
					puts("The table is created");
				}
				else
				{
					puts("Not enough memory");
				}
			}
		break;
		case 'a':
			if (TAB.list != NULL)
			{
				scanf ("%25s", buffer);
				if (add_el (&TAB, buffer))
				{
					puts("Not enough memory");
				}
			}
			else
			{
				puts("The table not created yet");
			}
		break;
		case 'g':
			if (TAB.list != NULL)
			{
				scanf ("%25s", buffer);

				printf ("%d\n",get_el (&TAB, buffer));
			}
			else
			{
				puts("The table not created yet");
			}
		break;
		case 'd':
			if (TAB.list != NULL)
			{
				scanf ("%25s", buffer);
				if (!del_el (&TAB, buffer))
				{
					puts("The element is missing in the table");
				}
				else
				{
					puts("The element is deleted");

				}
			}
			else
			{
				puts("The table not created yet");
			}
		break;
		case 's':
			if (TAB.list != NULL)
			{
				stat (&TAB, &nepust, &kolel, &min, &max, &sred);
			printf("%d %d %d %d %f \n", nepust, kolel, min, max, sred);

			}
			else
			{
				puts("The table not created yet");
			}
		break;
		case 'f':
			if (TAB.list != NULL)
			{
				cl_start = clock();
				gr = gruz (&TAB);
				if (gr)
				{
					puts("Not enough memory");
				}
				else
				{
					cl_finish = clock();
					sek = cl_finish - cl_start;
					sek = sek / CLOCKS_PER_SEC;
					printf("%f\n",sek);
				}
			}
			else
			{
				puts("The table not created yet");
			}

		break;

		case 'z':
			if (TAB.list != NULL)
			{
				zap (&TAB);

			}
			else
			{
				puts("The table not created yet");
			}

		break;

		}
	} while(bol);

	return 0;
}
