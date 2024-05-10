#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <winternl.h>



BOOL createargedspoofedprocess();

typedef NTSTATUS(NTAPI* fnNtQueryInformationProcess)(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength );


int main() {




    createargedspoofedprocess();

    printf("press enter to exit\n");
    getchar();

}



BOOL createargedspoofedprocess() {

    STARTUPINFOW si = { 0 };
    RtlSecureZeroMemory(&si, sizeof(STARTUPINFOW));
    PROCESS_INFORMATION pi = { 0 };
    RtlSecureZeroMemory(&pi, 0);

    PROCESS_BASIC_INFORMATION PBI = { 0 };
    ULONG retlen = NULL;


    fnNtQueryInformationProcess pNtQueryInformationProcess = (fnNtQueryInformationProcess)GetProcAddress(GetModuleHandleW(L"ntdll"), "NtQueryInformationProcess");
    if (pNtQueryInformationProcess == NULL) {
        printf("The ntqueryinformation process failed with error no %d\n", GetLastError());
        return FALSE;
    }
    LPWSTR lpapplicationname = L"C:\\Windows\\System32\\cmd.exe";
    LPWSTR cmdlineargs = L"                                        ";

    if (!CreateProcessW(lpapplicationname, cmdlineargs, NULL, NULL, FALSE, CREATE_SUSPENDED|CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        printf("create process failed with error no %d\n", GetLastError());
        return FALSE;
    }


    NTSTATUS status = pNtQueryInformationProcess(pi.hProcess, ProcessBasicInformation, &PBI, sizeof(PROCESS_BASIC_INFORMATION), &retlen);

    if (status != 0) {
        printf("The pntqueryinformatinprocess failed withe error no %d", status);
        return FALSE;
    }


    if(!ReadFromTargetProcess)






  



    

}
