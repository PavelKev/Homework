#include <conio.h>
#include <stdio.h>

int Endian_check(void)
//1-little-endian, 0-big-endian
{
  char *p,x;
  unsigned int *p1,k;
  int i;

  k=1;
  p1 = & k;
  p=(char*)p1;
  x=*p;
  i=x;
  return i;
}

int main()
{
  printf("%s",Endian_check()==0 ? "big-endian" : "little-endian");

  return 0;
}
