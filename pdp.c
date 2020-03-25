#include "headers/pdp.h"
#include "headers/tst.h"
#include "headers/dbg.h"

Byte mem[MEMSIZE] = {};
Word reg[8] = {};

void b_write(Adr adr, Byte b)
{$;
    mem[adr] = b;
$$;}

Byte b_read(Adr adr)
{$;
$$;
    return (mem[adr]);
}

void w_write(Adr adr, Word w)
{$;
    if(adr < 8)
        reg[adr] = w;
    else
    {
        assert(!(adr & 1));
        mem[adr + 1] = (Byte)(w >> 8);
        mem[adr] = (Byte)w;
    }
$$;}

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
        printf("File opening error.\n");
        return;
    }

    Adr adr = 01000;
    Word n = 0;
    Byte cur = 0;

    while(fscanf(PRGRM, "%hx%hx", &adr, &n) == 2)
    {
        //printf("\n");
        for (size_t i = 0; i < n; i++)
        {
            fscanf(PRGRM, "%hhx", &cur);
            b_write(adr + i, cur);
        }
        //printf("\n");
    }

    fclose(PRGRM);
$$;}

void mem_dump(Adr start, Word n)
{$;
    for(int i = 0; i < 2 * n; i += 2)
    {
        Word w = w_read(start + i);
        INDENT;
        trace("%06o : %06ho\n", start + i, w);
    }
$$;}
