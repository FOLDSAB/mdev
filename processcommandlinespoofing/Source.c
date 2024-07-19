#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <winternl.h>


typedef NTSTATUS(*fnNtQueryInformationProcess)(
	HANDLE           ProcessHandle,
	PROCESSINFOCLASS ProcessInformationClass,
	PVOID            ProcessInformation,
	ULONG            ProcessInformationLength,
	PULONG           ReturnLength
	);



BOOL ReadMemoryFromTarget(HANDLE hprocess,LPVOID pBaseaddress,LPVOID *ppBuffer,DWORD dwBuffersize ) {

	SIZE_T numberofbytes = NULL;
	*ppBuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwBuffersize);
	if(!ReadProcessMemory(hprocess, pBaseaddress, *ppBuffer, dwBuffersize, &numberofbytes) || numberofbytes != dwBuffersize){
		printf("Read process memroy failed with error no %d\n", GetLastError());
		return FALSE;
	}

	return TRUE;
}


//BOOL WriteToTargetMemrory(HANDLE hprocess, LPVOID pBaseAddress,)
BOOL WriteMemoryFromTarget(HANDLE hprocess, LPVOID pBaseaddress, LPVOID ppBuffer, DWORD dwBuffersize) {
	SIZE_T numberofbytes = NULL;
	//*ppBuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwBuffersize);
		if (!WriteProcessMemory(hprocess, pBaseaddress, ppBuffer, dwBuffersize, &numberofbytes) || numberofbytes != dwBuffersize) {
		//printf("Read process memroy failed with error no %d\n", GetLastError());
		return FALSE;
	}

	return TRUE;
}



int main() {

	STARTUPINFOW SI = { 0 };
	PROCESS_INFORMATION PI = { 0 };
	NTSTATUS status = NULL;

	WCHAR   Wprocname[MAX_PATH] = L"powershell.exe -c dir";
	PROCESS_BASIC_INFORMATION PBI = { 0 };
	ULONG	Returnlength = NULL;
	PPEB    Ppeb = NULL;
	PRTL_USER_PROCESS_PARAMETERS  PParams = NULL;
	SI.cb = (sizeof(SI));
	PUNICODE_STRING processtring = NULL;



	if (!CreateProcessW(NULL, Wprocname, NULL, NULL, FALSE, CREATE_SUSPENDED|CREATE_NO_WINDOW, NULL, NULL, &SI, &PI)) {
		printf("Createprocess failed with error no %d\n", GetLastError());
	}


	fnNtQueryInformationProcess NTProcessInformation = (fnNtQueryInformationProcess)GetProcAddress(GetModuleHandleW(L"Ntdll.dll"), "NtQueryInformationProcess");

	if (NTProcessInformation == NULL) {
		printf("Getprocaddress failed with error no %d\n", GetLastError());
	}



	//NTProcessInformation(PI.hProcess,)

	if (!NTProcessInformation(PI.hProcess, ProcessBasicInformation, &PBI, sizeof(PROCESS_BASIC_INFORMATION),&Returnlength)) {
		printf("The ntqueryinformation process failed with error no %x\n", GetLastError());
	}
		
	if (&PBI == NULL) {
		printf("ok PBI failed with error no \n");
	}


	if (!ReadMemoryFromTarget(PI.hProcess, PBI.PebBaseAddress, &Ppeb, sizeof(PEB))) {
		printf("Read process memory 1st failed with error no %x\n", GetLastError());
	}

	if (!ReadMemoryFromTarget(PI.hProcess, Ppeb->ProcessParameters, &PParams, (sizeof(RTL_USER_PROCESS_PARAMETERS)+0xFF)) ){
		printf("Read process memory 2st failed with error no %x\n", GetLastError());

	}
	
	LPWSTR Realargs = L"This is what it is";
	if (!WriteMemoryFromTarget(PI.hProcess, (PVOID)PParams->CommandLine.Buffer, Realargs, lstrlenW(Realargs) * sizeof(WCHAR) + 1)) {
		printf("The write process memory failed withe rror no %d\n\n", GetLastError());
	}








	printf("press <enter> to exit: ");
	getchar();
}