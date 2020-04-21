#ifndef PDP_11_CMD_H
#define PDP_11_CMD_H

#include "pdp.h"

typedef struct Arg
{
    uint32_t val;
    Word adr;
}Arg;

void run();

Arg get_mr(Word w);
Arg get_ss(Word w);
Arg get_dd(Word w);

void print_reg();
void print_halt();

void set_NZ(Word num);
void print_NZVC();
void print_new_val();

void push(Word val);
Word pop();

void do_HALT();
void do_CLR();
void do_MOV();
void do_ADD();
void do_SUB();
void do_SOB();

void do_JSR();
void do_RTS();

void do_TST();
void do_CMP();

void do_CCC();
void do_CLC();
void do_CLN();
void do_CLV();
void do_CLZ();

void do_SCC();
void do_SLC();
void do_SLN();
void do_SLV();
void do_SLZ();

void do_NOP();

void do_BR();
void do_BEQ();
void do_BNE();
void do_BMI();
void do_BPL();
void do_BLT();
void do_BGE();
void do_BLE();

void do_unknown();

enum
{
    NO_PARAMS = 0,
    HAS_DD    = 1,
    HAS_SS    = 1 << 1,
    HAS_N     = 1 << 2,
    HAS_NN    = 1 << 3,
    HAS_R     = 1 << 4,
    HAS_XX    = 1 << 5,
    HAS_B     = 1 << 6
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
