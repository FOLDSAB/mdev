#include <stdio.h>

int main() {
    int result;
    int a = 5;
    int b = 10;

    __asm {
        mov eax, a
        add eax, b
        mov result, eax
    }

    printf("Result: %d\n", result);

    printf("press <enter> to exit");
    getchar();
    return 0;
}
