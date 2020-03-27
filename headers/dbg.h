#ifndef PDP_11_DBG_H
#define PDP_11_DBG_H

enum
{
    START  = 1,
    END    = 0,
    IND    = 2,
    GETLVL = 3,
};

#define t 1
#define T 2

int DBG(const char * file, const char * func, int line, int relay, int pr);

#define $ DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, START, T)
#define $$ DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, END, T)
#define INDENT(x) DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, IND, x)

void trace(int pr, const char *  format, ...);


#endif //PDP_11_DBG_H
