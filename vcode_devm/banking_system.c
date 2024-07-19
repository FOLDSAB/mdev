#include <stdio.h>
#include <stdlib.h>

typedef struct _account_creation
{

    int age;
    char name[30];
    int balance;
    int account_number;

} account_creation;



void delete_account(account_creation customer[]);
int exist_checker(account_creation customer[],int acno);
    
int AddBalance(account_creation customer[]);

void Create_account(account_creation customer[] );


int main()
{

    account_creation customer[100];

    for (int i = 0; i < 100; i++)
    {
        customer[i].age= 0;
        customer[i].name[0] = '\0';
        customer[i].balance = 0;
        customer[i].account_number = 0;    }
    
    int choice;

    printf("Welcome to Bank Management System\n");

    while (1)

    {

printf("\n\n********************************************************\n\n");
        printf("What do you want to do\n1. Create an Account\n2. Add Balance to Account\n3. Delete an Account\n");
        scanf(" %d", &choice);

        if (choice == 1)
        {
            Create_account(customer);
        }
        else if(choice == 2){
          if ( AddBalance(customer) == 1){
            printf("Account doesn't exist");
          }
        }

        else if(choice==3){

            // int accno;
            // printf()
            delete_account(customer);
        }

        else
        {
            printf("Please Enter a valid entry\n");
        }
    }

}


int exist_checker(account_creation customer[],int acno){



if(customer[acno].age == 0){

    return 1;
}
}

int AddBalance(account_creation customer[]){
    int account_number;
    int amount;
    printf("Please Enter your account number: ");
    scanf(" %d",&account_number);
   if( exist_checker(customer,account_number) ==1){
    return 1;
   }
   else{
    printf("Please Enter the amount to add: ");
    scanf(" %d",&amount);

    customer[account_number].balance += amount;
   }

printf("\n\n**************************************************\n\n");
    printf("Your balance has been updated by %d\nYour new balance is %d\n",amount,customer[account_number].balance);

}


void Create_account(account_creation customer[] )

{

    static int account_count = 0;
    customer[account_count].account_number = account_count;
    customer[account_count].balance = 100;
    printf("please Enter your name: ");
    scanf(" %s", customer[account_count].name);
    printf("please Enter your age: ");
    scanf(" %d", &customer[account_count].age);

    printf("\n\n******************************************************\n\n");
        printf("your account has been created\n");
    printf("Name: %s\n", customer[account_count].name);
    printf("Age: %d\n", customer[account_count].age);
    printf("Balance: %d (Default)\n", customer[account_count].balance);
    printf("Account Number: %d\n-", customer[account_count].account_number);
    account_count++;

}

void delete_account(account_creation customer[]){
    int accno;

    printf("please enter your account number: ");
    scanf("%d",&accno);
    customer[accno].age = 0;
    customer[accno].account_number = 0;
    customer[accno].balance = 0;
    customer[accno].name[0] = '\0';
    }