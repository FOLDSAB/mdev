#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <winternl.h>

typedef NTSTATUS (*fnNtQueryInformationProcess)(
	HANDLE           ProcessHandle,
	PROCESSINFOCLASS ProcessInformationClass,
	PVOID            ProcessInformation,
	ULONG            ProcessInformationLength,
	PULONG           ReturnLength
);



BOOL ParentPIDSpoofing( LPWSTR newprocessname, HANDLE* hnewprocess, DWORD *dwnewPID) {

	STARTUPINFOEXW SI = { 0 };
	PROCESS_INFORMATION PI = { 0 };
	SI.StartupInfo.cb = sizeof(STARTUPINFOW);
	SIZE_T Attributelist = 0;
	HANDLE hprocess = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(HANDLE));

	 OpenAprocess(49820,&hprocess);

	SI.StartupInfo.cb = sizeof(STARTUPINFOEXW);

	InitializeProcThreadAttributeList(NULL, 1, 0, &Attributelist);

	SI.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Attributelist);

	if (SI.lpAttributeList == NULL) {
		printf("Heap alloc failed with error no %x\n", GetLastError());
		return FALSE;
	}


	if (!InitializeProcThreadAttributeList(SI.lpAttributeList, 1, 0, &Attributelist)) {
		printf("InitializeProcThreadAttirbuteList failed with error no %x\n", GetLastError());
		return FALSE;
	}

	if (!UpdateProcThreadAttribute(SI.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &hprocess, sizeof(hprocess), NULL, NULL)) {

		printf("UpdateProcThreadAttirbute failed with error no %x\n", GetLastError());
		return FALSE;
	}

	if (!CreateProcessW(NULL, newprocessname, NULL, NULL, FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &SI.StartupInfo, &PI)) {
		printf("The CreateprocessW failed with error no %x\n", GetLastError());
		return FALSE;
	}
	printf("\n[+] creating a spoofed process.....\n");
	printf("[+] process created Notepad.exe with processid %d and parent process id 42628\n", PI.dwProcessId);


	*hnewprocess = PI.hProcess;
	*dwnewPID = PI.dwProcessId;
	return TRUE;



}

BOOL OpenAprocess(DWORD ProcessID,HANDLE *hprocess);
BOOL ParentProcessIDSpoofing(HANDLE hprocess, SIZE_T Attributelist, PROCESS_INFORMATION PI, STARTUPINFOEXW SI, WCHAR* commandline, HANDLE* PIhprocess,DWORD *processID);
BOOL CommandLineSpoofing(HANDLE hprocess,PROCESS_BASIC_INFORMATION PBI,PPEB pPeb,PRTL_USER_PROCESS_PARAMETERS pprocessparams);
BOOL ReadMemoryFromRemoteProcess(HANDLE hprocess, LPVOID lpbaseaddress, LPVOID *lpbuffer, SIZE_T szsize);
BOOL WriteMemoryToRemoteProcess(HANDLE hprocess, LPVOID lpbaseaddress, LPVOID lpbuffer,SIZE_T szsize);

int main() {


	SIZE_T Attributelist = 0;

	WCHAR commandline[MAX_PATH] = L"notepad";
	STARTUPINFOEXW SI = { 0 };
	PROCESS_INFORMATION PI = { 0 };
	DWORD processID;
	PROCESS_BASIC_INFORMATION PBI = { 0 };
	PPEB pPeb = NULL;
	PRTL_USER_PROCESS_PARAMETERS processparams = NULL;
	DWORD createprocessProcessID;



	HANDLE hprocess = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(HANDLE));


	//if (!OpenAprocess(29672, &hprocess)) {
	//	//printf("Open A process cannot be done");
	//	goto end;
	//}
	//if (!ParentProcessIDSpoofing(hprocess, Attributelist, PI, SI, commandline, &PI.hProcess,&createprocessProcessID)) {
	//	goto end;
	//}


	//if (!CommandLineSpoofing(PI.hProcess, PBI, pPeb, processparams)) {
	//	goto end;
	//}

	if (!ParentPIDSpoofing(commandline, &hprocess, &processID)) {
		goto end;
}


	




end:	
	CloseHandle(hprocess);
	printf("press <enter> to exit");
	getchar();



}


