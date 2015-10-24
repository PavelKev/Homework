#include <stdio.h>
#include <conio.h>
#include <limits.h>

int thirdBits(void)
{
int a,i,res;

a=36;
res=36;
a=a<<3;
res=res+a;
a=a<<3;
res=res+a;
a=a<<3;
res=res+a;
a=a<<3;
res=res+a;

return res;
}
