#include <stdio.h>
#include <windows.h>
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start ,size_t len)
{
    size_t i;
    for(i=0 ; i < len ; i++)
        printf(" %.2x",start[i]);
    printf("\n");
}

void show_int(int x)
{
    show_bytes((byte_pointer) &x , sizeof(int));
    
}

void show_float(float x)
{
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x)
{
    show_bytes((byte_pointer)&x ,sizeof(void *));
}

int main()
{
    int i = 16;
    int flag;
    float f = 1.0;
    scanf("%d",&flag);
    if(flag == 1)
    {
        printf("int���ͱ���16��Windows64λϵͳ�е�ʮ�����ƴ洢��ʽΪ��");
    }
    else
    {
        printf("int���ͱ���16��Linux64λϵͳ�е�ʮ�����ƴ洢��ʽΪ��");
    }
    
    show_int(i);
    system("pause");
    return 0;
}