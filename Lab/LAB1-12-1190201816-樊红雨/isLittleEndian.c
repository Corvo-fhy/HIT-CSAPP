#include <stdio.h>

int main()
{
    int x=0x00000001;
    int flag;
    char *bytepointer;
    bytepointer = (char*) &x;
    if(bytepointer)
    {
        flag = 1;
        printf("该计算机为小端法");
    }
    else
    {
        flag = 0;
        printf("该计算机为大段法");
    }
    return 0;
}