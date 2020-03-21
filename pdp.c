#include "pdp.h"
#include "tst.h"

int Lvl = 0;

void b_write(Adress adr, byte b)
{$;
    mem[adr] = b;
$$;}

byte b_read(Adress adr)
{$;$$;
    return (mem[adr]);
}

void w_write(Adress adr, word w)
{$;
    assert(adr % 2 == 0);

    mem[adr] = *((byte*)&w);
    mem[adr+1] = *((byte*)&w + 1);
    $$;
}

word w_read(Adress adr)
{$;
    assert(adr % 2 == 0);

    //return *((word*)(mem + adr));

    word w = ((word)mem[adr+1]) << 8;
    w |= (word)mem[adr];

    $$;
    return (w);
}

void load_file(const char * filename)
{$;
    FILE * PRGRM = fopen(filename, "rb");
    assert(PRGRM != NULL);

    Adress adr = 0;
    word n = 0;
    byte cur = 0;

    while((fscanf(PRGRM, "%hx", &adr) > 0) && (fscanf(PRGRM, "%hx", &n) > 0))
    {
        printf("\n");
        for (size_t i = 0; i < n; i++)
        {
            fscanf(PRGRM, "%hhx", &cur);
            b_write(adr + i, cur);
        }
        printf("\n");
    }

    fclose(PRGRM);
$$;}

void mem_dump(Adress start, word n)
{$;
    for(int i = 0; i < 2 * n; i += 2)
        printf("%06o : %06ho\n", start + i, w_read(start + i));
$$;}
