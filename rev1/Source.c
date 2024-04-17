#include <stdio.h>
#include <Windows.h>
#include "resource.h"

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




	printf("press <enter> to exit");
	getchar();



}