#ifndef PDP_11_DBG_H
#define PDP_11_DBG_H

enum
{
    START  = 1,
    END    = 0,
    IND    = 2,
    GETLVL = 3,
};

int DBG(const char * file, const char * func, int line, int relay);

#define $ DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, START)
#define $$ DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, END)
#define INDENT DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, IND)

void trace(const char *  format, ...);


#endif //PDP_11_DBG_H
