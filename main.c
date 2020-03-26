#include "headers/tst.h"
#include "headers/dbg.h"
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

    if(strcmp(argv[1], "-t") != 0 && strcmp(argv[1], "-T") != 0 )
        test_run(argv[1]);
    else
    {
        tr = 1;
        test_run(argv[2]);
    }



$$;
    return 0;
}
