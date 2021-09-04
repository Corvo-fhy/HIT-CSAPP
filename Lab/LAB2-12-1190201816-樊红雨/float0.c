#include <stdio.h>
#include <stdlib.h>

int main()
{
    float f = 123;
    printf("除以0：%f\n",f/0);
    printf("除以极小：%f\n",f/1e-320);
    return 0;
}
