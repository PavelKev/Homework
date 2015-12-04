#include <stdio.h>
#include <conio.h>
#include <limits.h>

int bang(int a)
{
 int av,res;

 av=a >> 16;
 a=a | av;
 av=a >> 8;
 a=a | av;
 av=a >> 4;
 a=a | av;
 av=a >> 2;
 a=a | av;
 av=a >> 1;
 a=a | av;
 res=a & 1;
 res= !res;

return res;
}
