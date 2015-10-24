#include <conio.h>
#include <stdio.h>

void floatBits3(float a)
{
  float *p;
  unsigned int *p1,k,b,x;
  int i;


  p = &a;
  p1=(unsigned int*)p;
  x=*p1;

  k = 1;
  k = k<<31;
  for(i = 31;i>=0;i--)
  {
     b=x&k;
     b=b>>i;
     printf("%d",b);
     k=k>>1;
  }
}

int main()
{
    floatBits3(0.01);
    return 0;
}
