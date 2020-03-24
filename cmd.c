#include "headers/cmd.h"
#include "headers/tst.h"
#include <stdlib.h>

void do_add()
{$;
    INDENT;
    printf("[%s]\n", __PRETTY_FUNCTION__);
$$;}

void do_halt()
{$;
    INDENT;
    printf("[%s]\n", __PRETTY_FUNCTION__);
$$;
    exit(0);
}

void do_mov()
{$;
    INDENT;
    printf("[%s]\n", __PRETTY_FUNCTION__);
$$;}

void do_unknwn()
{$;
    INDENT;
    printf("[%s]\n", __PRETTY_FUNCTION__);
$$;
    //exit(0);
}

/*void do_add()
{
    printf("%s\n", __PRETTY_FUNCTION__);
}*/