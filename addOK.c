#include <stdio.h>
#include <conio.h>
#include <limits.h>

int addOK(int a,int b)
{
 int z,res;
 c = a + b;
 a = a >> 31;
 b = b >> 31;
 c = c >> 31;
 res = (a | !b) & (!a | b) | (!a & !b & !c) | (a & b & c);

return res;
}
