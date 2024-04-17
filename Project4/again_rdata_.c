#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "resource.h"


int main() {

	HRSRC hRsrc = NULL;
	HGLOBAL hGlobal = NULL;
	PVOID pPayloadAddress = NULL;
	SIZE_T sPayloadSize = NULL;


	hRsrc = FindResourceW(NULL, MAKEINTRESOURCEW(IDR_RCDATA1), RT_RCDATA);
	hGlobal = LoadResource(NULL, hRsrc);
	pPayloadAddress = LockResource(hGlobal);
	sPayloadSize = SizeofResource(NULL, hRsrc);

	PVOID pTempBuffer= HeapAlloc(GetProcessHeap(), 0, sPayloadSize);
	if (pTempBuffer != NULL) {
		memcpy(pTempBuffer, pPayloadAddress, sPayloadSize);
	}

	printf("The actual location of the payload is %p\n", pPayloadAddress);
	printf("the location of the ponter is ponting to is %p\n", pTempBuffer);
	printf("press <enter> to exit ....");
	getchar();



}