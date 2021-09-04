#include <stdio.h>
typedef unsigned float_bits;
float_bits float_half(float_bits f)
{
    unsigned s = f >> 31;
    unsigned exp = (f >> 23) &0xff;
    if(exp == 0 || exp == 1) //NaN或者正负无穷大 
    {
        return f;
    }
    unsigned frac = f & 0x7fffff;
    unsigned c = (frac & 1) && ((frac >> 1) & 1);//进位
    if (exp == 0)//非规格化数
    {
        frac >> 1;
        frac = frac + c;
    }
    else if(exp == 1)//阶码为1，需要“借位”
    {
        exp = 0;
        frac = (frac >> 1);
        frac = frac + 0x400000;
        frac = frac + c;
    }
    else
    {
        exp = exp -1;
    }
    return (s << 31) | (exp << 23) | (frac);
}