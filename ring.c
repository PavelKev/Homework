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
	element *p = NULL, *p1 = NULL;
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


int kontrol(element *h)//�������� �� ������������� ������. ���������� 1 - ���� ����, 0 - ����� ���
{
	element *p = NULL, *p1 = NULL;
	int k;

	k = 0;
	p1 = p = h;

	while ((p1 != NULL)&&(!k))
	{
		p1 = p1->next;
		if (p1 != NULL)
		{
			if (p1 == p)
			{
				k=1;
			}
			p1 = p1->next;
			if (p1 != NULL)
			{
				if (p1 == p)
				{
					k=1;
				}
			}
		}
		p = p->next;
	}

	return k;
}
int cirk(element *h)//������ ����� �����, ����� �������� ����� ������ �� ������� � ���������� �������
					//�� ������, ������ ����� ����� (������ - 0-���), �������� ����. ��� ������ ���������� 1.
					//���� ��������� � ������ ������, ��� ������� �����, ������������ 0 � ������ �� ��������.
					//��������� ����� ������� cirk, � ����� ������ ����� �� ������� exit, print_list �
					//append �������� ���������.
{
	element *p = NULL, *p1 = NULL;
	int rez, a, i = 0;

	scanf("%d",&a);
	p1 = p = h;
	if (h == NULL)
	{
		rez= 0;
	}
	else
	{
		while (p1->next != NULL)
		{
    		p1 = p1->next;
	    	i++;
    	}
    	if (i < a)
    	{
    		rez = 0;
		}
		else
		{
			rez = 1;
			for (i = 0; i <a; i++)
			{
				p = p->next;
			}
			p1->next = p;
		}
	}
return rez;
}


int main(void)
{
	int hod, bol = 1;
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
		case 'c':
			cirk(head);
		break;
		case 'f':
			head = first(head);
		break;
		case 'k':
			if(kontrol(head))
    		{
    			printf("yes\n");
    		}
    		else
    		{
    			printf("no\n");
    		}
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
