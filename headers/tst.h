#ifndef PDP_11_TST_H
#define PDP_11_TST_H

#include <stdio.h>


void head(int pr, const char * msg);
void test_rw_bw();
void test_argv(int argc, char ** argv);
void test_file(const char * filename);
void test_run(const char * filename);


#endif //PDP_11_TST_H
