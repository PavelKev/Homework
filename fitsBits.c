#include <stdio.h>
#include <conio.h>
#include <limits.h>

int fitsBits(int a,int b)
{
int l,x,y,res;
 b = b - 1;
 res = a >> b;
 res = !res;
 l = a >>  31;
 x = res& !l;
 a = ~a;
 res = a >> b;
 res = !res;
 y  = res & l;
 res = x | y;
return res;
}
