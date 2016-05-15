#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define NAME "task2.asm"

#define SIZE_OF_MEMORY 262144

#define OUT_OF_MEMORY -1

#define ERROR_OPEN_FILE -3
#define SYNTAX_ERROR -5
#define LINK_ERROR_1 -7//��� ������ ������� �������� ���������� ������
#define LINK_ERROR_2 -9//������ �� �������������� �����
#define STACK_ERROR -11//������ �� ������� �����
#define PROGRAM_ERROR_1 -13//����� IP �� ������� ���������� ������
#define PROGRAM_ERROR_2 -15//��������� � ������ ��� �������� ���������� �������

//��������� ������ �� �����
#define READ_SPASE 0
#define READ_CMD 1
#define READ_COMMENT 2
#define READ_ERROR -100


typedef struct Label//�������� ������ �����
{
	char str[25];
	unsigned int val;
	struct Label *next;
}label;

typedef struct Comand//������� ������� ������
{
	char co;
	unsigned int arg;
}comand;
typedef struct Element_of_Stack//������� �����
{
	int val;
	struct Element_of_Stack *next;
}element_of_stack;

unsigned int errnom = 0;

void print_label (label *p)//������ ������ ����� (��� �������)
{
	while (p != NULL)
	{
		printf("%d %s\n", p->val, p->str);
		p = p->next;
	}
	return;
}
label* free_label (label *h)//�������� ������ ����� � ������������� ������
{
	label *p = NULL;

	p = h;
	while (p != NULL)
	{
		p = p->next;
		free (h);
		h = p;
	}
	return h;
}

label* add_label (unsigned int a, char* str, label* h)//���������� ����� � ������ �����
{
	label *p = NULL, *p1;

	if (h == NULL)
	{
		h = (label*)malloc (sizeof (label));
		if (h != NULL)
		{
			h->val = a;
			strcpy (h->str, str);
			h->next = NULL;
		}
		else
		{
			errnom = OUT_OF_MEMORY;
		}
	}
	else
	{
		p = h;
		while (p != NULL)
		{
			if (!strcmp(p->str, str))
			{
				errnom = LINK_ERROR_1;
			}
			p1 = p;
			p = p->next;
		};

		if (!errnom)
		{
			p1->next = (label*)malloc (sizeof (label));
			if (p1->next != NULL)
			{
				p1 = p1->next;
				p1->val = a;
				strcpy (p1->str, str);
				p1->next = NULL;
			}
			else
			{
				errnom = OUT_OF_MEMORY;
			}
		}
	}

	return h;
}
char ch_com(char* co)//���������� ������ - ����� ������� �� ������
{
	if (!strcmp(co,"ld")) return '1';
	if (!strcmp(co,"st")) return '2';
	if (!strcmp(co,"ldc")) return '3';
	if (!strcmp(co,"add")) return '4';
	if (!strcmp(co,"sub")) return '5';
	if (!strcmp(co,"cmp")) return '6';
	if (!strcmp(co,"jmp")) return '7';
	if (!strcmp(co,"br")) return '8';
	if (!strcmp(co,"ret")) return '9';

	return '0';
	}
	void fine (void)
	{
		FILE *fp = NULL;
		fp = fopen(NAME, "a");
		fputc ('\n', fp);
		fclose(fp);

	}

