#include <stdio.h>
#include <Windows.h>
#include "resource.h"

int main() {
	//HMODULE mod = GetModuleHandleA("user32.dll");
	
	HRSRC hRsrc = NULL;
	HGLOBAL hGlobal = NULL;
	PVOID pPayloadAddress = NULL;
	SIZE_T sPayloadSize = NULL;
	// PWSTR pResourceId = MAKEINTRESOURCEW(IDR_RCDATA1);

	hRsrc = FindResourceW(NULL, MAKEINTRESOURCEW(IDR_RCDATA1), RT_RCDATA);


	if (hRsrc == NULL) {
		printf("the find resource failed with error: %d\n", GetLastError());
	}
	
	hGlobal = LoadResource(NULL, hRsrc);

	if (hGlobal == NULL) {
		printf("The load resource failed with error: %d\n", GetLastError());
	}

	pPayloadAddress = LockResource(hGlobal);

	if (hGlobal == NULL) {
		printf("The locking of the resource has sent a error: %d\n", GetLastError());
	}

	sPayloadSize = SizeofResource(NULL, hRsrc);

	if (sPayloadSize == NULL) {
		printf("The payload size cannot be fetched due to error: %d\n",GetLastError());
	}

	PVOID TempResourcePointer = HeapAlloc(GetProcessHeap(), 0, sPayloadSize);

	if (TempResourcePointer != NULL) {
		memcpy(TempResourcePointer, pPayloadAddress, sPayloadSize);


	}
	
	printf("The address of the payload lies in 0x%p\n",pPayloadAddress);
	printf("The pointer to the payload address is 0x%p\n", TempResourcePointer);
	printf("The size of resource is %zu\n", sPayloadSize);
	printf("Press <enter> to exit");
	getchar();
}