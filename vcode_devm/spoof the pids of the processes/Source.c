#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <processthreadsapi.h>

int main() {
    STARTUPINFOEXA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    RtlSecureZeroMemory(&si, sizeof(STARTUPINFOEXA));
    RtlSecureZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    si.StartupInfo.cb = sizeof(STARTUPINFOEXA);

    SIZE_T attibutesize = 0;
    InitializeProcThreadAttributeList(NULL, 1, 0, &attibutesize);

    PPROC_THREAD_ATTRIBUTE_LIST pthreadattx = (PPROC_THREAD_ATTRIBUTE_LIST)(HeapAlloc(GetProcessHeap(), 0, attibutesize));
    if (!pthreadattx) {
        printf("Failed to allocate memory for attribute list\n");
        return 1; 
    }

   
    if (!InitializeProcThreadAttributeList(pthreadattx, 1, 0, &attibutesize)) {
        printf("InitializeProcThreadAttributeList failed with error no %d\n", GetLastError());
        HeapFree(GetProcessHeap(), 0, pthreadattx); 
        return 1;
    }

    HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 24552);
    if (hprocess == NULL) {
        printf("OpenProcess failed with error no %d\n", GetLastError());
        HeapFree(GetProcessHeap(), 0, pthreadattx); 
        return 1; 
    }

    UpdateProcThreadAttribute(pthreadattx, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &hprocess, sizeof(HANDLE), NULL, NULL);

    BOOL success = CreateProcessA(NULL, (LPSTR)"notepad", NULL, NULL, FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &si.StartupInfo, &pi);
    if (!success) {
        printf("CreateProcess failed with error no %d\n", GetLastError());
        CloseHandle(hprocess); 
        HeapFree(GetProcessHeap(), 0, pthreadattx); 
        return 1; 
    }

    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hprocess);
    HeapFree(GetProcessHeap(), 0, pthreadattx);

    return 0;
}
