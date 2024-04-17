#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdint.h> // Include for unsigned char

void XORBYKEY(PBYTE pshellcode, SIZE_T sshellcode, BYTE key) {
    for (SIZE_T i = 0; i < sshellcode; i++) {
        pshellcode[i] = pshellcode[i] ^ (key + i);
        printf("0x%02X, ", pshellcode[i]); // Print byte values in hexadecimal format

    }
}

int main() {
    const unsigned char TEXT_RAWDATA[] = {
      0x10, 0x20, 0x30, 0x40, 0x14, 0x24, 0x34, 0x4C, 0x18, 0x28, 0x38, 0x48, 0x1C, 0x2C, 0x3C, 0x54, 0x00, 0x30, 0x20, 0x50, 0x04, 0x34, 0x24, 0x5C, 0x08, 0x38, 0x28, 0x58, 0x0C, 0x3C, 0x2C, 0x64, 0x30, 0x00, 0x10, 0x60, 0x34, 0x04, 0x14, 0x6C
    };



    const unsigned char* pTEXT_RAWDATA = TEXT_RAWDATA;
    SIZE_T spayloadsize = sizeof(TEXT_RAWDATA);
    BYTE key = 0x1;

    printf("The size of spayloadsize is %ld\n",(LONG) spayloadsize);
    XORBYKEY((PBYTE)pTEXT_RAWDATA, spayloadsize, key);

    getchar(); // Wait for a character before exiting

    return 0;
}
