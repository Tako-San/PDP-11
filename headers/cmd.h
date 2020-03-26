#ifndef PDP_11_CMD_H
#define PDP_11_CMD_H

#include "pdp.h"

typedef struct Arg
{
    Word val;
    Word adr;
}Arg;

void run();

Arg get_mr(Word w);
Arg get_ss(Word w);
Arg get_dd(Word w);

void print_reg();

void do_HALT();
void do_CLR();
void do_MOV();
void do_ADD();
void do_SUB();
void do_SOB();
void do_unknown();

enum
{
    NO_PARAMS = 0,
    HAS_DD    = 1,
    HAS_SS    = 2,
    HAS_N     = 4,
    HAS_NN    = 8,
    HAS_R     = 16,
    HAS_XX    = 32,
};

typedef struct Cmd
{
    Word mask;
    Word opcode;
    uint8_t params;
    char * name;
    void (* do_func)(void);
}Cmd;

#endif //PDP_11_CMD_H
