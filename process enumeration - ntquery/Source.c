#include <stdio.h>
#include <Windows.h>
#include <winternl.h>


int main() {


	typedef NTSTATUS(NTAPI* fnNtQuerySystemInformation) (

		SYSTEM_INFORMATION_CLASS SystemInformationClass,
		PVOID                    SystemInformation,
		ULONG                    SystemInformationLength,
		PULONG                   ReturnLength

		);


	ULONG returnvalue = NULL,
		returnvalue2 = NULL;
	PSYSTEM_PROCESS_INFORMATION systemprocinfo = NULL;
	PVOID pvaluetofree = NULL;
	fnNtQuerySystemInformation	pNtQuerySystemInformation = NULL;
	NTSTATUS status = NULL;
	LPCWSTR szProcname = L"svchost.exe";




	
	 pNtQuerySystemInformation = (fnNtQuerySystemInformation) GetProcAddress(GetModuleHandle(L"NTDLL.DLL"), "NtQuerySystemInformation");


	 if (pNtQuerySystemInformation == NULL) {
		 printf("The process address of ntquerysysteminformation cannot be found ");
		 

	 }

	 else {
		 printf("ntquerysysteminformation runned sucessfully\n");

		 pNtQuerySystemInformation(SystemProcessInformation, NULL, NULL, &returnvalue);

		 systemprocinfo = (PSYSTEM_PROCESS_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (SIZE_T)returnvalue);


		 if (systemprocinfo == NULL) {
			 printf("[!] heap alloc failed with error no %d", GetLastError());
		 }


		 pvaluetofree = (PVOID)systemprocinfo;


		 
		 status = pNtQuerySystemInformation(SystemProcessInformation, systemprocinfo, returnvalue, &returnvalue2);

		 if (status != 0x0) {
			 printf("the ntquery system information failed with error no %x", status);
		 }

		 while (TRUE)
		 {


			 if (systemprocinfo->ImageName.Length && wcscmp(systemprocinfo->ImageName.Buffer,szProcname)==0) {

				 printf("%ls ----  %ld\n", systemprocinfo->ImageName.Buffer,systemprocinfo->UniqueProcessId);

			 }

			 systemprocinfo = (PSYSTEM_PROCESS_INFORMATION)((ULONG_PTR) systemprocinfo+systemprocinfo->NextEntryOffset);

		 }
	 
	 
	 }


	 printf("press <enter> to exit\n");
	 getchar();









	
}