#include <stdio.h>

unsigned srl (unsigned x, int k)
// Perform shift arithetically
{
    unsigned xsra = (int) x >> k;
    int w = sizeof(int) << 3;
    int h = (int)-1 << (w-k); //得到二进制高k位都为1的二进制数
    xsra = xsra & (~h); //~h位高k位为0，其余位为1的二进制数，逻辑右移k位的高k位都为0
    return xsra; //原二进制数和~h进行按位与得到高k位为0，其余位不变的xsra.
} 

int sra(int x, int k)
// Perfprm shift logically
{
    int xsrl = (unsigned) x >> k;
    int w = sizeof(int) << 3;
    int h = (int)-1 << (w-k);//h为高k位都为1的二进制数
    int Is_neg = x & ((int)(-1) << (w-1));
    Is_neg = Is_neg && Is_neg;//若x为负数，则Is_neg为1，否则为0
    h = h & ((!Is_neg)-1);  /*
                            若Is_neg为1，则表达式(!Is_neg)-1为-1，即二进制全为1，h和-1按位与不变
                            若Is_neg为0，则表达式(!Is_neg)-1为0，h和0按位与变为0.
                            */
    xsrl = xsrl | h;        /*
                            若x为负数原二进制数与h按位或得到得到高k位都为1其余位不变的数
                            若x为正数原二进制数与h按位或不变.
                            */
    return xsrl;
}

int main()
{
    unsigned testu = 0x80000000;
    int testi = 0x80000000;
    printf("%x\n",srl(testu,31));
    printf("%x\n",sra(testi,31));
    getchar();
    return 0;
}