BOOL WriteMemoryToRemoteProcess(HANDLE hprocess, LPVOID lpbaseaddress, LPVOID lpbuffer,SIZE_T szsize) {


	SIZE_T lpNumberOfBytesWritten = 0;




	if (!WriteProcessMemory(hprocess, lpbaseaddress, lpbuffer, szsize, &lpNumberOfBytesWritten) || szsize != lpNumberOfBytesWritten) {
		printf("write process memory failed with error no %x\n", GetLastError());
	
		return FALSE;
	}


}


BOOL ReadMemoryFromRemoteProcess(HANDLE hprocess, LPVOID lpbaseaddress, LPVOID *lpbuffer, SIZE_T szsize) {
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

BOOL CommandLineSpoofing(HANDLE hprocess, PROCESS_BASIC_INFORMATION PBI, PPEB pPeb, PRTL_USER_PROCESS_PARAMETERS pprocessparams) {


	NTSTATUS status;
	
	
fnNtQueryInformationProcess NTinformationprocess = 	GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationProcess");


if (NTinformationprocess == NULL) {

	printf("GetprocAddress or GetmoduleHandleW failed with error no %x\n", GetLastError());
	return FALSE;

}

ULONG returnlength; 

status = NTinformationprocess(hprocess, ProcessBasicInformation, &PBI, sizeof(PBI), &returnlength);



if (status != 0) {

	printf("ntinformation process failed with error no %x\n", GetLastError());

}


if (!ReadMemoryFromRemoteProcess(hprocess, PBI.PebBaseAddress, &pPeb, sizeof(PEB))) {
	return FALSE;
}


if(!ReadMemoryFromRemoteProcess(hprocess,pPeb->ProcessParameters,&pprocessparams,sizeof(RTL_USER_PROCESS_PARAMETERS)+0xFF)){
	HeapFree(GetProcessHeap(), 0, pprocessparams);
	return FALSE;
}
printf("The PEB address is %p\n", PBI.PebBaseAddress);


wprintf("This is the command line %s", pprocessparams->CommandLine.Buffer);
WCHAR updatecommandline[] = L"This is the updated commandline";

if (!WriteMemoryToRemoteProcess(hprocess, pprocessparams->CommandLine.Buffer, updatecommandline, sizeof(updatecommandline)) ){
	return FALSE;
}

//Sleep(10000);
//
//if (ResumeThread(hprocess) == -1) {
//	printf("resumethread failed with error no %x\n", GetLastError());
//}

return TRUE;







}
BOOL OpenAprocess(DWORD ProcessID,HANDLE *hprocess) {




	*hprocess =	OpenProcess(PROCESS_CREATE_PROCESS, FALSE, ProcessID);


	if (NULL == *hprocess) {

		printf("cannot open process with error no %x\n", GetLastError());
		CloseHandle(*hprocess);
		return FALSE;
	}

	return TRUE;


	

}
BOOL ParentProcessIDSpoofing(HANDLE hprocess, SIZE_T Attributelist, PROCESS_INFORMATION PI, STARTUPINFOEXW SI, WCHAR* commandline, HANDLE *PIhprocess,DWORD *processID) {


	SI.StartupInfo.cb = sizeof(STARTUPINFOEXW);

	InitializeProcThreadAttributeList(NULL, 1, 0, &Attributelist);

	SI.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Attributelist);

	if (SI.lpAttributeList == NULL) {
		printf("Heap alloc failed with error no %x\n", GetLastError());
		goto end;
	}

	if (!InitializeProcThreadAttributeList(SI.lpAttributeList, 1, 0, &Attributelist)) {
		printf("InitializeProcThreadAttirbuteList failed with error no %x\n", GetLastError());
		goto end;
	}

	if (!UpdateProcThreadAttribute(SI.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &hprocess, sizeof(hprocess), NULL, NULL)) {

		printf("UpdateProcThreadAttirbute failed with error no %x\n", GetLastError());
		goto end;
	}

	if (!CreateProcessW(NULL, commandline, NULL, NULL, FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &SI.StartupInfo, &PI)) {
		printf("The CreateprocessW failed with error no %x\n", GetLastError());
		goto end;
	}


	*PIhprocess = PI.hProcess;
	*processID = PI.dwProcessId;
	return TRUE;





end:
	return FALSE;


}