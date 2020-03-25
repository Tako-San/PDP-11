#include "headers/dbg.h"
#include <stdarg.h>
#include <stdio.h>

extern int tr;

int DBG(const char * file, const char * func, int line, int relay)
{
    static int lvl = 0;

    if(relay == START)
    {
        lvl++;
        trace("%6s [%02d]%*s >>> %s\n", file, line, 4 * lvl, "", func);
    }
    else if(relay == END)
    {
        lvl--;
    }
    else if(relay == IND)
    {
        trace("%*s", 4*lvl + 16, "");
    }
    else if(relay == GETLVL)
    {
        return lvl;
    }
    return lvl;
}

void trace(const char *  format, ...)
{
    if(tr == 0)
        return;

    va_list ap;
    va_start(ap, format);

    vprintf(format, ap);

    va_end(ap);

}

