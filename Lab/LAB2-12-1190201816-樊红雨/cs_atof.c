#include <stdio.h>
#include <string.h>
#include <math.h>

double cs_atoi(char *p)
{
    double x = 0;
    double cnt ;
    int i = 0;
    int length = strlen(p);
    int num = length;
    cnt = pow(10,(length-1));
    while (*p != '\0')
    {
        if(*p != '.')
            i++;
        if(*p == '.')
        {
            p++;
            num = i;
            continue;
        }
        x = x + (((double)*p-48) * cnt);
        cnt = cnt / 10;
        p++;
    }
    if (num != length)
    {
        x = x * pow(10,-(length-num));
    }

    return x;
}

int main()
{
    char cstr[100];
    int i=0;
    char  buf;
    
    buf = getchar();
    while ((buf >=48 && buf <= 57) || buf == '.')
    {
        cstr[i] = buf;
        i++;
        buf = getchar();
    }
    cstr[i] = '\0';
    double x = cs_atoi(cstr);
    printf("%f\n",x);
    fflush(stdin);

    getchar();
    return 0;
}