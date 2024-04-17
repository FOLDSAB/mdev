#include <stdio.h>
#include <Windows.h>


int main() {
	char shellcode[] = { 0x11,0x22,0x33,0x1a };

	printf("%s", &shellcode[1]);
	getchar();
}
