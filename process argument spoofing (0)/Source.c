#include <stdio.h>
#include <Windows.h>

int main() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	LPSTR lpapplication = "notepad";

	if (CreateProcessA(NULL, lpapplication, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi) == 0) {

		printf("createprocess failed with error no %d\n", GetLastError());
		return FALSE;

	}


	/**hthread = pi.hThread;
	*hprocess = pi.hProcess;
	*processid = pi.dwProcessId;*/

	return TRUE;

    
}