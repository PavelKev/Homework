#include <conio.h>
#include <stdio.h>
union dub
{
    unsigned int x;
    float y;
};
typedef union dub DUB;

void floatBits1(float a)
{
  DUB t;
  unsigned int k,b;
  int i;

  k=1;
  k=k<<31;
  t.y=a;
  for(i=31;i>=0;i--)
  {
     b=t.x&k;
     b=b>>i;
     printf("%d",b);
     k=k>>1;
  }
}

int main()
{
    floatBits1(0.01);
    return 0;
}
