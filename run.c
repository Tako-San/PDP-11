#include "headers/pdp.h"
#include "headers/cmd.h"
#include "headers/dbg.h"
#include "headers/tst.h"

#include <stdio.h>
#include <stdlib.h>

extern Cmd cmd[];

extern Byte mem[MEMSIZE];

extern Word reg[8];
#define pc reg[7]

// Global variables which used in do_funcs
Arg ss = {};
Arg dd = {};
Word xx = 0;
Word nn = 0;
Word n = 0;
Word r = 0;
Byte BorW = 0;

enum
{
    W = 0,
    B = 1
};

extern int tr;

void run()
{$;
    pc = 01000;

    while(pc <= MEMSIZE/2)
    {
        trace(Z, "\n");
        Word w = w_read(pc);

        INDENT(Z); trace(t, "%06o: ", pc);

        pc += 2;

        //print_reg();

        for(size_t i = 0; cmd[i].opcode != 0x0001; i++)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                if(cmd[i].params & HAS_B)
                    BorW = w >> 15;

                trace(t, "%s%s\t", cmd[i].name, (BorW == B) ? "b" : "");

                if(cmd[i].params & HAS_SS)
                    ss = get_ss(w);
                if(cmd[i].params & HAS_DD)
                    dd = get_dd(w);
                if(cmd[i].params & HAS_N)
                    trace(0, "\ntodo: get_n(w)\n");//n = get_n(w);
                if(cmd[i].params & HAS_NN)
                    nn = w & 077;
                if(cmd[i].params & HAS_R)
                    r = (w & 0700) >> 6; // temporary solution
                if(cmd[i].params & HAS_XX)
                    xx = w & 077;
                //if(cmd[i].params != NO_PARAMS)

                trace(t, "\t");
                cmd[i].do_func();

                trace(T, "\n");
                print_reg();

                break;
            }
            /*else if(i == 3)
            {
                cmd[i].do_func();
                break;
            }*/
        }


    }
$$;}


Arg get_ss(Word w)
{$;
    Arg res = get_mr(w >> 6);
$$;
    return res;
}

Arg get_dd(Word w)
{$;
    Arg res = get_mr(w);
$$;
    return res;
}

Arg get_mr(Word w)
{$;
    int r = w & 7;
    int m = (w >> 3) & 7;

    Arg res = {};

    switch(m)
    {
        case 0: res.adr = r;
                res.val = reg[r];

                INDENT(Z);
                trace(t, "R%d ", r);

                break;
        case 1: res.adr = reg[r];

                if(BorW == W)
                    res.val = w_read(res.adr);
                else if(BorW == B)
                    res.val = b_read(res.adr);

                INDENT(Z);
                trace(t, "(R%d) ", r);

                break;
        case 2: res.adr = reg[r];

                if(BorW == W)
                {
                    res.val = w_read(res.adr);
                    reg[r] += 2;
                }
                else if(BorW == B)
                {
                    res.val = b_read(res.adr);
                    reg[r] += (r < 6) ? 1 : 2;
                }

                if(r == 7)
                {
                    INDENT(Z);
                    trace(t, "#%o ", res.val);
                }
                else
                {
                    INDENT(Z);
                    trace(t, "(R%d)+ ", r);
                }

                break;
        case 3: res.adr = w_read(reg[r]);

                if(BorW == W)
                {
                    res.val = w_read(res.adr);
                    reg[r] += 2;
                }
                else if(BorW == B)
                {
                    res.val = b_read(res.adr);
                    reg[r] += 2;
                    //reg[r] += (res.adr < 6)? 1 : 2;
                }

                if(r == 7)
                {
                    INDENT(t);
                    trace(T, "@#%o ", res.val);
                }
                else
                {
                    INDENT(Z);
                    trace(t, "@(R%d)+ ", r);
                }

                break;
        case 4:
                if(BorW == W)
                {
                    reg[r] -= 2;
                    res.adr = reg[r];
                    res.val = w_read(res.adr);
                }
                else if(BorW == B)
                {
                    reg[r] -= (r < 6) ? 1 : 2;
                    res.adr = reg[r];
                    res.val = w_read(res.adr);
                }

                INDENT(Z);
                trace(t, "-(R%d) ", r);

                break;
       default: INDENT(Z);
                trace(t, "Mode %d is not implemented yet ", m);
                exit(1);

    }

$$;

    return res;
}


void print_halt()
{
    head(0, __PRETTY_FUNCTION__);
    trace(0, "\n     ");

    for(int i = 0; i < 4; i += 1)
        trace(0, "r%d = %06o ", i, reg[i]);

    trace(0, "\n     ");

    for(int i = 4; i <= 5; i += 1)
        trace(0, "r%d = %06o ", i, reg[i]);

    trace(0, "sp = %06o ", reg[6]);
    trace(0, "pc = %06o\n", reg[7]);

    head(0, "---------");
}


void print_reg()
{
    for(int i = 0; i < 6; i ++)
        trace(t, "%d:%06o ", i, reg[i]);
    trace(t, "s:%06o p:%06o\n\n", reg[6], reg[7]);
}