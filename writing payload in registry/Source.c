#include <stdio.h>
#include <Windows.h>
#define REGISTRY "Control Panel"
#define REGSTRING "writingpayloadinregistry"



//BOOL writeshellcodetoregistry(unsigned char* pshellcode,SIZE_T sShellcode);
BOOL ReadPaylodFromshellcode(SIZE_T sShellcode,unsigned char* pshellcode);

int main() {
	



	
	unsigned char shellcode[] = { 0x41,0x41,0x90,0x90,0x90,0x90,0x90,0x90 };




	unsigned char* pshellcode = shellcode;
	

	PBYTE* ppshellcode = NULL;


	SIZE_T sShellcode = sizeof(shellcode);

	//writeshellcodetoregistry(pshellcode,sShellcode);
	ReadPaylodFromshellcode(sShellcode, pshellcode);


	printf("press <ENTER>  to exit\n");
	getchar();


}


//BOOL ReadPaylodFromshellcode(SIZE_T sShellcode,unsigned char* pshellcode) {
//
//
//	LSTATUS status = NULL;
//
//	DWORD dwbytesread = sShellcode;
//
//	PVOID pbytes = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,sShellcode);
//
//	if (pbytes == NULL) {
//		printf("heap alloc failed with error no %d", GetLastError());
//	}
//
//	status = RegGetValueA(HKEY_CURRENT_USER, REGISTRY, REGSTRING, RRF_RT_ANY, NULL, pbytes, &dwbytesread);
//
//	if (status != ERROR_SUCCESS) {
//		printf("reggetvaluea failed with error %d\n", status);
//	}
//
//
//	//printf("%x",(unsigned char) pbytes);
//
//
//
//
//
//
//
//
//
//}

BOOL ReadPaylodFromshellcode(SIZE_T sShellcode, unsigned char* pshellcode) {
	LSTATUS status;
	DWORD dwbytesread = sShellcode; // Initialize the variable
	PVOID pbytes = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sShellcode);

	if (pbytes == NULL) {
		printf("heap alloc failed with error no %d\n", GetLastError());
		return FALSE;
	}

	status = RegGetValueA(HKEY_CURRENT_USER, REGISTRY, REGSTRING, RRF_RT_ANY, NULL, pbytes, &dwbytesread);

	if (status != ERROR_SUCCESS) {
		printf("reggetvaluea failed with error %d\n", status);
		HeapFree(GetProcessHeap(), 0, pbytes); // Free allocated memory
		return FALSE;
	}

	// Print the read data
	printf("Shellcode read from registry: ");
	for (DWORD i = 0; i < dwbytesread; i++) {
		printf("%02x ", ((unsigned char*)pbytes)[i]); // Cast pbytes to unsigned char* to access bytes
	}
	printf("\n");

	HeapFree(GetProcessHeap(), 0, pbytes); // Free allocated memory
	return TRUE;
}




//BOOL writeshellcodetoregistry(unsigned char* pshellcode,SIZE_T sShellcode) {
//	
//	HKEY hkey = NULL;
//	LSTATUS status = NULL;
//
//	status = RegOpenKeyExA(HKEY_CURRENT_USER, REGISTRY, 0, KEY_SET_VALUE, &hkey);
//	if (status != ERROR_SUCCESS)  {
//		printf("The regopenkeyexa failed withe error %d\n", status);
//	}
//
//	status = RegSetValueExA(HKEY_CURRENT_USER, REGSTRING, 0, REG_BINARY, pshellcode, sShellcode);
//
//
//	if (status != ERROR_SUCCESS) {
//		printf("The regsetvalue throws a error %d\n", status);
//	}
//
//
//	printf("[+]DONE");
//
//	if (hkey) {
//		RegCloseKey(hkey);
//	}
//
//
//}