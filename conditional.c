#include <stdio.h>
#include <conio.h>
#include <limits.h>

int conditional(int x,int y,int z)
{
int xz,res;
x=!x;
x=!x;
x=x<<31;
x=x>>31;
xz=~x;
res=y&x;
xz=z&xz;
res=res+xz;

return res;
}
