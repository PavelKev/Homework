#include <stdio.h>
#include <conio.h>
#include <limits.h>

int bitXor(int a,int b)
{
int na,nb,res;

na=~a;
nb=~b;
a=a&nb;
b=b&na;
na=~a;
nb=~b;
res=na&nb;
res=~res;
return res;
}
