#include "pdp.h"
#include "tst.h"

void b_write(address adr, byte b)
{$;
    mem[adr] = b;
$$;}

byte b_read(address adr)
{$;
$$;
    return (mem[adr]);
}

void w_write(address adr, word w)
{$;
    assert(!(adr & 1));

    mem[adr + 1] = (byte)(w >> 8);
    mem[adr] = (byte)w;

$$;}

word w_read(address adr)
{$;
    assert(!(adr & 1));

    word w = ((word)mem[adr+1]) << 8;
    w |= (word)mem[adr];

$$;
    return (w);
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

    address adr = 0;
    word n = 0;
    byte cur = 0;

    while(fscanf(PRGRM, "%hx%hx", &adr, &n) == 2)
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

void mem_dump(address start, word n)
{$;
    for(int i = 0; i < 2 * n; i += 2)
        printf("%06o : %06ho\n", start + i, w_read(start + i));
$$;}
