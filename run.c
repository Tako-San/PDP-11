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

Arg ss = {};
Arg dd = {};
Word nn = 0;
Word n = 0;
Word r = 0;



extern int tr;

void run()
{$;
    pc = 01000;

    while(pc <= MEMSIZE/2)
    {
        trace(t, "\n\n");
        Word w = w_read(pc);

        INDENT(t); trace(t, "%06o %06o: \n", pc, w);

        pc += 2;

        //print_reg();

        for(size_t i = 0; cmd[i].opcode != 0x0001; i++)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
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
                    trace(0, "\ntodo: get_xx(w)\n");
                cmd[i].do_func();
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

                INDENT(T);
                trace(T, "R%d\n", r);

                break;
        case 1: res.adr = reg[r];
                res.val = w_read(res.adr);

                INDENT(T);
                trace(T, "(R%d)\n", r);

                break;
        case 2: res.adr = reg[r];
                res.val = w_read(res.adr);
                reg[r] += 2; // +1

                if(r == 7)
                {
                    INDENT(T);
                    trace(T, "#%o\n", res.val);
                }
                else
                {
                    INDENT(T);
                    trace(T, "(R%d)+\n", r);
                }

                break;
        case 3: res.adr = w_read(reg[r]);
                res.val = w_read(res.adr);
                reg[r] += 2;
                if(r == 7)
                {
                    INDENT(T);
                    trace(T, "@#%o\n", res.val);
                }
                else
                {
                    INDENT(T);
                    trace(T, "@(R%d)+\n", r);
                }

                break;
        case 4: reg[r] -= 2;
                res.adr = reg[r];
                res.val = w_read(res.adr);

                INDENT(T);
                trace(T, "-(R%d)\n", r);

                break;
       default: INDENT(T);
                trace(T, "Mode %d is not implemented yet\n", m);
                exit(1);

    }

$$;

    return res;
}


void print_reg()
{
    head(0, __PRETTY_FUNCTION__);
    trace(0, "\n     ");
    //INDENT;
    for(int i = 0; i <= 4; i += 2)
        trace(0, "r%d = %06o ", i, reg[i]);
    trace(0, "sp = %06o\n", reg[6]);

    //INDENT;
    trace(0, "     ");
    for(int i = 1; i <= 5; i += 2)
        trace(0, "r%d = %06o ", i, reg[i]);
    trace(0, "pc = %06o\n", reg[7]);

    head(0, "---------");
}