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
        printf("�ü����ΪС�˷�");
    }
    else
    {
        flag = 0;
        printf("�ü����Ϊ��η�");
    }
    return 0;
}