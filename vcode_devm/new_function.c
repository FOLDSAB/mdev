#include <stdio.h>
#include <Windows.h>


BOOL GenerateIPV4Output(unsigned char* pshellcode,SIZE_T shellcode);
char* GenerateIPV4(int a, int b, int c , int d){
    unsigned char output[32];
    sprintf(output,"%d.%d.%d.%d",a,b,c,d);


    printf("[i] output:%s\n",output);
    // return (char*)output;

}
int main() {
    unsigned char Text[] = {0x11, 0x22, 0x33, 0x44,0x11, 0x22, 0x33, 0x45};

    unsigned char *pText = Text;

    SIZE_T sText = (SIZE_T)(sizeof(Text));

    printf("The size of payload is %zu\n",sText);

   GenerateIPV4Output(pText,sText);

    return 0;
}

BOOL GenerateIPV4Output(unsigned char* pshellcode,SIZE_T shellcodesize){

if(pshellcode == NULL|| shellcodesize == 0 || shellcodesize % 4 !=0)
{

return FALSE;
}

printf("char* IPV4ARRAY[%d] = {\n\t",(int)(shellcodesize/4));

int c = 4, counter = 0;
char *IP = NULL;


for (int i = 0 ; i < shellcodesize ; i++){

    if (c == 4){
        counter++;
    
    printf("pshellcode[%d]=%d\n",i,pshellcode[i]);
    printf("pshellcode[%d]=%d\n",i+1,pshellcode[i+1]);
    printf("pshellcode[%d]=%d\n",i+2,pshellcode[i+2]);
    printf("pshellcode[%d]=%d\n",i+3,pshellcode[i+3]);
    IP = GenerateIPV4(pshellcode[i],pshellcode[i+1],pshellcode[i+2],pshellcode[i+3]);

    if (i == shellcodesize - 4){
        printf("\"%s\"",IP);
    }
    else{
        printf("\"%s\"",IP);
    }
    c = 1;


    }

    else{
        printf("called");
        c++;
    }
}
}
