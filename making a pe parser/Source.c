#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Header.h"


BOOL PEcheckerDOSHEADER(mIMAGE_DOS_HEADER Temp_dos_header, FILE* hfile,int* fseekholder);
BOOL PEcheckerNTHEADER(FILE* hfile, mIMAGE_DOS_HEADER Temp_dos_header, mIMAGE_NT_HEADERS64 temp_NT_header64,int* fseekholder);
BOOL PEcheckerSECTIONS(FILE* hfile, int fseekholder, mIMAGE_SECTION_HEADER Temp_section_header, mIMAGE_NT_HEADERS64 temp_NT_header64);


int main() {


    mIMAGE_DOS_HEADER Temp_dos_header = { 0 };
    mIMAGE_NT_HEADERS32 Temp_nt_header32 = { 0 };
    mIMAGE_NT_HEADERS64 temp_nt_header64 = { 0 };
    mIMAGE_SECTION_HEADER Temp_section_header = { 0 };
    int fseekholder = 0;
    


    LPSTR filename = "C:\\Users\\ACER\\Desktop\\devm\\remote_function_stomping\\x64\\Release\\remote_function_stomping.exe";
    FILE* hfile;
    errno_t err = fopen_s(&hfile, filename, "rb");

    if (err != 0) {
        printf("The file cannot be opened\n");
        return EXIT_FAILURE;
    }

    long int abcd[100] = { 0 };

  
    if (PEcheckerDOSHEADER(Temp_dos_header, hfile,&fseekholder)) {

        
        PEcheckerNTHEADER( hfile, Temp_dos_header,temp_nt_header64,&fseekholder);


        // adding the fseekholder 
        //fseekholder += fseekholder + sizeof(temp_nt_header64);

        printf("fseekholder is %d\n", fseekholder);
       

        PEcheckerSECTIONS(hfile,fseekholder,Temp_section_header,temp_nt_header64);
        
        
     }
    else {
        
        goto __endoffunction;
   
    }



__endoffunction:

        fclose(hfile);
        printf("\n\n\n\nPress enter to exit\n");
        getchar();

    return EXIT_SUCCESS;
}


