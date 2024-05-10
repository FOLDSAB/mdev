#include <stdio.h>
#include <Windows.h>
#include <wininet.h>

BOOL OpenInternetToTake(HANDLE* hinternet);

int main() {
    HANDLE hinternt = NULL;
    if (OpenInternetToTake(&hinternt)) {
    }
    else {
        printf("Failed to open internet with error no %d\n", GetLastError());
    }
    
    InternetCloseHandle(hinternt);
    return 0;
}

BOOL OpenInternetToTake(HANDLE* hinternet) {
    *hinternet = InternetOpenA("MyApp", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (*hinternet == NULL) {
        printf("InternetOpen failed with error no %d\n", GetLastError());
        return FALSE;
    }
    else {
        printf("Internet opened successfully!\n");
        
    }

    DWORD something =(DWORD) NULL;
HANDLE hurl =  InternetOpenUrlA(*hinternet, "http://localhost:1222/something.txt", NULL, 0, INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID, something);

   if (hurl == NULL){
    printf("Internetopenurla filaed with errro no %d\n",GetLastError());
    return FALSE;
   }


    else{
       
        DWORD noofbytestoread = 1000;
        DWORD nbreads = 0;
          LPWSTR filecontents = (LPWSTR)malloc(noofbytestoread); // Allocate memory for file contents
    if (filecontents == NULL) {
        printf("Memory allocation failed.\n");
        return FALSE;
    }
        InternetReadFile(hurl,filecontents,noofbytestoread,&nbreads);
        printf("%s\n",filecontents);
        return TRUE;
    }



}

