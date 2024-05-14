#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

BOOL ParseDosHeaders(FILE* hfile, LONG* NTheaderoffset);
BOOL ParseNTHeaders(FILE* hfile, LONG NTheaderoffset,WORD* Noofsections);
BOOL ParseSectionHeaders(FILE* hfile,LONG NTheaderoffset,WORD noofsections);
int main(int argv, char *argc[]) {

    LONG Ntheaderoffset = NULL;
    
    WORD noofsections = 0;

    if (argv != 2) {
        printf("Please give the correct Path to file\n");
        goto END;
    }
    const char* PathToFile = argc[1];

    FILE* hfile; 
    errno_t err = fopen_s(&hfile, PathToFile, "rb");


  if (err != 0) {
      printf("cannot open the file specified");
      goto END;
  }

    if (!ParseDosHeaders(hfile,&Ntheaderoffset)) {
        printf("Error parsing DOS headers\n");
        goto END;
    }

    if (!ParseNTHeaders(hfile, Ntheaderoffset,&noofsections)) {
        printf("Error Parsing Dos Header\n");
        goto END;
    }
    if (!ParseSectionHeaders(hfile, Ntheaderoffset, noofsections)) {
        printf("Error Parsing Dos Header");
        goto END;
    }

    END:
        printf("Press enter to exit");
        getchar();
        return 0;
}

BOOL ParseDosHeaders(FILE* hfile,LONG *NTheaderoffset) {
    if (hfile == NULL) {
        return FALSE;
    }

    fseek(hfile, 0, SEEK_SET);

    IMAGE_DOS_HEADER imgDos = { 0 };
    fread(&imgDos, sizeof(IMAGE_DOS_HEADER), 1, hfile);
    

    if (imgDos.e_magic != IMAGE_DOS_SIGNATURE) {
        printf("The magic failed\n");
        return FALSE;
    }


    printf("Image Magicbyte: %X\n", imgDos.e_magic);
    printf("Offset to NT header 0x%lX\n", imgDos.e_lfanew);
    *NTheaderoffset = imgDos.e_lfanew;
    return TRUE;
}


BOOL ParseNTHeaders(FILE* hfile, LONG NTheaderoffset, WORD* Noofsections) {

    IMAGE_NT_HEADERS imgNT;

    rewind(hfile);

    fseek(hfile, NTheaderoffset, SEEK_SET);

    fread(&imgNT, sizeof(IMAGE_NT_HEADERS), 1, hfile);

    if (imgNT.Signature != IMAGE_NT_SIGNATURE) {
        printf("non matching signature\n");
        return FALSE;
    }

    else {


        printf("\n\n\n############################ OPTIONAL HEADER ########################################\n\n\n");
        printf("No of sections: %X\n", imgNT.FileHeader.NumberOfSections);
        *Noofsections = imgNT.FileHeader.NumberOfSections;
        printf("Size of code section: %d Bytes\n", imgNT.OptionalHeader.SizeOfCode);

        // this is only the RVA i have to get the VA too
        printf("Address of entrypoint [RVA] 0x%X\n", imgNT.OptionalHeader.AddressOfEntryPoint);
        printf("Size of images: %d Bytes\n", imgNT.OptionalHeader.SizeOfImage);
        printf("Size of initialized data: %d Bytes\n", imgNT.OptionalHeader.SizeOfInitializedData);
        printf("Size of Uninitialized data %d Bytes\n", imgNT.OptionalHeader.SizeOfUninitializedData);
        printf("File checksum : 0x%X\n", imgNT.OptionalHeader.CheckSum);
        printf("Size of Heap reserve: %d Bytes\n", (int)imgNT.OptionalHeader.SizeOfHeapReserve);
        printf("Size of Heap commit: %d Bytes\n", (int)imgNT.OptionalHeader.SizeOfHeapCommit);
        printf("Size of Stack reserve: %d Bytes\n", (int)imgNT.OptionalHeader.SizeOfStackReserve);
        printf("size of Stack commit: %d Bytes \n", (int)imgNT.OptionalHeader.SizeOfStackCommit);


    }

    printf("\n\n\n######################################DATA DIRECTORY##################################\n\n\n");

    char* directories[IMAGE_NUMBEROF_DIRECTORY_ENTRIES] = { "EXPORT","IMPORT","RESOURCE","SECURITY","BASERELOC","DEBUG","ARCHITECTURE","GLOBALPTR","TLS","LOAD_CONFIG","BOUND_IMPORT","IAT","DELAY_IMPORT","COM_DESCRIPTOR","RESERVED" };

    for (WORD i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
    {
    
        printf("%s Directory at 0x%X of size %d Bytes\n", directories[i], imgNT.OptionalHeader.DataDirectory[i].VirtualAddress, (int)imgNT.OptionalHeader.DataDirectory[i].Size);

    }


    return TRUE;

}

BOOL ParseSectionHeaders(FILE* hfile, LONG NTheaderoffset, WORD noofsections)
{
    printf("\n\n\n######################## Section Header ############################\n\n\n");


    LONG offset = NTheaderoffset + sizeof(IMAGE_NT_HEADERS);
    
    IMAGE_SECTION_HEADER imgSectionHeader = { 0 };

    for (int i = 0; i < noofsections; i++) {



    

        rewind(hfile);
        fseek(hfile, offset, SEEK_SET);



        fread(&imgSectionHeader,sizeof(IMAGE_SECTION_HEADER), 1, hfile);

        printf("%s\n", imgSectionHeader.Name);



        
        printf("section name: %s\n", imgSectionHeader.Name);
        printf("virtual size: 0x%x\n", imgSectionHeader.Misc.VirtualSize);
        printf("virtual address: 0x%x\n", imgSectionHeader.VirtualAddress);
        printf("size of raw data: %d bytes\n", imgSectionHeader.SizeOfRawData);
        printf("pointer to raw data: 0x%x\n", imgSectionHeader.PointerToRawData);
        printf("characteristics: 0x%x\n\n", imgSectionHeader.Characteristics);

        offset = offset + sizeof(IMAGE_SECTION_HEADER);

    }



    
    return TRUE;
}


