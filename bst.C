#include <stdlib.h>
#include <conio.h>
#include <stdlib.h>

typedef struct Element
{
	int val;
	struct Element *left;
	struct Element *right;
}element;

element* append(element *h, int a)
{

	if(h == NULL)
	{
		h = (element*)malloc(sizeof(element));
		if (h != NULL)
		{
			h->val = a;
			h->left = NULL;
			h->right = NULL;
		}
		else
		{
			puts("Not enough memory");
		}
	}
	else
	{
		if (a < h->val)
		{
			h->left = append(h->left, a);
		}
		else
		{
			if (a > h->val)
			{
				h->right = append(h->right, a);
			}
		}

	}

	return h;
}

int check_a (element *h, int a, int l)
{
	if (h != NULL)
	{
		if (!l)
		{
			if (h-> val == a)
			{
				l = 1;
			}
			else
			{
				l = check_a (h->left, a, l);
				l = check_a (h->right, a, l);
			}
		}
	}
	return l;
}
element* del_a (element *h, int a)
{
	element *p;
	if (h != NULL)
	{
		if (a < h->val)
		{
			h->left = del_a (h->left, a);
		}
		else
		{
			if (a > h-> val)
			{
				h->right = del_a (h->right, a);
			}
			else
			{
				if (a == h-> val)
				{
					if ((h->left == NULL)&&(h->right == NULL))
					{
						free(h);
						return NULL;
					}
					if (h->left == NULL)
					{
						p = h->right;
						h->val = h->right->val;
						h->left = h->right->left;
						h->right = h->right->right;
						free(p);
						return h;
					}
					if (h->right == NULL)
					{
						p = h->left;
						h->val = h->left->val;
						h->right = h->left->right;
						h->left = h->left->left;
						free(p);
						return h;
					}
					if (h->left->right == NULL)
					{
						p = h;
						h->left->right = h->right;
						h = h->left;
						free(p);
						return h;
					}
					p = h->left;
					while (p->right != NULL)
					{
						p = p->right;
					}
					h->val = p->val;
					h->left = del_a (h->left, p->val);

				}
			}
		}

	}
	return h;
}
void go_up (element *h)
{
	if (h != NULL)
	{
		go_up (h->left);
		printf ("%d ", h->val);
		go_up (h->right);
	}
}
void go_down (element *h)
{
	if (h != NULL)
	{
		go_down (h->right);
		printf ("%d ", h->val);
		go_down (h->left);
	}
}
void clear (element *h)
{
	if (h != NULL)
	{
		clear (h->left);
		clear (h->right);
		free (h);
	}
}
void tree_abc (element *h)
{
	if (h != NULL)
	{
		printf(" (%d", h->val);
		tree_abc (h->left);
		tree_abc (h->right);
		printf(")");
	}
	else
	{
		printf(" null");
	}
}


int main(void)
{
	int hod, bol = 1, a, l;
	element *head = NULL;

	do
	{
		hod = getch();
		switch (hod)
		{
		case 'q':
			clear (head);
			bol = 0;
		break;
		case 'a':
			scanf("%d",&a);
			head = append (head, a);
		break;
		case 'd':
			scanf("%d",&a);
			head = del_a (head, a);
		break;
		case 'c':
			scanf("%d",&a);
			l = 0;
			if (check_a (head, a, l))
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
		break;
		case '<':
			go_up (head);
			printf ("\n");
		break;
		case '>':
			go_down (head);
			printf ("\n");
		break;
		case 't':
			tree_abc (head);
			printf ("\n");
		break;

		}

	} while(bol);


	return 0;
}
