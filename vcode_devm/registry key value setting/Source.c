#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <winreg.h>
#include <string.h>
#define REGISTRY "Control Panel"


int main() {
	LSTATUS status = NULL;
	LPSTR data = "what is this";
	DWORD szdata =(DWORD)strlen(data);
	LPSTR returneddata = NULL;



	/*status = RegSetValueA(HKEY_CURRENT_USER, REGISTRY, REG_SZ, data, szdata);

	if (status != ERROR_SUCCESS) {
		printf("the regsetvalue failed with error no %d", GetLastError());
	}*/

	

		//returneddata = (LPSTR)malloc(szdata);

		status = RegGetValueA(HKEY_CURRENT_USER, REGISTRY, "", RRF_RT_ANY, NULL, (PVOID)returneddata, NULL);
	
			if (status != ERROR_SUCCESS) {
				printf("The reggetvaluea failed with error no %d", status);
				}
			else {
				printf(" The registry data is %ls", returneddata);

			}

			RegCloseKey(HKEY_CURRENT_USER);
	
	
	
	printf("press enter to exit");
	getchar();
}


