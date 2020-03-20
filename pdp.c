#include "pdp.h"

void b_write(Adress adr, byte b)
{//$
    mem[adr] = b;
    return({});
}

byte b_read(Adress adr)
{//$
    return mem[adr];
}

void w_write(Adress adr, word w)
{//$
    assert(adr % 2 == 0);
    *((word*)(mem + adr)) = w;
    return ({});
}

word w_read(Adress adr)
{//$
    assert(adr % 2 == 0);
    return *((word*)(mem + adr));
}

void load_file()
{

}
