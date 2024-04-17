#include <stdio.h>
#include <Windows.h>
int main(){
    HANDLE hfile = INVALID_HANDLE_VALUE;

    LPCWSTR filepath =L"C:\\Users\\ACER\\Desktop\\devm\\vcode_devm\\handle.txt";

    hfile = CreateFileW(filepath,GENERIC_ALL,0,NULL,CREATE_ALWAYS,0,NULL);


    if (INVALID_HANDLE_VALUE == hfile){
        printf("[-] invalid file creation with error 0x%d",GetLastError());
    }


}