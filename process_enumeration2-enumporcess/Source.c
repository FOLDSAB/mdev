#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <psapi.h>

int main() {


	DWORD dwapids[1024 * 2],
		noofbytesreturn1 = NULL,
		noofbytesreturn2 = NULL,
		dwnoofpids = NULL;
	HANDLE hprocess = NULL;
	HMODULE hmodule[1024];
	WCHAR psfilename[MAX_PATH];




	if (EnumProcesses(dwapids, sizeof(dwapids), &noofbytesreturn1) == 0) {

		printf("enumporcess failed with error no %d", GetLastError());
		return -1;
	}
	else {

		dwnoofpids = noofbytesreturn1 / sizeof(DWORD);

		printf("the number of pids is: %ld\n", dwnoofpids);



		for (int i = 0; i < dwnoofpids; i++) {

			if (dwapids[i] != 0) {
				//printf("the process id is %ld\n", dwapids[i]);
				hprocess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, dwapids[i]);


			
				if (hprocess == NULL) {
					//printf("hprocess failed with error no %d\n", GetLastError());
					continue;

				}

				else {

					if (EnumProcessModules(hprocess, hmodule, sizeof(hmodule), &noofbytesreturn2) == 0) {
						printf("the enumporcessmodules handles failed with error no %d\n", GetLastError());
					}

					else {

						for (int j = 0; j < noofbytesreturn2 / sizeof(HMODULE);j++) {

							if (GetModuleBaseName(hprocess, hmodule[j], psfilename, sizeof(psfilename)) == 0) {

								//printf("getmodulebasename failed with error no %d\n", GetLastError());
								CloseHandle(hprocess);
								continue;
							}

							else {
								//printf("Process id is %ld ---- process name is %ls \n", dwapids[i],psfilename);
								printf("%ld ---- %ls \n", dwapids[i], psfilename);

								CloseHandle(hprocess);
								
								break;
								
							}
							



						}
					}


				}
			}

		}

	}









	printf("press enter to exit");
	getchar();
}