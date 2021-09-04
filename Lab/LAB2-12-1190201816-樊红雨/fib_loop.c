#include<stdio.h>
int fib_loopint(int n)
{
	int a = 1, b = 1, c;
	for (int i = 2; i < n; i++)
	{
	    c = a + b;
		a = b;
		b = c;
	}
	return c;
}
long fib_looplong(int n)
{
	long a = 1, b = 1, c;
	for (int i = 2; i < n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

unsigned int fib_loopui(int n)
{
	unsigned int a = 1, b = 1, c=1;
	for (int i = 2; i < n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}
unsigned long fib_loopul(int n)
{
	unsigned long a = 1, b = 1, c=1;
	for (int i = 2; i < n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}
int main()
{
	int n1, n2, n3, n4;
	for (n1 = 3; fib_loopint(n1) > 0; n1++)
	{
	}
	printf("int��nΪ %d\n", n1);
	for (n2 = 3; fib_looplong(n2) > 0; n2++)
	{
	}
	printf("long��nΪ %d\n", n2);

	for (n3 = 3; fib_loopui(n3) > fib_loop3(n3 - 1); n3++)
	{
	}
	printf("unsigned int��nΪ %d\n", n3);
	for (n4 = 3; fib_loopul(n4) >fib_loop4(n4 - 1); n4++)
	{
	}
	printf("unsigned long��nΪ %d\n", n4);
	return 0;
}
