
/* gcc -m64 -Os -static main.c -o test -s */

#include "logging.h"

#include <errno.h>   // errno

int main()
{
    log("INFO : Initializing ... ");
    log("INFO : Done.");
    return errno;
}
