#include <stdio.h>
#include <windows.h>
#include "Header.h"

#pragma warning(disable : 4996)
#pragma warning(suppress : 4996)


BOOL Createanaccount(pBankAccountCreation customercreation[],pBankAccount customer[],int* account_sn) {
    int i = 0;
    int j = 0;
    int DefaultAcNo = 1000;
    while (customercreation[i] != NULL && i < maximum) {
        i++;
    }

    if (i == maximum) {
        printf("Maximum account creation reached.\n");
        return FALSE;
    }
    customercreation[i] = (pBankAccountCreation)malloc(sizeof(BankAccountCreation));
    customer[i] = (pBankAccount)malloc(sizeof(BankAccountCreation));

    if (customercreation[i] == NULL) {
        printf("The creation failed");
    }
    printf("Welcome to Bank Account Creation\n");
    printf("Please enter your Name: ");

    fgets(customercreation[i]->name, sizeof(customercreation[i]->name), stdin);
    
    printf("%s", customercreation[i]->name);


    printf("Please enter your age: ");
    scanf("%d\n", &customercreation[i]->age);
    printf("The age is %d\n", customercreation[i]->age);

    customer[i]->Accountnumber = (DefaultAcNo);
    customer[i]->Balance = 100;

    *account_sn = i;

    return TRUE;
}


