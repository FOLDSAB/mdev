#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Psapi.h>

BOOL printprocess();

int main() {
    printprocess();
    printf("press <enter> to exit");
    getchar();
    return 0;
}

BOOL printprocess() {
    DWORD adwprocess[1024 * 2];
    DWORD dwreturnlen1 = 0;
    DWORD dwreturnlen2 = 0;
    DWORD dwnoofpids = 0;

    HANDLE hprocess = NULL;
    HMODULE hmodule[100];
    WCHAR szproc[MAX_PATH];

    if (!EnumProcesses(adwprocess, sizeof(adwprocess), &dwreturnlen1)) {
        printf("EnumProcesses failed with error no %d\n", GetLastError());
        return FALSE;
    }

    dwnoofpids = dwreturnlen1 / sizeof(DWORD);
    printf("The number of PIDs is %ld\n", dwnoofpids);

    for (int i = 0; i < dwnoofpids; i++) {
        if (adwprocess[i] != 0) {
            printf("Process ID: %ld\n", adwprocess[i]);
            hprocess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, adwprocess[i]);
            if (hprocess != NULL) {
                printf("Successfully opened process\n");
                if (EnumProcessModules(hprocess, hmodule, sizeof(hmodule), &dwreturnlen2)) {
                    for (DWORD j = 0; j < dwreturnlen2 / sizeof(HMODULE); j++) {
                        if (GetModuleBaseName(hprocess, hmodule[j], szproc, MAX_PATH)) {
                            printf("Process name: %ls\n", szproc);
                        }
                        else {
                            printf("Failed to get process name for PID %ld\n", adwprocess[i]);
                        }
                        break;
                    }
                }
                else {
                    printf("EnumProcessModules failed at PID %ld with error no %d\n", adwprocess[i], GetLastError());
                }
                CloseHandle(hprocess);
            }
            else {
                printf("Failed to open process with PID %ld\n", adwprocess[i]);
            }
        }
    }
    return TRUE;
}
