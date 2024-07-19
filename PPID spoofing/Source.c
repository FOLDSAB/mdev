#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>




int main() {




	STARTUPINFOEXA SI = { 0 };
	PROCESS_INFORMATION PI = { 0 };
	LPPROC_THREAD_ATTRIBUTE_LIST LPThreadAttList = NULL;
	SIZE_T szLPThreadAttList = 0;



	SI.StartupInfo.cb = sizeof(STARTUPINFOEXA);

	InitializeProcThreadAttributeList(NULL, 1, 0, &szLPThreadAttList);


	// A process id of the process
	HANDLE hprocess = OpenProcess(MAXIMUM_ALLOWED, FALSE, 3524);

	if (hprocess == NULL) {
		printf("cannot open openprocess with error no %d\n",GetLastError());
	}


	LPThreadAttList = (LPPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, szLPThreadAttList);


	if (!InitializeProcThreadAttributeList(LPThreadAttList, 1, 0, &szLPThreadAttList)) {
		printf("The InitializeprocthreadAttlist failed with error no %d\n", GetLastError());
	}


	if (!UpdateProcThreadAttribute(LPThreadAttList, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &hprocess, sizeof(hprocess), NULL, NULL)) {
		printf("The UpdateProcThreadAttribute failed with error no %d\n", GetLastError());
	}



	//SI.lpAttributeList = LPThreadAttList;
	
	LPCSTR lppath = "C:\\Windows\\System32\\notepad.exe";
	if (!CreateProcessA(NULL,lppath , NULL, NULL, FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &SI.StartupInfo, &PI)){
		printf("create process failed with error no %d\n", GetLastError());
	}


	DeleteProcThreadAttributeList(LPThreadAttList);
	CloseHandle(PI.hThread);
	CloseHandle(PI.hProcess);

	

	printf("press Enter to exit");
	getchar();




}