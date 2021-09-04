#include <stdio.h>
#include <float.h>

int main()
{
	union 
	{
		int x;
		float y;
	}My_float[7];
	My_float[0].x = 0x00000000;
	My_float[1].x = 0x80000000;
	My_float[2].x = 0x00000001;
	My_float[3].x = 0x7f7fffff;
	My_float[4].x = 0x00800000;
	My_float[5].x = 0x7f800000;
	My_float[6].x = 0x7fffffff;
	printf("+0:%f\n", My_float[0].y);
	printf("它的十六进制:");
	printf("%x\n", My_float[0].x);
	printf("-0:%f\n", My_float[1].y);
	printf("它的十六进制:");
	printf("%x\n", My_float[1].x);
	printf("最小的浮点正数:%.100f\n", My_float[2].y);
	printf("它的十六进制:");
	printf("%x\n", My_float[2].x);
	printf("最大的浮点数:%f\n", My_float[3].y);
	printf("它的十六进制:");
	printf("%x\n", My_float[3].x);
	printf("最小正规格化浮点数:%.100f\n", My_float[4].y);
	printf("它的十六进制:");
	printf("%x\n", My_float[4].x);
	printf("正无穷大:%.100f\n", My_float[5].y);
	printf("它的十六进制:");
	printf("%x\n", My_float[5].x);
	printf("NaN:%.100f\n", My_float[6].y);
	printf("它的十六进制:");
	printf("%x\n", My_float[6].x);

	return 0;
}
