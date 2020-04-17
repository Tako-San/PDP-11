#include "headers/cmd.h"
#include "headers/dbg.h"
#include <stdlib.h>

extern int tr;

// Global variables which used in do_funcs
extern Arg ss;
extern Arg dd;
extern Word xx;
extern Word nn;
extern Word n;
extern Word r;
extern Byte BorW;

//flags
uint8_t flag_N = 0;
uint8_t flag_Z = 0;
uint8_t flag_V = 0;
uint8_t flag_C = 0;

enum
{
    W = 0,
    B = 1
};


extern Byte mem[MEMSIZE];

extern Word reg[8];
#define pc reg[7]

Cmd cmd[] =
        {
                {0xFFFF, 0000000, NO_PARAMS, "HALT", do_HALT},
                {0xFFFF, 0000240, NO_PARAMS, "NOP", do_NOP},

                {0xFFFF, 0000257, NO_PARAMS, "CCC", do_CCC},
                {0xFFFF, 0000241, NO_PARAMS, "CLC", do_CLC},
                {0xFFFF, 0000250, NO_PARAMS, "CLN", do_CLN},
                {0xFFFF, 0000242, NO_PARAMS, "CLV", do_CLV},
                {0xFFFF, 0000244, NO_PARAMS, "CLZ", do_CLZ},

                {0xFFFF, 0000277, NO_PARAMS, "CCC", do_SCC},
                {0xFFFF, 0000261, NO_PARAMS, "CLC", do_SLC},
                {0xFFFF, 0000270, NO_PARAMS, "CLN", do_SLN},
                {0xFFFF, 0000262, NO_PARAMS, "CLV", do_SLV},
                {0xFFFF, 0000264, NO_PARAMS, "CLZ", do_SLZ},

                {0xFFC0, 0000400, HAS_XX, "BR", do_BR},
                {0xFFC0, 0001400, HAS_XX, "BEQ", do_BEQ},
                {0xFFC0, 0001000, HAS_XX, "BNE", do_BNE},
                {0xFFC0, 0100400, HAS_XX, "BMI", do_BMI},
                {0xFFC0, 0100000, HAS_XX, "BPL", do_BPL},
                {0xFFC0, 0002400, HAS_XX, "BLT", do_BLT},
                {0xFFC0, 0002000, HAS_XX, "BGE", do_BGE},
                {0xFFC0, 0003400, HAS_XX, "BLE", do_BLE},

                {0xFE00, 0077000, HAS_R | HAS_NN, "SOB", do_SOB},

                {0xF000, 0060000, HAS_SS | HAS_DD, "ADD", do_ADD},
                {0xF000, 0160000, HAS_SS | HAS_DD, "SUB", do_SUB},

                {0x7FC0, 0005000, HAS_B | HAS_DD, "CLR", do_CLR},
                {0x7FC0, 0005700, HAS_B | HAS_DD, "TST", do_TST},

                {0x7000, 0010000, HAS_B | HAS_SS | HAS_DD, "MOV", do_MOV},
                {0x7000, 0020000, HAS_B | HAS_SS | HAS_DD, "CMP", do_CMP},

                {0x0000, 0000000, NO_PARAMS, "unknown cmd", do_unknown},
        };

void do_ADD()
{$;
    INDENT(Z);
    trace(Z, "[%s]\n", __PRETTY_FUNCTION__);

    uint32_t res = dd.val + ss.val;
    w_write(dd.adr, res);

    set_NZ(res);
    flag_C = (res >> (8 * sizeof(Word))) & 1;

    INDENT(Z);
    trace(t, "%d + %d\t", dd.val, ss.val);

    INDENT(Z);
    print_NZVC();
    trace(t, "\n");
$$;
}

void do_SUB()
{$;
    INDENT(Z);
    trace(Z, "[%s]\n", __PRETTY_FUNCTION__);
    //print_reg();

    uint32_t res = dd.val - ss.val;
    w_write(dd.adr, res);

    set_NZ(res);
    flag_C = (res >> (8 * sizeof(Word))) & 1;

    INDENT(Z);
    trace(T, "%d - %d\t", dd.val, ss.val);

    INDENT(Z);
    print_NZVC();
    trace(t, "\n");
$$;}

void do_HALT()
{$;
    INDENT(Z);
    tr = 1;
    trace(Z, "[%s]\n", __PRETTY_FUNCTION__);
    print_halt();
$$;
    exit(0);
}

void do_MOV()
{$;
    INDENT(Z);
    trace(Z, "[%s]\n", __PRETTY_FUNCTION__);

    if(BorW == W)
        w_write(dd.adr, ss.val);
    else if(BorW == B)
        b_write(dd.adr, ss.val);
    else
    {
        trace(0, "WHAT JKL;SDFJKLFSDJKFSJKL\n");
        exit(0);
    }

    set_NZ(ss.val);
    flag_V = 0;

    INDENT(Z);
    if(dd.adr < 6)
        trace(t, "r%d = %o\t", dd.adr, ss.val);
    else if(dd.adr == 6)
        trace(t, "s = %o\t", ss.val);
    else if(dd.adr == 7)
        trace(t, "p = %o\t", ss.val);
    else
        trace(t, "mem[%d] = %o\t", dd.adr, ss.val);

    INDENT(Z);
    print_NZVC();
    trace(t, "\n");

    BorW = 0;
$$;
}

