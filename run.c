#include "headers/pdp.h"
#include "headers/cmd.h"
#include "headers/tst.h"

#include <stdio.h>


Cmd cmd[] =
        {
                {0xFFFF, 0x0000, "halt", do_halt},
                {0xF000, 0x1000, "mov", do_mov},
                {0xF000, 0x6000, "add", do_add},
                {0xFFFF, 0xFFFF, "unknwn cmd", do_unknwn},
        };

Word reg[8] = {};
#define pc reg[7]


void run()
{$;
    pc = 01000;

    while(pc <= MEMSIZE/2)
    {
        Word w = w_read(pc);

        printf("\n");
        INDENT;
        printf("%06o %06o: \n\n", pc, w);
        // trace

        pc += 2;

        for(size_t i = 0; cmd[i].opcode != 0xFFFF; i++)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                cmd[i].do_func();
                break;
            }
            else
                do_unknwn();
        }

    }
$$;}