#include "headers/tst.h"
#include "headers/dbg.h"
#include "headers/pdp.h"
#include "headers/cmd.h"
#include <string.h>

int tr = 0;

int main(int argc, char * argv[])
{$;
    //test_rw_bw();
    //test_argv(argc, argv);

    test_argv(argc, argv);

    if(argc == 1)
    {
        printf("\nUsage:\n\n");
        return 0;
    }
    else if(argc == 2)
    {
        load_file(argv[1]);
        mem_dump(0100, 5);
        mem_dump(01000, 9);
        run();
    }
    else if(strcmp(argv[1], "-t") == 0)
    {
        tr = t;
        load_file(argv[2]);
        mem_dump(0100, 5);
        mem_dump(01000, 9);
        run();
    }
    else if(strcmp(argv[1], "-T") == 0)
    {
        tr = T;
        load_file(argv[2]);
        mem_dump(0100, 5);
        mem_dump(01000, 9);
        run();
    }
    else
    {
        printf("Unknown key");
    }
/*    else
    {
        tr = 1;
        load_file(argv[2]);
        run();
    }*/



$$;
    return 0;
}
