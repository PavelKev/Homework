int isPower2(int x)
{
int x1 = x + ~0;
int _x = (x & x1); // 0 for 2^n
return (1 & !_x) & !(!x) & ~(x >> 31);
}
