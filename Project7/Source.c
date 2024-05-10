#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main() {




	STARTUPINFOEXA si = { 0 };
	PPROC_THREAD_ATTRIBUTE_LIST pithreadatx = NULL;
	SIZE_T attlist = 0;
	PROCESS_INFORMATION pi = { 0 };


	InitializeProcThreadAttributeList(NULL, 1, NULL, &attlist);

	pithreadatx = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, attlist);

	if (!InitializeProcThreadAttributeList(pithreadatx, 1, 0, &attlist)) {
		printf("initalize proc thread attlist failed with error no %d\n", GetLastError());
	}
	else {
		si.StartupInfo.cb = sizeof(STARTUPINFOEXA);

		HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 948);
		if (!UpdateProcThreadAttribute(pithreadatx, NULL, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &hprocess, sizeof(HANDLE), NULL, NULL)) {
			printf("update proc thread attlist failed with error no %d\n", GetLastError());
	}

		else {

			CreateProcessA(NULL, (LPSTR)"Notepad", NULL, NULL, FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &si.StartupInfo, &pi);
			
		}
		

	}








	printf("press enter to exit");
	getchar();





}