label* init_temp_file(label* mmm, unsigned int* numc)	//������ ������ ����� � ��������� ���� vrem.tmp ��� �����, �����������,
{												//� � ����� ������������� ���������� (���� ������ - ���� �������, �������
	FILE *fp = NULL, *fpv = NULL;				//������������� ����� ��������, � �� ������� ���������� �����, �����
	int sost = 0;								//�������� � ���������� ���� ������, ������ �������� ������, ������� �
	unsigned int lcom, ef;						//��������� �������, �������� ������ ����� ���� � ���������)
	char comanda [25], sim;
	char ex_label = 0, ex_cmd = 0, coma;


	//fine();
	fp = fopen(NAME, "rb");
	if (fp == NULL)
	{
		errnom = ERROR_OPEN_FILE;
		return NULL;
	}
	fpv = fopen("vrem.tmp", "w");

	ef = fread(&sim, sizeof(char), 1, fp);
 	while(ef)
	{
		switch (sost)
		{
		case READ_SPASE:
			switch (sim)
			{
			case ':':
				sost = READ_ERROR;
			break;
			case '\r':
			case '\n':
			case ' ':
			case '\t':
			break;
			case ';':
				sost = READ_COMMENT;
			break;
			default:
				sost = READ_CMD;
				lcom = 1;
				comanda [0] = sim;
			}
		break;
		case READ_CMD:
			switch (sim)
			{
			case ':':
				if ((!ex_label)&&(!ex_cmd))
				{
					comanda [lcom] = '\0';
					mmm = add_label(*numc, comanda, mmm);
					ex_label = 1;
					sost = READ_SPASE;
				}
				else
				{
					sost = READ_ERROR;
				}
			break;
			case '\r':
			case ' ':
			case '\n':
			case '\t':
			case ';':
				comanda [lcom] = '\0';

				if(!ex_cmd)
				{
					coma = ch_com(comanda);
					switch (coma)
					{
						case '0':
							sost = READ_ERROR;
						break;
						case '1':
						case '2':
						case '3':
						case '7':
						case '8':
							fputc (coma, fpv);
							ex_cmd = 1;
							if (sim == ';')
							{
								sost = READ_COMMENT;
							}
							else
							{
								sost = READ_SPASE;
							}
						break;
						case '4':
						case '5':
						case '6':
						case '9':
							fputc (coma, fpv);
							fputc ('\n', fpv);
							(*numc)++;
							ex_label = 0;
							if (sim == ';')
							{
								sost = READ_COMMENT;
							}
							else
							{
								sost = READ_SPASE;
							}
						break;
					}
				}
				else
				{
					fputs (comanda, fpv);
					fputc ('\n', fpv);
					(*numc)++;
					ex_label = 0;
					ex_cmd = 0;
					if (sim == ';')
					{
						sost = READ_COMMENT;
					}
					else
					{
						sost = READ_SPASE;
					}
				}

			break;
			default:
				comanda [lcom] = sim;
				lcom++;
				if (lcom >= 25)
				{
					sost = READ_ERROR;
				}
			}
		break;
		case READ_COMMENT:
			switch (sim)
			{
			case '\r':
			case '\n':
				sost = READ_SPASE;
			break;
			}
		break;
		case READ_ERROR:
			fclose (fpv);
			fclose (fp);
			errnom = SYNTAX_ERROR;
			return NULL;
		break;
		}
		if(sost != READ_ERROR)
		{
			ef = fread (&sim, sizeof(char), 1, fp);
		}

	};

	if (ex_cmd)
	{
		errnom = SYNTAX_ERROR;
	}
	else
	{
		printf ("File %s OK: %d commands\n", NAME, *numc);
	}
	fclose (fpv);
	fclose (fp);

	return mmm;
}

void print_program (comand* p, unsigned int* numc)//������ ������� ������ (��� �������)
{
	unsigned int i;

	for (i = 0; i < *numc; i++)
	{
		printf("%d %c %d\n", i, p[i].co, p[i].arg);
	}
}

comand* init_vrem (comand* p, label* h)	//������ �� ���������� ����� ������ ������, ������� ���������-����� ��
{										//������ ������ �������� ������ �����
	FILE *fpv = NULL;
	char line[26], eme[26];
	label *hh;
	unsigned int nc = 0, l, i;

	fpv = fopen("vrem.tmp", "r");

	while (fgets (line, 255, fpv) != NULL)
	{
		switch (line[0])
		{
			case '4':
			case '5':
			case '6':
			case '9':
				p[nc].co = line[0];
				p[nc].arg = 0;
				nc++;
			break;
			case '1':
			case '2':
			case '3':
				p[nc].co = line[0];
				p[nc].arg = atoi (&(line[1]));
				nc++;
			break;
			case '7':
			case '8':
				p[nc].co = line[0];
				hh = h;
				l = 0;
				while (hh != NULL)
				{
					i = 0;
					while(line[i+1] != '\n')
					{
						eme[i] = line [i+1];
						i++;
					}
					eme[i] = '\0';

					if (!strcmp(hh->str, eme))
					{
						l = 1;
						p[nc].arg = hh->val;
					}
					hh = hh->next;
				}
				if (l == 0)
				{
					errnom = LINK_ERROR_2;
				}
				nc++;
			break;

		}
	}

	fclose (fpv);
	return p;

}

