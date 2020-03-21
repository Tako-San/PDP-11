#ifndef PDP_11_TST_H
#define PDP_11_TST_H

void DBG(const char * file, const char * func, int line, int relay);

#define $ DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, 1)
#define $$ DBG(__FILE__, __PRETTY_FUNCTION__, __LINE__, 0)

void head();
void test1();
void test2();
void test3();


#endif //PDP_11_TST_H
