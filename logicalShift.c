#include <stdio.h>
#include <conio.h>
#include <limits.h>

int logicalShift(int x,int n)
{
int a,res;

res=x>>n;
a=7;
a=a<<4;
a=a+0xF;
a=a<<4;
a=a+0xF;
a=a<<4;
a=a+0xF;
a=a<<4;
a=a+0xF;
a=a<<4;
a=a+0xF;
a=a<<4;
a=a+0xF;
a=a<<4;
a=a+0xF;
a=a>>n;
a=a<<1;
a=a+1;
res=res&a;
return res;
}
