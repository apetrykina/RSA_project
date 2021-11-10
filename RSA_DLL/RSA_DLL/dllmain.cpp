#include "pch.h"
#include <iostream>
using namespace std;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		cout << "lpReserved = " << lpReserved << endl;
		if (lpReserved)
			cout << "DLL static mode.\n\n";
		else
			cout << "DLL dymamic mode.\n\n";
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

