#include <stdio.h>
#include <string.h>
#include <windows.h>

int main() {
	double x;
	scanf("%lf", &x);
	int flag = 0;
	int i = 0;
	char str[100];
	if (x < 0) 
    {
		flag = 1;
		x = -x;
		str[i++] = '-';
	}
	if (x >= 0 && x < 1) 
    {
		str[i++] = '0';
	}
	int cnt = x;
	int k = 1;
	while (cnt / k) {
		k *= 10;
	}
	k /= 10;
	x -= cnt;
	while (cnt) {
		int m = cnt / k;
		cnt -= k * m;
		k =k/ 10;
		str[i++] = m + '0' - 0;
	}
	if (x != 0) {
		str[i++] = '.';
		int length = 0;
		while (x && length <= 5) {
			x *= 10;
			length++;
			int m = x;
			str[i++] = m + '0' - 0;
			x -= m;
		}
		while (length <= 5) {
			str[i++] = '0';
		}
		str[i] = '\0';
		if (x != 0)
		{
			x *= 10;
			int m = x;
			x -= m;
			i--;
			if (m >= 5)
			{
				while (i >= 0)
				{
					if (str[i] == '.'){
						i--;
						continue;
					}
					if (str[i] == '9') {
						str[i] = '0';
						i--;
						continue;
					}
					str[i]++;
					break;
				}
			}
		}
	}
	else
	{
		str[i++] = '.';
		str[i++] = '0';
		str[i++] = '0';
		str[i++] = '0';
		str[i++] = '0';
		str[i++] = '0';
		str[i++] = '0';
		str[i] = '\0';
	}
	printf("%s\n", str);
	system("pause");
	return 0;
}
