#include "headers/tst.h"
#include "headers/dbg.h"

int tr = 1;

int main(int argc, char * argv[])
{$;
    //test_rw_bw();
    //test_argv(argc, argv);
    if(argc > 1)
    {
        //test_file(argv[1]);
        test_run(argv[1]);
    }

$$;
    return 0;
}
