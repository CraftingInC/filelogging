
/* gcc -m64 -Os -static main.c -o test -s */

#include <errno.h>
#include "logging.h"

int initConsoleColors();

int main()
{
    log("INFO : Initializing ... ");
    if(initConsoleColors())
    {
        log("INFO : Done.");
        wprintf(L"\x1b[33mINFO \x1b[39m: \x1b[94mWe have Virtual Terminal Sequences with color !\x1b[0m\n");
    } else {
        log("ERROR : Unable to initialize Virtual Terminal Sequence.");
    }
    wprintf(L"\x1b[93mERROR CODE RETURNED : %lu\x1b[0m\n", errno);
    return errno;
}

#ifdef _WIN32
#include <windows.h>
#include <fcntl.h>     /* _O_U8TEXT _O_U16TEXT  _setmode() */
#else
#include <wchar.h>     /* wprintf() */
#include <locale.h>    /* setlocale()   LC_ALL */
#endif /* _WIN32 */

int initConsoleColors()
{
#ifdef _WIN64
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
        wprintf(L"\x1b[36mINFO \x1b[39m: \x1b[91minitConsoleColors working\x1b[0m\n");
        errno = 0;
        return 1;
    } else {
        log("ERROR : Unable to get Console Handle.");
        wprintf(L"\x1b[91mERROR : Unable to get Console Handle\x1b[0m\n");
        return -1;
    }
#else
    setlocale(LC_ALL, "en_US.utf8");
#endif /* _WIN64 */
    log("INFO : initConsoleColors working.");
    wprintf(L"\x1b[36mINFO \x1b[39m: \x1b[91minitConsoleColors working.\x1b[0m\n");
    return 1;
}
