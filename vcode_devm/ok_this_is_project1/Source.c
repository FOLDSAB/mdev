#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

BOOL arrayAdder(int* parr, int len) {
    int* temparr = (int*)malloc((len + 1) * sizeof(int)); // Dynamically allocate memory
    if (temparr == NULL) {
        printf("Memory allocation failed\n");
        return FALSE;
    }

    for (int i = 0; i < len; i++) {
        temparr[i] = parr[i];
    }

    temparr[len] = 12;

    printf("The n is %d\n", len + 1);
    memcpy(parr, temparr, (len + 1) * sizeof(int));
    free(temparr); // Free dynamically allocated memory
    return TRUE;
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
    int len = sizeof(arr) / sizeof(int);
    printf("The size of arr is %d\n", sizeof(arr));
    printf("The len of arr is %d\n", len);
    if (arrayAdder(arr, len)) {
        printf("The len of arr is %d\n", len + 1);

        for (int i = 0; i < (len + 1); i++) {
            printf("The arr[%d] : %d \n", i, arr[i]);
        }
    }

    printf("Press <enter> to exit");
    getchar();
    return 0;
}
