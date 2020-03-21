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

void DBG(const char * file, const char * func, int line, int relay)
{
    static int lvl = 0;

    if(relay == 1)
    {
        lvl++;
        printf("%s [%02d]%*s >>> %s\n", file, line, 4 * lvl, "", func);
    }
    else
    {
        lvl--;
    }
}

void load_file()
{

}
