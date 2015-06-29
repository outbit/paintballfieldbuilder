#include <windows.h>
#include <stdio.h>
#include "wskey.h"      // Licensing Software
using namespace WSKey;

std::ofstream g_logfile; // DEFINE IN A SOURCE FILE (main.cpp)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CWSKey key;
    char tmp[WSK_MAXSTR] = {0};
    if ( true == key.GenerateKey() ) {
        key.GetKey(tmp);
        key.LogKey();
        MessageBox(0, tmp, "Generated Key", 0);
    } else {
        MessageBox(0, "failed", "to Generate Key", 0);
    }


    return 0;
}