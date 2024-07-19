// Data Structure: Define a structure to represent a contact, containing fields such as name, phone number, email, etc.

// Functionality:

// Add Contact: Implement a function to add a new contact to the address book.
// Delete Contact: Implement a function to delete a contact from the address book.
// Search Contact: Implement a function to search for a contact by name or phone number.
// List All Contacts: Implement a function to display all contacts in the address book.
// Update Contact: Implement a function to update the information of an existing contact.
// File I/O: Implement functions to read contacts from a file when the program starts and write contacts to a file when the program exits. This allows the address book to persist across different program executions.

// User Interface: Create a simple command-line interface that allows users to interact with the address book. Provide options for adding, deleting, searching, listing, and updating contacts.

// Error Handling: Implement error handling to deal with cases such as invalid input, file read/write errors, etc.

// Menu System: Design a menu system that presents users with options and allows them to navigate through different functionalities of the address book.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <fileapi.h>

typedef struct _address_book
{
    char name[40];
    unsigned long long int number;
    char email[50];
} address_book, *Paddress_book;

int AddContact(address_book *NewContact, FILE *Book, FILE *NoContactFile);
int ListAllContacts(address_book contacts,FILE *Book);
int UpdateContact(address_book contacts, FILE *Book,FILE *NoContactFile);

int main()
{

    int choice;
    address_book contacts;

    printf("What do you want to do\n1. Add Contact\n2. Delete Contact\n3. List All Contacts\n4. Update Contact\n");
    printf("\nyour choice: ");
    scanf("%d", &choice);

    FILE *Book;
    Book = fopen("address_book.txt", "a+");
    if (Book == NULL)
    {
        printf("cannot open file");
    }

    FILE *NoContactFile;
    NoContactFile = fopen("address_book_nocontacts.txt", "r+");
    if (NoContactFile == NULL)
    {
        printf("cannot open file");
    }

    if (choice == 1)
    {
        AddContact(&contacts, Book, NoContactFile);
    }
    else if (choice == 2)


    {
    }
    else if (choice == 3)
    {

        ListAllContacts(contacts,Book);
    }
    else if (choice == 4)
    {

        UpdateContact(contacts,Book,NoContactFile);
    }
    else
    {
        printf("please Enter valid input\n");
    }

        fclose(Book);
        fclose(NoContactFile);
}

int AddContact(address_book *NewContact, FILE *Book, FILE *NoContactFile)

{

    int noofcontacts;
    if (fscanf(NoContactFile, "%d", &noofcontacts) == 1)
    {
        printf("Please Enter the Name: ");
        scanf(" %s", NewContact->name);
        printf("please Enter the number: ");
        scanf(" %llu", &NewContact->number);
        printf("Please Enter the email");
        scanf(" %s", NewContact->email);
        fprintf(Book, "%s %llu %s\n", NewContact->name, NewContact->number, NewContact->email);
        noofcontacts++;
        fseek(NoContactFile, 0, SEEK_SET);
        fprintf(NoContactFile, "%d", noofcontacts);

        printf("\n****************************************\n");
        printf("Added a new contact");
                printf("NAME: %s\n", NewContact->name);
        printf("NUMBER: %d\n", NewContact->number);
        printf("EMAIL: %s\n", NewContact->email);


    }

    else{
        printf("Cannot read from file");
        return 1;
    }
    return 0;
}


int ListAllContacts(address_book contacts,FILE *Book){

fseek(Book,0,SEEK_SET);

while (fscanf(Book, "%30s %d %50s", contacts.name, &contacts.number, contacts.email) == 3) {
        printf("*************************************************\n");
        printf("NAME: %s\n", contacts.name);
        printf("NUMBER: %d\n", contacts.number);
        printf("EMAIL: %s\n", contacts.email);
    }

}


int UpdateContact(address_book contacts, FILE *Book,FILE *NoContactFile){
    char *PsContact_name = (char *)malloc(sizeof(char));
    int noofcontacts;
    printf("What contact Would you like to update Please Enter the name: ");
    scanf(" %s",PsContact_name);

    fscanf(NoContactFile," %d",&noofcontacts);
    // fseek(Book,0,SEEK_SET);

    for (int i = 0 ; i < noofcontacts;i++)
    {

      if  (fscanf(Book,"%30s %d %s",contacts.name,&contacts.number,contacts.email)==3){
        printf("%s %d %s",contacts.name,contacts.number,contacts.email);
        if(strcmp(PsContact_name,contacts.name)==0){
            
            printf("%s %d %s",contacts.name,contacts.number,contacts.email);
            printf("please Enter the update number");
            scanf("%s",&contacts.number);
            // rewind(Book);
            // rewind(Book);
            fprintf(Book,"%s %d %s",contacts.name,contacts.number,contacts.email);
            return 1;
        }

        else{
            printf("cannot find your contact");
            continue;
            
        }

      }



    }
    return 1;

    

}