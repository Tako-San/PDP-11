#include "pdp.h"
#include "tst.h"

int main(int argc, char * argv[])
{$;
    test_rw_bw();
    test_argv(argc, argv);
    if(argc > 1)
        test3(argv[1]);

$$;
    return 0;
}
