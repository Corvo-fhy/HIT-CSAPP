#include <stdio.h>

int mul3div4(int x)
{
    
    int w = sizeof(int) << 3;
    int Is_neg = x >> (w-1);
    Is_neg = Is_neg && Is_neg;//若x为负数，Is_neg为1
    int Is_bias = 2 & ((!Is_neg)-1);//若x为负数，则Is_bias为2，否则为0
    int bias = (1 << Is_bias) -1;//计算偏置量
    x = (x + bias) >> 2;//进行算术右移
    return x;
}