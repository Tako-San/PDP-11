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
        run();
    }
    else if(strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "-T") == 0 )
    {
        tr = 1;
        load_file(argv[2]);
        run();
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
