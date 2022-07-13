/* gcc -m64 -Os -static main.c -o test -s */

#ifdef _WIN32
#include <windows.h>   /* HANDLE  STD_OUTPUT_HANDLE  INVALID_HANDLE_VALUE  DWORD
                          GetConsoleMode()    SetConsoleMode()    GetLastError()  */
#include <fcntl.h>     /* _O_U8TEXT _O_U16TEXT  _setmode() */
#include <stdio.h>     /* stdout  _fileno  wprintf() sleep() */
#define sleep(x) Sleep(x * 1000)
#else
#include <wchar.h>     /* wprintf() */
#include <locale.h>    /* setlocale()   LC_ALL */
#include <unistd.h>    /* sleep() */
#endif /* _WIN32 */

#include <errno.h>

#include "logging.h"

int initConsoleColors();

int main()
{
    if(initConsoleColors())
    {
        log("INFO : Colors Initialized.");
        wprintf(L"\x1b[94m\u2591\u2592\u2593\x1b[0m\n");
    }
    sleep(1);
    log("INFO : Program Closed.");
    wprintf(L"\x1b[93mLAST ERROR CODE : %lu\x1b[0m\n", errno);
    return errno;
}

int initConsoleColors()
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_U8TEXT);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if(GetConsoleMode(hOut, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        } else {
            log("ERROR : Unable to get Console Mode.");
            wprintf(L"\x1b[91mERROR : Unable to get Console Mode\x1b[0m\n");
            return -1;
        }
        log("INFO : initConsoleColors working.");
        wprintf(L"\x1b[91mINFO : initConsoleColors working\x1b[0m\n");
        errno = 0;
        return 1;
    } else {
        log("ERROR : Unable to get Console Handle.");
        wprintf(L"\x1b[91mERROR : Unable to get Console Handle\x1b[0m\n");
        return -1;
    }
#else
    setlocale(LC_ALL, "en_US.utf8");
#endif /* _WIN32 */
    log("INFO : initConsoleColors working.");
    wprintf(L"\x1b[91mINFO : initConsoleColors working.\x1b[0m\n");
    return 1;
}

