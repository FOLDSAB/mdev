#include <stdio.h>
#include <Windows.h>
#include <wininet.h>

BOOL OpenInternetToTake(HANDLE* hinternet);

int main() {
    HANDLE hinternt = NULL;
    if (OpenInternetToTake(&hinternt)) {
        printf("Internet opened successfully!\n");
        // Perform operations using hinternt
        // InternetCloseHandle(hinternt); // Close the handle when done
    }
    else {
        printf("Failed to open internet with error no %d\n", GetLastError());
    }

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
        return TRUE;
    }
}
