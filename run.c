#include "headers/pdp.h"
#include "headers/cmd.h"
#include "headers/dbg.h"
#include "headers/tst.h"

#include <stdio.h>
#include <stdlib.h>

Cmd cmd[] =
        {
                {0xFFFF, 0000000, NO_PARAMS, "halt", do_halt},
                {0xF000, 0010000, HAS_SS,"mov", do_mov},
                {0xF000, 0060000, HAS_SS, "add", do_add},
                {0x0000, 0000000, NO_PARAMS, "unknown cmd", do_unknown},
        };

extern Byte mem[MEMSIZE];

extern Word reg[8];
#define pc reg[7]

Arg ss = {};
Arg dd = {};

extern int tr;

void run()
{$;
    pc = 01000;

    while(pc <= MEMSIZE/2)
    {
        trace("\n\n");
        Word w = w_read(pc);

        INDENT; trace("%06o %06o: \n", pc, w);

        pc += 2;

        for(size_t i = 0; cmd[i].opcode != 0x0001; i++)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                if(cmd[i].params == HAS_SS)
                    ss = get_ss(w);
                if((cmd[i].params == HAS_DD) || (cmd[i].params == HAS_SS))
                    dd = get_dd(w);
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
                INDENT;
                trace("R%d \n", r);
                break;
        case 1: res.adr = reg[r];
                res.val = w_read(res.adr);
                INDENT;
                trace("(R%d) \n", r);
                break;
        case 2: res.adr = reg[r];
                res.val = w_read(res.adr);
                reg[r] += 2; // +1
                if(r == 7)
                {
                    INDENT;
                    trace("#%o \n", res.val);
                }
                else
                {
                    INDENT;
                    trace("(R%d)+ \n", r);
                }
                break;
       default: INDENT;
                trace("Mode %d is not implemented yet\n", m);
                exit(1);

    }

$$;

    return res;
}


void print_reg()
{
    head(__PRETTY_FUNCTION__);
    trace("\n");
    //INDENT;
    for(int i = 0; i <= 4; i += 2)
        trace("r%d = %06o ", i, reg[i]);
    trace("sp = %06o\n", reg[6]);

    //INDENT;
    for(int i = 1; i <= 5; i += 2)
        trace("r%d = %06o ", i, reg[i]);
    trace("pc = %06o\n", reg[7]);

    head("---------");
}