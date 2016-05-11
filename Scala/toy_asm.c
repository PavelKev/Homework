#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define NAME "task2.asm"

#define SIZE_OF_MEMORY 262144

#define OUT_OF_MEMORY -1

#define ERROR_OPEN_FILE -3
#define SYNTAX_ERROR -5
#define LINK_ERROR_1 -7//Две разные команды помечены одинаковой меткой
#define LINK_ERROR_2 -9//Ссылка на несуществующую метку
#define STACK_ERROR -11//Чтение из пустого стека
#define PROGRAM_ERROR_1 -13//Выход IP за пределы количества команд
#define PROGRAM_ERROR_2 -15//Обращение к памяти вне пределов выделенной области

typedef struct Metka//Элеменнт списка меток
{
	char str[25];
	unsigned int val;
	struct Metka *next;
}metka;

typedef struct Coman//Элемент массива команд
{
	char co;
	unsigned int arg;
}comand;
typedef struct ElS//Элемент стека
{
	int val;
	struct ElS *next;
}els;

unsigned int errnom = 0;


void printmet (metka *p)//Печать списка меток (для отладки)
{
	while (p != NULL)
	{
		printf("%d %s\n", p->val, p->str);
		p = p->next;
	}
	return;
}
metka* freemet (metka *h)//Удаление списка меток с освобождением памяти
{
	metka *p = NULL;
	
	p = h;
	while (p != NULL)
	{
		p = p->next;
		free (h);
		h = p;
	}
	return h;
}

metka* addmet(unsigned int a, char* str, metka* h)//Добавление метки в список меток
{
	metka *p = NULL, *p1;
	
	if (h == NULL)
	{
		h = (metka*)malloc (sizeof (metka));
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
			p1->next = (metka*)malloc (sizeof (metka));
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
char ch_com(char* co)//Возвращает символ - номер команды по строке
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

metka* inivrem(metka* mmm, unsigned int* numc)	//Создаёт список меток и временный файл vrem.tmp без меток, коментариев,
{												//и с более упорядоченной структурой (одна строка - одна команда, команды
	FILE *fp = NULL, *fpv = NULL;				//представленны одним символом, а не строкой переменной длины, между
	int sost = 0;								//командой и аргументом один пробел, лишние переводы строки, пробелы и 
	unsigned int lcom, ef;						//табуляции удалены, переводы строки могут быть и добавлены)
	char comanda [25], sim;
	char est_metka = 0, est_com = 0, coma;

	
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
		case 0:
			switch (sim) 
			{
			case ':':
				sost = -100;
			break;
			case '\r':
			case '\n':
			case ' ':
			case '\t':
			break;
			case ';':
				sost = 2;
			break;
			default:
				sost = 1;
				lcom = 1;
				comanda [0] = sim;
			}
		break;
		case 1:
			switch (sim)
			{
			case ':':
				if ((!est_metka)&&(!est_com))
				{
					comanda [lcom] = '\0';
					mmm = addmet(*numc, comanda, mmm);
					est_metka = 1;
					sost = 0;
				}
				else
				{
					sost = -100;
				}
			break;
			case '\r':
			case ' ':
			case '\n':
			case '\t':
			case ';':
				comanda [lcom] = '\0';
				
				if(!est_com)
				{
					coma = ch_com(comanda);
					switch (coma)
					{
						case '0':
							sost = -100;
						break;
						case '1':
						case '2':
						case '3':
						case '7':
						case '8':
							fputc (coma, fpv);
							est_com = 1;
							if (sim == ';') 
							{
								sost = 2;
							}
							else
							{
								sost = 0;
							}
						break;
						case '4':
						case '5':
						case '6':
						case '9':
							fputc (coma, fpv);
							fputc ('\n', fpv);
							(*numc)++;
							est_metka = 0;
							if (sim == ';') 
							{
								sost = 2;
							}
							else
							{
								sost = 0;
							}
						break;
					}
				}
				else
				{
					fputs (comanda, fpv);
					fputc ('\n', fpv);
					(*numc)++;
					est_metka = 0;
					est_com = 0;
					if (sim == ';') 
					{
						sost = 2;
					}
					else
					{
						sost = 0;
					}
				}
				
			break;
			default:
				comanda [lcom] = sim;
				lcom++;
				if (lcom >= 25)
				{
					sost = -100;
				}
			}
		break;
		case 2:
			switch (sim)
			{
			case '\r':
			case '\n':
				sost = 0;
			break;
			}
		break;
		case -100:
			fclose (fpv);
			fclose (fp);
			errnom = SYNTAX_ERROR;
			return NULL;
		break;
		}
		if(sost != -100)
		{
			ef = fread (&sim, sizeof(char), 1, fp);
		}
		
	};
	
	if (est_com)
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

void print_prog (comand* p, unsigned int* numc)//Печать массива команд (для отладки)
{
	unsigned int i;
	
	for (i = 0; i < *numc; i++)
	{
		printf("%d %c %d\n", i, p[i].co, p[i].arg);
	}
}

comand* inilink (comand* p, metka* h)	//Создаёт из временного файла массив команд, заменяя аргументы-метки на
{										//номера команд согласно списку меток
	FILE *fpv = NULL;
	char line[26], eme[26];
	metka *hh;
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

els* step(els* s, int* h, comand* p, unsigned int* sstack, unsigned int* IP)//Выполняет одну команду из массива команд
{
	int rez;
	els *sv = NULL;
	
	switch (p[*IP].co)
	{
		case '1':
			sv = (els*)malloc (sizeof (els));
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
			sv = (els*)malloc (sizeof (els));
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
els* freestack(els* h)//Удаление стека с освобождением памяти
{
	els *p = NULL;
	
	p = h;
	while (p != NULL)
	{
		p = p->next;
		free (h);
		h = p;
	}
	return h;
}
void printstack (els *p)//Печать стека
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
	metka *metki = NULL;
	char ag;
	unsigned int sstack = 0, IP = 0, numc = 0;
	
	int *pamiat = NULL;
	els *stack = NULL;

	metki = inivrem(metki, &numc);
//	printmet (metki);

	if (!errnom)
	{
		prog = (comand*) malloc (numc * sizeof(comand));
		if (prog != NULL)
		{
			prog = inilink (prog, metki);
//			print_prog (prog, &numc);
		}
		else
		{
			errnom = OUT_OF_MEMORY;
		}

	}
	metki = freemet (metki);
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
					printstack(stack);
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
					printstack(stack);					
				break;
				}

			}
		
		
			stack = freestack (stack);
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

