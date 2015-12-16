#include <cstdio>
#include <conio.h>
#include <stdlib.h>

typedef struct Element
{
	int val;
	struct Element *next;
}element;

element* clear(element *h)//������� ������, �������� ������, ������� q
{
	element *p = NULL;

	p = h;
	while (p != NULL)
	{
		p = p->next;
		free(h);
		h = p;
	}
	return h;
}
void print_list(element *h)//������ ������, ������� p
{
	element *p = NULL;

	p = h;

	while (p != NULL)
	{
		printf("%d ",p->val);
		p = p->next;
	}
	printf("\n");
}

element* append(element *h)//���������� �������� � ����� ������, ������� a, ����� ����� �����
{
	element *p = NULL;
	int a;

	scanf("%d",&a);
	if (h == NULL)
	{
		h = (element*)malloc(sizeof(element));
		if (h != NULL)
		{

			h->val = a;
			h->next = NULL;
		}
		else
		{
			printf("���������� �뤥���� ������\n");
		}
	}
	else
	{
		p = h;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = (element*)malloc(sizeof(element));
		if (p != NULL)
		{
			p = p->next;
			p->val = a;
			p->next = NULL;
		}
		else
		{
			printf("���������� �뤥���� ������\n");
		}
	}
	return h;
}

element* del(element *h)//�������� ������� �����, ������� ����������, �� ������, ������� r, ����� ����� �����
{
	element *p = NULL,*p1 = NULL;
	int a,bol;

	scanf("%d",&a);

	p = h;

	if (h->val == a)
	{
		h = h->next;
		free(p);
	}
	else
	{
		p1 = h;
		bol = 1;
		while ((p->next != NULL)&&(bol))
		{
			p1 = p->next;
			if (p1->val == a)
			{
				p->next = p1->next;
				free(p1);
				bol = 0;
			}
			else
			{
				p = p1;
			}
		}
	}
	return h;
}

element* first(element *h)//���������� �������� � ������ ������, ������� f, ����� ����� �����
{
	element *p = NULL;
	int a;

	scanf("%d",&a);
	p = (element*)malloc(sizeof(element));
	if (p != NULL)
	{
		p->val = a;
		p->next = h;
	}
	else
	{
		p = h;
		printf("���������� �뤥���� ������\n");
	}

	return p;
}

int main(void)
{
	int hod,bol = 1;
	element *head = NULL;

	do
	{
		hod = getch();
//		printf("%d\n",hod);
		switch (hod)
		{
		case 'a':
			head = append(head);
		break;
		case 'f':
			head = first(head);
		break;
		case 'p':
			print_list(head);
		break;
		case 'q':
			head = clear(head);
			bol = 0;
		break;
		case 'r':
			head = del(head);
		break;
		}

	} while(bol);


	return 0;
}
