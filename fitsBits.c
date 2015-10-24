#include <stdio.h>
#include <conio.h>
#include <limits.h>

int fitsBits(int x,int n)
{
int res;
res=x>>n;
res=!res;
return res;
}
