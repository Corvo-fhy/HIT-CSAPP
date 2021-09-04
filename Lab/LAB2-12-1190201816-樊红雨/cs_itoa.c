#include<stdio.h>
#include<math.h>
#include<windows.h>
int main()
{
	int num;
	char str[100];
	int n,i;
	n = 0;
	scanf("%d",&num);
	while (pow(10,n) < num)
	{
		n++;
	}
	
	for ( i = 0; i < n; i++)
	{
		str[i] = (num / ((int)(pow(10, n - i - 1))))%10 + '0';
	}
	str[n] = '\0';
	printf("%s\n", str);
	system("pause");
	return 0;
}
