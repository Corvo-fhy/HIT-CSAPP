#include <stdio.h>

typedef unsigned char *bytepointer;

struct structure{
    int a; 
    float b;
}stu;
enum Students{A,B,C,D,E}stuenum;
union Number{int x;float y;}numberunion;

void show_bytes(bytepointer start, size_t len);

void show_int(int x);

void show_float(float x);

void show_pointer(void *x);

void show_char(char x);

void show_double(double x);

void show_long(long x);

void show_short(short x);


int main()
{
    int i = 12345;
    short s = 123;
    long l = 12345;
    char c = 'F';
    float f = 1.25;
    double d = 2.25;
    char *pc = &c;
    stu.a = 100;
    stu.b = 50.5;
    stuenum = B;
    numberunion.x = 50;
    numberunion.y = 50.5;
    printf("main 的地址: %p\n",&main);
    printf("\n");
    printf("printf 的地址: %p \n",&printf);
    printf("\n");
    printf("int: i 的内容: %d, 地址为: %.x, 十六进制为:",i,&i);
    show_int(i);
    printf("\n");
    printf("char: c 的内容: %c, 地址为: %.x, 十六进制为:",c,pc);
    show_char(c);
    printf("\n");
    printf("float: f 的内容: %f, 地址为: %.x, 十六进制为:",f,&f);
    show_float(f);
    printf("\n");
    printf("double: d 的内容: %lf, 地址为: %.x, 十六进制为:",d,&d);
    show_double(d);
    printf("\n");
    printf("pointer 的内容: %d, 地址为: %.x, 十六进制为:",c,pc);show_pointer(pc);
    printf("\n");
    printf("struct: stu 的内容：a = %d, b = %f, 的地址为：%.x, 十六进制为:",stu.a,stu.b,&stu);show_bytes((bytepointer)&stu,sizeof(stu));
    printf("\n");
    printf("union: number的内容：number.x = %d, number.y = %f, 地址为：%.x, 十六进制为:",numberunion.x,numberunion.y,&numberunion);show_bytes((bytepointer)&numberunion,sizeof(numberunion));
    printf("\n");
    printf("enum: sdudents的地址为：%.x,  十六进制为:",&stuenum);show_bytes((bytepointer)&stuenum,sizeof(stuenum));
    printf("\n");
    getchar();
    return 0;
}

void show_bytes(bytepointer start, size_t len)
{
    size_t i;
    for(i=0;i<len;i++)
    {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x)
{
    show_bytes((char *)&x,sizeof(x));
}

void show_double(double x)
{
    show_bytes((char *)&x,sizeof(x));
}

void show_float(float x)
{
    show_bytes((char *)&x,sizeof(x));
}

void show_char(char x)
{
    show_bytes((char *)&x,sizeof(x));
}

void show_short(short x)
{
    show_bytes((char * )&x,sizeof(x));
}

void show_long(long x)
{
    show_bytes((char *)&x,sizeof(x));
}

void show_pointer(void *x)
{
    show_bytes((char * )&x,sizeof(x));
}