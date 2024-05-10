#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <processthreadsapi.h>

int main()
{
	// 5980 is the process id of the runtime broker.exe it might change next time running the proces
	//so make sure you change it to valid one.
	HANDLE hprocess = OpenProcess(MAXIMUM_ALLOWED, FALSE, 5980);
	STARTUPINFOEXA si;

	ZeroMemory(&si, sizeof(STARTUPINFOEXA));


	//si.cb = sizeof(STARTUPINFOEXA);

	PROCESS_INFORMATION pi;


	SIZE_T sizeofattibute = NULL;

	InitializeProcThreadAttributeList(NULL, 1, 0, &sizeofattibute);


	si.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, sizeofattibute);


	if (InitializeProcThreadAttributeList(si.lpAttributeList, 1, 0, &sizeofattibute) == 0) {
		printf("initializeprocthreadattributelist failed with error no %d", GetLastError());
	}

	else {

		if (UpdateProcThreadAttribute(si.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &hprocess, sizeof(HANDLE), NULL, NULL) == 0) {
			printf("updateprocthreaattribute list failed with error no %d", GetLastError());
			si.StartupInfo.cb = sizeof(STARTUPINFOEXA);

	    }
		else {

			CreateProcessA(NULL, (LPSTR)"notepad", NULL, NULL, FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &si.StartupInfo, &pi);
		}



		DeleteProcThreadAttributeList(si.lpAttributeList);
		CloseHandle(hprocess);
	}





	printf("press enter to exit");



}