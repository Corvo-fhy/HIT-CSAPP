#include <stdio.h>
#include <inttypes.h>

int signed_high_prod(int x, int y)  //有符号数相乘的高32位
{
    int64_t mul = (int64_t) x * y;
    return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) //无符号数相乘的高32位
{
    int h_x = x >> 31;
    int h_y = y >> 31;
    int signed_prod = signed_high_prod(x,y);
    return signed_prod + x * h_y + y * h_x;
}

unsigned text(unsigned x, unsigned y)
{
    uint64_t mul =(uint64_t) x * y;
    return mul >> 32;
}
int main()
{
    printf("%d\n",text(0xffffffff,0xffffffff)==unsigned_high_prod(0xffffffff,0xffffffff));
    
    getchar();
    return 0;
}