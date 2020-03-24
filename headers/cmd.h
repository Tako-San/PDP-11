#ifndef PDP_11_CMD_H
#define PDP_11_CMD_H

#include "pdp.h"

void run();

void do_halt();
void do_mov();
void do_add();
void do_unknwn();

typedef struct Cmd
{
    Word mask;
    Word opcode;
    char * name;
    void (* do_func)(void);
}Cmd;

#endif //PDP_11_CMD_H
