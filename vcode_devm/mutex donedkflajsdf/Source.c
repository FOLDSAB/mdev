#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


int main() {


	STARTUPINFOA si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	if (CreateProcessA(NULL, (LPSTR)"Notepad", NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, "C:\\", &si, &pi) == 0) {

		printf("create processa failed withe rror no %d\n", GetLastError());


		
}



	getchar();

}