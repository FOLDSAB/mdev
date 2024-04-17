// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <stdio.h>


VOID messagepayload() {
    MessageBoxA(NULL, "Is it dll injection", "wow|", MB_OK|MB_ICONINFORMATION);
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        messagepayload();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

