#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, unsigned long fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
    }

    return TRUE;
}
