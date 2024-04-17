#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


char* ipv4obfuscator(int a, int b, int c, int d);

BOOL CallerForIpv4(unsigned char* pShellcode, SIZE_T Sshellcodesize);
int main() {

	unsigned char Shellcode[] = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88 };

	unsigned char* pShellcode = Shellcode;


	SIZE_T Sshellcode = (SIZE_T) (sizeof(Shellcode));

	printf("The size of shellcode is %zu\n", Sshellcode);

	CallerForIpv4(pShellcode, Sshellcode);
	
	getchar();


}


BOOL CallerForIpv4(unsigned char* pShellcode, SIZE_T Sshellcodesize) {
	

	int no = 4, count = 0;
	char *IP = NULL;


	for (int i = 0; i < Sshellcodesize; i++) {
	
		if (no == 4) {
			printf(" pShellcode[%d] = %X\n",i, pShellcode[i]);
			IP = ipv4obfuscator(pShellcode[i], pShellcode[i + 1], pShellcode[i + 2], pShellcode[i + 3]);
			no = 1;
		}
		
		else {
			no++;

		}
	}

	if (IP != NULL) {
		printf("%s", IP);
	}
	return TRUE;
}

char* ipv4obfuscator(int a, int b, int c, int d)
{
	char* output = (char*)malloc(90 * sizeof(char));
	if (output == NULL)
	{
		printf("Heap allocation failed");
		return NULL; 
	}
	else
	{
		snprintf(output, 90, "%d.%d.%d.%d", a, b, c, d);
		printf("%s\n", output);
	}
	return output; 
}



