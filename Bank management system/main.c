#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Header.h"
#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)

/* Bank Management System: Build a simple bank management system where users can create accounts, deposit money, withdraw money, check balance, and perform other banking operations */



BOOL Createanaccount(pBankAccountCreation customercreation[],pBankAccount customer[],int* account_sn);

int main() {
	pBankAccountCreation customercreation[maximum] = { 0 };
	pBankAccount customer[maximum] = { 0 };

	printf("Welcome to BANK\n");


	char* abcd = (char*)malloc(100);

	if (abcd == NULL) {
		printf("The abcd failed with error no %d\n", GetLastError());
		return -1;
	}


	printf("printf what do you want to do\n");

	
	fgets(abcd, 100, stdin);
	SIZE_T len = strlen(abcd);

	abcd[len - 1] = '\0';
	int account_SN = 0;



		if (strcmp(abcd, "create") == 0) {

			if (Createanaccount((pBankAccountCreation)customercreation, customer,&account_SN)) {
				printf("[+] Your account has been created sucessfully\n");
				printf("\t\t NAME: %s\n", customercreation[account_SN]->name);
				printf("\t\t Age: %d\n", customercreation[account_SN]->age);
				printf("\t\t AccountNumber: %d\n", customer[account_SN]->Accountnumber);
				printf("\t\t Balance: %d\n",customer[account_SN]->Balance);
			}

		}





	printf("press enter to exit");
	getchar();


}