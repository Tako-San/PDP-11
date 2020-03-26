#include "headers/cmd.h"
#include "headers/dbg.h"
#include <stdlib.h>

extern int tr;

extern Arg ss;
extern Arg dd;

extern Byte mem[MEMSIZE];

extern Word reg[8];
#define pc reg[7]
#define pc_num 7

void do_add()
{$;
    INDENT;
    trace("[%s]\n", __PRETTY_FUNCTION__);
    //print_reg();

    w_write(dd.adr, dd.val + ss.val);

    INDENT;
    trace("%d + %d", dd.val, ss.val);
    print_reg();
$$;
}

void do_halt()
{$;
    INDENT;
    tr = 1;
    trace("[%s]\n", __PRETTY_FUNCTION__);
    print_reg();
$$;
    exit(0);
}

void do_mov()
{$;
    INDENT;
    trace("[%s]\n", __PRETTY_FUNCTION__);
    //print_reg();

    w_write(dd.adr, ss.val);

    INDENT;
    trace("reg[%d] = %d", dd.adr, ss.val);
    print_reg();
$$;
}

void do_unknown()
{$;
    INDENT;
    trace("[%s]\n", __PRETTY_FUNCTION__);
$$;
    exit(1);
}

/*void do_add()
{
    printf("%s\n", __PRETTY_FUNCTION__);
}*/

