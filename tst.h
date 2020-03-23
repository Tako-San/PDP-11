#ifndef PDP_11_TST_H
#define PDP_11_TST_H

void DBG(const char * file, const char * func, int line, int relay);

#define $ DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, 1)
#define $$ DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, 0)

void head(const char * msg);
void test_rw_bw();
void test_argv();
void test3();


#endif //PDP_11_TST_H
