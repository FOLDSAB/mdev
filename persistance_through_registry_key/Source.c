#include <stdio.h>
#include <Windows.h>

int main() {


	CHAR filename[] = { 0 };


	GetModuleFileNameA(NULL, filename, sizeof(filename));

	printf("%s\n", filename);

	LPSTR subkey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hkey;

	
	DWORD deposition;
	if (RegCreateKeyExA(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &deposition) != ERROR_SUCCESS){
		printf("regcreatekeyexa failed iwth error no %x\n",GetLastError());
	}

	
	if (deposition != REG_OPENED_EXISTING_KEY) {
		printf("error is here");
	}

	LPSTR valuename = "malallaa";
	
	if (RegSetValueExA(hkey, valuename, 0, REG_SZ,filename,  lstrlenA(filename)+1) != ERROR_SUCCESS) {
		printf("Regsetvalueexa failed withe rror no %x\n",GetLastError());
	}


	printf("Press enter to exit\n");
	getchar();








}
