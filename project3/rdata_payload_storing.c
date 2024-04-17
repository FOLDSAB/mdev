#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "resource.h"
#pragma warning(suppress : 6387)

int main() {

	HRSRC  hRsrc = NULL;
	HGLOBAL hGLobal = NULL;
	PVOID pPayloadAddress = NULL;
	SIZE_T sPayloadsize = NULL;
	LPCWSTR ResourceID = MAKEINTRESOURCEW(IDR_RCDATA1);


	hRsrc = FindResourceW(NULL,ResourceID, RT_RCDATA);

	if (hRsrc == NULL) {
		printf("[-] Handle to the resource failed due to %d\n", GetLastError());
	}

	hGLobal = LoadResource(NULL,hRsrc);

	if (hGLobal == NULL) {
		printf("[-] Loadresource failed with errorno: %d\n", GetLastError());
	}

	pPayloadAddress = LockResource(hGLobal);

	if (pPayloadAddress == NULL) {
		printf("[-] LockResource failed with error: %d\n", GetLastError());
	}

	sPayloadsize = SizeofResource(NULL, hRsrc);

	if (sPayloadsize == NULL) {
		printf("[-] sizeofresource failed with error %d\n", GetLastError());
	}


	printf("[i] payloadaddress var: 0x%p\n", pPayloadAddress);
	printf("[i] payloadsize: %ld\n", sPayloadsize);

	PVOID pTempBuffer = HeapAlloc(GetProcessHeap(), 0, sPayloadsize);


	if (pTempBuffer != NULL) {
		memcpy(pTempBuffer, pPayloadAddress, sPayloadsize);
	}

	printf("The value of pTempBuffer is 0x%p\n", pTempBuffer);


	getchar();

	
}