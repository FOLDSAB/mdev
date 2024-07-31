#include <stdio.h>

int main() {
    int result;

    __asm {
        mov eax, 42     // Move the value 42 into the EAX register
        mov result, eax // Move the value from EAX into 'result'
    }

    printf("The result is %d\n", result);
    return 0;
}