void do_CLR()
{$;
   INDENT(Z);
    trace(Z, "[%s]\n", __PRETTY_FUNCTION__);

    if(BorW == W)
        w_write(dd.adr, 0);
    else if(BorW == B)
        b_write(dd.adr, 0);
    else
    {
        trace(0, "WHAT JKL;SDFJKLFSDJKFSJKL\n");
        exit(0);
    }

    INDENT(Z);
    if(dd.adr < 6)
        trace(t, "r%d = %o\t", dd.adr, ss.val);
    else if(dd.adr == 6)
        trace(t, "s = %o\t", ss.val);
    else if(dd.adr == 7)
        trace(t, "p = %o\t", ss.val);
    else
        trace(t, "mem[%d] = %o\t", dd.adr, ss.val);

    flag_N = flag_V = flag_C = 0;
    flag_Z = 1;

    INDENT(Z);
    print_NZVC();
    trace(t, "\n");

    BorW = 0;
$$;}

void do_SOB()
{$;
    INDENT(Z);
    trace(Z, "[%s]\n", __PRETTY_FUNCTION__);

    INDENT(Z);
    print_NZVC();

    INDENT(Z);
    trace(t, "\nbefore SOB: R = %hx, Rn = %ho, NN = %hx, pc = %ho\n", r, reg[r], nn, pc);

    reg[r] -= 1;

    if(reg[r] > 0)
        pc -= 2*nn;

    INDENT(Z);
    trace(t, "after  SOB: R = %hx, Rn = %ho, NN = %hx, pc = %ho\n", r, reg[r], nn, pc);

$$;}

void do_TST()
{$;
    INDENT(Z);
    trace(t, "[%s]\n", __PRETTY_FUNCTION__);

    set_NZ(dd.val);
    flag_V = flag_C = 0;

    INDENT(Z);
    print_NZVC();
$$;}

void do_CMP()
{$;
    INDENT(Z);
    trace(t, "[%s]\n", __PRETTY_FUNCTION__);

    uint32_t res = ss.val - dd.val;

    set_NZ(res);
    flag_C = (res >> (8 * sizeof(Word))) & 1;

    INDENT(Z);
    print_NZVC();

$$;}


void do_BR()
{$;
    pc += 2*xx;
    INDENT(Z);
    print_NZVC();
$$;}

void do_BEQ()
{$;
    if(flag_Z == 1)
        do_BR();
$$;}

void do_BNE()
{$;
    if(flag_Z == 0)
        do_BR();
$$;}

void do_BMI()
{$;
    if(flag_N == 1)
        do_BR();
$$;}

void do_BPL()
{$;
    if(flag_N == 0)
        do_BR();
$$;}

void do_BLT()
{$;
    if(0)
        do_BR();
$$;}

void do_BGE()
{$;
    if(0)
        do_BR();
$$;}

void do_BLE()
{$;
    if(0)
        do_BR();
$$;}


void do_CCC()
{$;
    flag_N = flag_Z = flag_V = flag_C = 0;
$$;}

void do_CLC()
{$;
    flag_C = 0;
$$;}

void do_CLN()
{$;
    flag_N = 0;
$$;}

void do_CLV()
{$;
    flag_V = 0;
$$;}

void do_CLZ()
{$;
    flag_C = 0;
$$;}



void do_SCC()
{$;
    flag_N = flag_Z = flag_V = flag_C = 1;
$$;}

void do_SLC()
{$;
    flag_C = 1;
$$;}

void do_SLN()
{$;
    flag_N = 1;
$$;}

void do_SLV()
{$;
    flag_V = 1;
$$;}

void do_SLZ()
{$;
    flag_C = 1;
$$;}

void do_NOP()
{$;$$;}



void do_unknown()
{$;
    INDENT(t);
    trace(t, "[%s]\n", __PRETTY_FUNCTION__);
$$;
    exit(1);
}


void set_NZ(Word num)
{$;
    flag_Z = (num == 0);

    int move = (BorW == W)? 15 : 7;
    flag_N = (num >> move) & 1;
$$;}

void print_NZVC()
{$;
    trace(t, "%c", flag_N ? 'N' : '-');
    trace(t, "%c", flag_Z ? 'Z' : '-');
    trace(t, "%c", flag_V ? 'V' : '-');
    trace(t, "%c", flag_C ? 'C' : '-');
    //trace(t, ":%d%d%d%d", flag_N, flag_Z, flag_V, flag_C);
$$;}