BOOL PEcheckerDOSHEADER(mIMAGE_DOS_HEADER Temp_dos_header, FILE* hfile, int* fseekholder) {

    fseek(hfile, 0, SEEK_SET);
    fread(&Temp_dos_header, sizeof(mIMAGE_DOS_HEADER), 1, hfile);


    if (Temp_dos_header.e_magic == 23117) {
        printf("############ DOS HEADER ############\n\n");
        printf("A PE FILE\n");
        printf("Magic Bytes: %X\n", Temp_dos_header.e_magic);
        printf("Offset to NTheader: %X\n", Temp_dos_header.e_lfanew);
        printf("File address of relocation table: %lX\n", Temp_dos_header.e_lfarlc);
        // transferring the offset to ntheader to fseekholder
        *fseekholder =(int) Temp_dos_header.e_lfanew;
    }
    else {
        printf("The file is not a PE FILE\n");
        return FALSE;
    }

    return TRUE;
}
BOOL PEcheckerNTHEADER(FILE* hfile, mIMAGE_DOS_HEADER Temp_dos_header, mIMAGE_NT_HEADERS64 temp_NT_header64, int* fseekholder)
{

    printf("\n\n\n\n############################# NT HEADER #############################\n\n\n");


    // seeking the file to the starting of the NT_HEADER


    if (fseek(hfile, *fseekholder, SEEK_SET)) {
        printf("fseek failed with error no %d\n", GetLastError());
        return FALSE;
    }



    else {

        if (!fread(&temp_NT_header64, sizeof(mIMAGE_NT_HEADERS64), 1, hfile)) {
            printf("fread failed with error no %d\n", GetLastError());
            return FALSE;
        }

        else
        {
            if (temp_NT_header64.FileHeader.Machine == 34404) {
                printf("FILE: 64 bit\n");
                printf("No of sections: %X\n", temp_NT_header64.FileHeader.NumberOfSections);
                printf("Size of Optional Header: %d Bytes\n", temp_NT_header64.FileHeader.SizeOfOptionalHeader);

                // xor 32 is done becuase the file might contain two character stics so, after elemaninting one if we get 2 then it is a exe file;
                if ((temp_NT_header64.FileHeader.Characteristics ^ 32) == 2) {
                    printf("File identified as EXE");


                    printf("\n\n\n############################ OPTIONAL HEADER ########################################\n\n\n");
                    printf("Size of code section: %d Bytes\n", temp_NT_header64.OptionalHeader.SizeOfCode);

                    // this is only the RVA i have to get the VA too
                    printf("Address of entrypoint [RVA] 0x%X\n", temp_NT_header64.OptionalHeader.AddressOfEntryPoint);
                    printf("Size of images: %d Bytes\n", temp_NT_header64.OptionalHeader.SizeOfImage);
                    printf("Size of initialized data: %d Bytes\n", temp_NT_header64.OptionalHeader.SizeOfInitializedData);
                    printf("Size of Uninitialized data %d Bytes\n", temp_NT_header64.OptionalHeader.SizeOfUninitializedData);
                    printf("File checksum : 0x%X\n", temp_NT_header64.OptionalHeader.CheckSum);
                    //printf("No of entries in data directory array: %X\n", temp_NT_header64.OptionalHeader.DataDirectory);
                    printf("Size of Heap reserve: %d Bytes\n", (int)temp_NT_header64.OptionalHeader.SizeOfHeapReserve);
                    printf("Size of Heap commit: %d Bytes\n", (int)temp_NT_header64.OptionalHeader.SizeOfHeapCommit);
                    printf("Size of Stack reserve: %d Bytes\n", (int)temp_NT_header64.OptionalHeader.SizeOfStackReserve);
                    printf("size of Stack commit: %d Bytes \n", (int)temp_NT_header64.OptionalHeader.SizeOfStackCommit);


                    printf("\n\n\n################################ DATA DIRECTORY #####################################\n\n\n");




                    char* directories[16] = { "EXPORT","IMPORT","RESOURCE","SECURITY","BASERELOC","DEBUG","ARCHITECTURE","GLOBALPTR","TLS","LOAD_CONFIG","BOUND_IMPORT","IAT","DELAY_IMPORT","COM_DESCRIPTOR","RESERVED" };

                    for (int i = 0; i < 15; i++) {
                        printf("%s Directory at 0x%X of size %d Bytes\n", directories[i], (unsigned)temp_NT_header64.OptionalHeader.DataDirectory[i].VirtualAddress, temp_NT_header64.OptionalHeader.DataDirectory[i].Size);
                    }



       /*             PIMAGE_IMPORT_DESCRIPTOR importdescriptor = (PIMAGE_IMPORT_DESCRIPTOR)temp_NT_header64.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;*/






                }
                /*

                only checked for 64 bit but for 32 bit and other are remaining;

                */
            }






        }


    }

}
BOOL PEcheckerSECTIONS(FILE* hfile, int fseekholder, mIMAGE_SECTION_HEADER Temp_section_header, mIMAGE_NT_HEADERS64 temp_NT_header64)
{
    // Calculate the offset to the section headers
    int sectionOffset = fseekholder + sizeof(mIMAGE_NT_HEADERS64);

    // Move the file pointer to the section headers
    fseek(hfile, sectionOffset, SEEK_SET);

    printf("\n\n\n\n############################# SECTION HEADERS #############################\n\n\n");

    // Loop through each section header and print its details
    for (int i = 0; i < temp_NT_header64.FileHeader.NumberOfSections; i++) {
        printf("%d",i);
        fread(&Temp_section_header, sizeof(mIMAGE_SECTION_HEADER), 1, hfile);

        printf("Section %d:\n", i + 1);
        printf("Name: %s\n", Temp_section_header.Name);
        printf("Virtual Address: 0x%X\n", Temp_section_header.VirtualAddress);
        printf("Size of Raw Data: %d Bytes\n", Temp_section_header.SizeOfRawData);
        printf("Pointer to Raw Data: %d\n", Temp_section_header.PointerToRawData);
        printf("Characteristics: 0x%X\n\n", Temp_section_header.Characteristics);
    }

    return TRUE;
}
