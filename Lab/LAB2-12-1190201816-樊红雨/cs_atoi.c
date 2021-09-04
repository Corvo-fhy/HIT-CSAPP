#include <stdio.h>
#include <string.h>
#include <math.h>
int cs_atoi(char *p)
{
    int x = 0;
    int cnt ;
    int length = strlen(p);
    cnt = pow(10,(length-1));
    while (*p != '\0')
    {
        x = x + (((unsigned)*p-48) * cnt);
        cnt = cnt / 10;
        p++;
    }
    return x;
}

int main()
{
    char cstr[100];
    int i=0;
    char  buf;
    buf = getchar();
    while (buf >=48 && buf <= 57)
    {
        cstr[i] = buf;
        i++;
        buf = getchar();
    }
    cstr[i] = '\0';
    int x = cs_atoi(cstr);
    printf("%d\n",x);
    fflush(stdin);
    getchar();
    return 0;
}