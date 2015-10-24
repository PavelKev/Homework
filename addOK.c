#include <stdio.h>
#include <conio.h>
#include <limits.h>

int addOK(int x,int y)
{
 int xv,yv,pr,a,res;

 a=255;
 a=a<<8;
 a=a+255;
 xv=x&a;
 yv=y&a;
 pr=xv+yv;
 pr=pr>>16;
 x=x>>16;
 y=y>>16;
 x=x&a;
 y=y&a;
 pr=x+y+pr;
 pr=pr>>16;
 res=!pr;

return res;
}
