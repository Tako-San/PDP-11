#include "headers/pdp.h"
#include "headers/tst.h"
#include "headers/dbg.h"

Byte mem[MEMSIZE] = {};
Word reg[8] = {};


void b_write(Adr adr, Byte b)
{$;
    if(adr < 8)
    {
        if(b & 0x80)
            reg[adr] = 0xFF00;
        else
            reg[adr] = 0x0000;

        reg[adr] |= (Word)b;
    }
    else if(adr == odata)
    {
        mem[odata] = b;
        trace(0, "%c", mem[odata]);
        mem[ostat] |= 0200;
    }
    else
        mem[adr] = b;
$$;
}

Byte b_read(Adr adr)
{$;
    Byte b = 0;

    if(adr < 8)
        b = (Byte)reg[adr];
    else
        b = mem[adr];
$$;
    return b;
}

void w_write(Adr adr, Word w)
{$;
    if(adr < 8)
        reg[adr] = w;
    else if(adr == odata)
    {
        mem[adr + 1] = (Byte)(w >> 8);
        mem[adr] = (Byte)w;
        trace(0, "%c", mem[odata]);
        mem[ostat] |= 0200;
    }
    else
    {
        assert(!(adr & 1));
        mem[adr + 1] = (Byte)(w >> 8);
        mem[adr] = (Byte)w;
    }
$$;
}

Word w_read(Adr adr)
{$;
    Word w = 0;

    if(adr < 8)
        w = reg[adr];
    else
    {
        assert(!(adr & 1));
        w = ((Word)mem[adr + 1]) << 8;
        w |= (Word)mem[adr];
    }
$$;
    return w;
}

void load_file(const char * filename)
{$;
    FILE * PRGRM = NULL;
    PRGRM = fopen(filename, "rb");
    if (PRGRM == NULL)
    {
        perror(filename);
        for(int i = 0; i < 10; i++)
            printf("File opening error.\n");
        exit(1);
    }

    Adr adr = 01000;
    Word n = 0;
    Byte cur = 0;

    while(fscanf(PRGRM, "%hx%hx", &adr, &n) == 2)
    {
        for (int i = 0; i < n; i++)
        {
            fscanf(PRGRM, "%hhx", &cur);
            b_write(adr + i, cur);
        }
    }

    fclose(PRGRM);

    mem[ostat] = 0200;
$$;
}

void mem_dump(Adr start, Word n)
{$;
    for(int i = 0; i < 2 * n; i += 2)
    {
        Word w = w_read(start + i);
        INDENT(Z);
        trace(T,"%06o : %06ho\n", start + i, w);
    }

    INDENT(Z);
    trace(T,"\n");

$$;}
