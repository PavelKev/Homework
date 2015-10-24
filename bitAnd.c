#include <stdio.h>
#include <conio.h>
#include <limits.h>

int bitAnd(int a,int b)
{
int res;

a=~a;
b=~b;
res=a|b;
res=~res;
return res;
