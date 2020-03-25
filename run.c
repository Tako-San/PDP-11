#include "headers/pdp.h"
#include "headers/cmd.h"
#include "headers/tst.h"

#include <stdio.h>
#include <stdlib.h>

Cmd cmd[] =
        {
                {0xFFFF, 0000000, NO_PARAMS, "halt", do_halt},
                {0xF000, 0010000, HAS_SS,"mov", do_mov},
                {0xF000, 0060000, HAS_SS, "add", do_add},
                {0xFFFF, 0000001, NO_PARAMS, "unknown cmd", do_unknown},
        };

Word reg[8] = {};
#define pc reg[7]

Arg ss = {};
Arg dd = {};

void run()
{$;
    pc = 01000;

    while(pc <= MEMSIZE/2)
    {
        Word w = w_read(pc);

        printf("\n");
        INDENT; printf("%06o %06o: \n", pc, w);
        // trace

        pc += 2;

        for(size_t i = 0; 1/*cmd[i].opcode != 0x0001*/; i++)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                if(cmd[i].params == HAS_SS)
                {
                    ss = get_ss(w);
                    dd = get_dd(w);
                }
                if(cmd[i].params == HAS_DD)
                    dd = get_dd(w);
                cmd[i].do_func();
                break;
            }
            else if(i == 3)
            {
                cmd[i].do_func();
                break;
            }
        }


    }
$$;}


Arg get_ss(Word w)
{$;
    Arg res = get_modereg(w >> 6);
$$;
    return res;
}

Arg get_dd(Word w)
{$;
    Arg res = get_modereg(w);
$$;
    return res;
}

Arg get_modereg(Word w)
{$;
    int r = w & 7;
    int m = (w >> 3) & 7;

    Arg res = {};

    switch(m)
    {
        case 0: res.adr = r;
                res.val = reg[r];
                INDENT; printf("R%d \n", r); //trace
                break;
        case 1: res.adr = reg[r];
                res.val = w_read(res.adr);
                INDENT; printf("(R%d) \n", r); //trace
                break;
        case 2: res.adr = reg[r];
                res.val = w_read(res.adr);
                reg[r] += 2; // +1
                if(r == 7)
                {
                    INDENT; printf("#%o \n", res.val); //trace
                }
                else
                {
                    INDENT; printf("(R%d)+ \n", r); //trace
                }
                break;
       default: INDENT; printf("Mode %d is not implemented yet\n", m); //trace
                exit(1);

    }

$$;

    return res;
}


void print_reg()
{
    printf("\n");
    INDENT;
    for(int i = 0; i <= 4; i += 2)
        printf("r%d = %06o ", i, reg[i]);
    printf("sp = %06o\n", reg[6]);

    INDENT;
    for(int i = 1; i <= 5; i += 2)
        printf("r%d = %06o ", i, reg[i]);
    printf("pc = %06o\n", reg[7]);
}