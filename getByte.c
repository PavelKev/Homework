#include <stdio.h>
#include <conio.h>
#include <limits.h>

int getByte(int x,int n)
{
 int res;
 n=n<<3;
 x=x>>n;
 res=x&255;
return res;
}
