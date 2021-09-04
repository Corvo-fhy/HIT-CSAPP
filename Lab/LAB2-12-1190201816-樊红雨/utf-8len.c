#include <stdio.h>
#include <windows.h>


int utf8len(char* cstr) {
	char *s = cstr;
	int length = 0;
	char byte;
	while (*s != '\0') {
		length++;
		byte = *s;
		if ((byte & 0x80) == 0) {
			s++;
		}
		else {
            int result = 0;
			do{
                byte = byte << 1;
                result++;
			}while(byte & 0x80);
			s += result;
		}
	}
	return length;
}
int main() {
	char cstr[100]="";
	scanf("%s", cstr);
	printf("%d\n", utf8len(cstr));
    system("pause");
	return 0;
}
