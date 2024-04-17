#include <stdio.h>
#include <windows.h>

int main() {

	HANDLE hfile = INVALID_HANDLE_VALUE;

	LPCWSTR filepath = L"C:\\Users\\ACER\\Desktop\\devm\\Project1";
	
	hfile = CreateFileW(filepath, GENERIC_ALL, 0, NULL, CREATE_NEW, 0, NULL);

	if (INVALID_HANDLE_VALUE != hfile) {
		printf("[-] The handle for the file is not sucess full with error value %d\n",GetLastError());
	}
}