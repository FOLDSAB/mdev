#pragma once
#define maximum 100


typedef struct _BankAccountCreation {
	char name[100];
	int age;
} BankAccountCreation, * pBankAccountCreation;

typedef struct _BankAccount {

	long int Balance;
	long int Accountnumber;
	pBankAccountCreation customer[maximum];


}BankAccount, * pBankAccount;