#include <stdio.h>

int main()
{
    size_t word;
    word = sizeof(int*)*8;
    printf("%d",word);
    return 0;
}