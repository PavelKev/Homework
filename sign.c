#include <stdio.h>
#include <conio.h>
#include <limits.h>

int sign(int x)
{
int s,n,res;
s=x>>31;
n=!x;
n=!n;
res=s|n;
return res;
}