element_of_stack* step(element_of_stack* s, int* h, comand* p, unsigned int* sstack, unsigned int* IP)//��������� ���� ������� �� ������� ������
{
	int rez;
	element_of_stack *sv = NULL;

	switch (p[*IP].co)
	{
		case '1':
			sv = (element_of_stack*)malloc (sizeof (element_of_stack));
			if (sv != NULL)
			{
				if ((p[*IP].arg < SIZE_OF_MEMORY) && (p[*IP].arg >= 0))
				{
					sv->val = h[p[*IP].arg];
					sv->next = s;
					s = sv;
					(*IP)++;
					(*sstack)++;
				}
				else
				{
					errnom = PROGRAM_ERROR_2;
				}
			}
			else
			{
				errnom = OUT_OF_MEMORY;
			}
		break;
		case '2':
			if (*sstack != 0)
			{
				if ((p[*IP].arg < SIZE_OF_MEMORY) && (p[*IP].arg >= 0))
				{
					sv = s;
					h [p[*IP].arg] = sv->val;
					s = s->next;
					free (sv);
					(*IP)++;
					(*sstack)--;
				}
				else
				{
					errnom = PROGRAM_ERROR_2;
				}
			}
			else
			{
				errnom = STACK_ERROR;
			}
		break;
		case '3':
			sv = (element_of_stack*)malloc (sizeof (element_of_stack));
			if (sv != NULL)
			{
				sv->val = p[*IP].arg;
				sv->next = s;
				s = sv;
				(*IP)++;
				(*sstack)++;
			}
			else
			{
				errnom = OUT_OF_MEMORY;
			}
		break;
		case '4':
			if (*sstack >= 2)
			{
				sv = s;
				s = s->next;
				s->val = sv->val + s->val;
				free (sv);
				(*IP)++;
				(*sstack)--;
			}
			else
			{
				errnom = STACK_ERROR;
			}
		break;
		case '5':
			if (*sstack >= 2)
			{
				sv = s;
				s = s->next;
				s->val = sv->val - s->val;
				free (sv);
				(*IP)++;
				(*sstack)--;
			}
			else
			{
				errnom = STACK_ERROR;
			}
		break;
		case '6':
			if (*sstack >= 2)
			{
				sv = s;
				s = s->next;
					if (sv->val == s->val)
					{
						s->val = 0;
					}
					else
					{
						if (sv->val > s->val)
						{
							s->val = 1;
						}
						else
						{
							s->val = -1;
						}
					}
				free (sv);
				(*IP)++;
				(*sstack)--;
			}
			else
			{
				errnom = STACK_ERROR;
			}
		break;
		case '7':
			*IP = p[*IP].arg;
		break;
		case '8':
			if (*sstack != 0)
			{
				if (s->val != 0)
				{
					*IP = p[*IP].arg;
				}
				else
				{
					(*IP)++;
				}
				sv = s;
				s = s->next;
				free (sv);
				(*sstack)--;
			}
			else
			{
				errnom = STACK_ERROR;
			}
		break;
		case '9':
			errnom = 2016;
		break;
	}

	return s;
}
element_of_stack* free_stack(element_of_stack* h)//�������� ����� � ������������� ������
{
	element_of_stack *p = NULL;

	p = h;
	while (p != NULL)
	{
		p = p->next;
		free (h);
		h = p;
	}
	return h;
}
void print_stack (element_of_stack *p)//������ �����
{
	printf("Stack: ");
	while (p != NULL)
	{
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
	return;
}

int main(void)
{
	comand *prog = NULL;
	label *labels = NULL;
	char ag;
	unsigned int sstack = 0, IP = 0, numc = 0;

	int *pamiat = NULL;
	element_of_stack *stack = NULL;

	labels = init_temp_file(labels, &numc);
//	print_label (labels);

	if (!errnom)
	{
		prog = (comand*) malloc (numc * sizeof(comand));
		if (prog != NULL)
		{
			prog = init_vrem (prog, labels);
//			print_program (prog, &numc);
		}
		else
		{
			errnom = OUT_OF_MEMORY;
		}

	}
	labels = free_label (labels);
	unlink("vrem.tmp");
	if (!errnom)
	{
		printf("Preprocessing completed successfully\n");
		printf("R - run; S - step; Q - exit\n");

		ag = '0';
		pamiat = (int*) malloc (SIZE_OF_MEMORY * sizeof(int));
		if (pamiat != NULL)
		{
			while ((ag != 'q') && (ag != 'Q'))
			{
				ag = getch();
				switch (ag)
				{
				case 'S':
				case 's':
					stack = step (stack, pamiat, prog, &sstack, &IP);
					printf ("IP = %d, ", IP);
					print_stack(stack);
					if (IP >= numc)
					{
						errnom = PROGRAM_ERROR_1;
					}
					if (errnom == 2016)
					{
						errnom = 0;
						ag = 'q';
					}
					if (errnom)
					{
						ag = 'q';
					}
				break;
				case 'R':
				case 'r':
					while ((ag != 'q') && (ag != 'Q'))
					{
						stack = step (stack, pamiat, prog, &sstack, &IP);
						if (IP >= numc)
						{
							errnom = PROGRAM_ERROR_1;
						}
						if (errnom == 2016)
						{
							errnom = 0;
							ag = 'q';
						}
						if (errnom)
						{
							ag = 'q';
						}
					}
					print_stack(stack);
				break;
				}

			}


			stack = free_stack (stack);
			free (pamiat);
		}
		else
		{
			errnom = OUT_OF_MEMORY;
		}
	}
	if (prog != NULL) free (prog);
	switch (errnom)
	{
	case 0:
		printf ("End of program\n");
	break;
	case OUT_OF_MEMORY:
		printf ("Out of memory\n");
	break;
	case ERROR_OPEN_FILE:
		printf ("Error opening file\n");
	break;
	case SYNTAX_ERROR:
		printf ("Syntax error\n");
	break;
	case LINK_ERROR_1:
		printf ("Link error N1\n");
	break;
	case LINK_ERROR_2:
		printf ("Link error N2\n");
	break;
	case STACK_ERROR:
		printf ("Stack error\n");
	break;
	case PROGRAM_ERROR_1:
		printf ("Program error N1\n");
	break;
	case PROGRAM_ERROR_2:
		printf ("Program error N2\n");
	break;
	}

	return errnom;
}

