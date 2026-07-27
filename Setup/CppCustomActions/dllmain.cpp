#include "framework.h"

#include <MsiQuery.h>
#include <wcautil.h>


extern "C" BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason, LPVOID)
{
    switch (ulReason)
    {
    case DLL_PROCESS_ATTACH:
        WcaGlobalInitialize(hInst);
        break;

    case DLL_PROCESS_DETACH:
        WcaGlobalFinalize();
        break;
    }

    return TRUE;
}
