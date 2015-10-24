#include <conio.h>
#include <stdio.h>
typedef struct kvar
{
    unsigned a0: 1;
    unsigned a1: 1;
    unsigned a2: 1;
    unsigned a3: 1;
    unsigned a4: 1;
    unsigned a5: 1;
    unsigned a6: 1;
    unsigned a7: 1;
    unsigned a8: 1;
    unsigned a9: 1;
    unsigned a10: 1;
    unsigned a11: 1;
    unsigned a12: 1;
    unsigned a13: 1;
    unsigned a14: 1;
    unsigned a15: 1;
    unsigned a16: 1;
    unsigned a17: 1;
    unsigned a18: 1;
    unsigned a19: 1;
    unsigned a20: 1;
    unsigned a21: 1;
    unsigned a22: 1;
    unsigned a23: 1;
    unsigned a24: 1;
    unsigned a25: 1;
    unsigned a26: 1;
    unsigned a27: 1;
    unsigned a28: 1;
    unsigned a29: 1;
    unsigned a30: 1;
    unsigned a31: 1;
} KVAR;

union dub
{
    KVAR x;
    float y;
};
typedef union dub DUB;

void floatBits2(float a)
{
  DUB t;

  t.y=a;

  printf("%d",t.x.a31);
  printf("%d",t.x.a30);
  printf("%d",t.x.a29);
  printf("%d",t.x.a28);
  printf("%d",t.x.a27);
  printf("%d",t.x.a26);
  printf("%d",t.x.a25);
  printf("%d",t.x.a24);
  printf("%d",t.x.a23);
  printf("%d",t.x.a22);
  printf("%d",t.x.a21);
  printf("%d",t.x.a20);
  printf("%d",t.x.a19);
  printf("%d",t.x.a18);
  printf("%d",t.x.a17);
  printf("%d",t.x.a16);
  printf("%d",t.x.a15);
  printf("%d",t.x.a14);
  printf("%d",t.x.a13);
  printf("%d",t.x.a12);
  printf("%d",t.x.a11);
  printf("%d",t.x.a10);
  printf("%d",t.x.a9);
  printf("%d",t.x.a8);
  printf("%d",t.x.a7);
  printf("%d",t.x.a6);
  printf("%d",t.x.a5);
  printf("%d",t.x.a4);
  printf("%d",t.x.a3);
  printf("%d",t.x.a2);
  printf("%d",t.x.a1);
  printf("%d",t.x.a0);

 }

int main()
{
    floatBits2(0.01);
    return 0;
}

