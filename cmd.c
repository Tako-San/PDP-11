#include "headers/cmd.h"
#include "headers/tst.h"
#include <stdlib.h>

extern Arg ss;
extern Arg dd;
extern Word reg[8];
#define pc reg[7];

void do_add()
{//$;
    INDENT;
    printf("[%s]\n", __PRETTY_FUNCTION__);
    print_reg();
    reg[dd.adr] = dd.val + ss.val;
    print_reg();
//$$;
}

void do_halt()
{//$;
    INDENT;
    printf("[%s]\n", __PRETTY_FUNCTION__);
    print_reg();
//$$;
    exit(0);
}

void do_mov()
{//$;
    INDENT;
    printf("[%s]\n", __PRETTY_FUNCTION__);
    print_reg();
    reg[dd.adr] = w_read(ss.adr);
    print_reg();
//$$;
}

void do_unknown()
{//$;
    INDENT;
    printf("[%s]\n", __PRETTY_FUNCTION__);
//$$;
    //exit(0);
}

/*void do_add()
{
    printf("%s\n", __PRETTY_FUNCTION__);
}*/

