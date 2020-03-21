#include "pdp.h"
#include "tst.h"

int main(int argc, char * argv[])
{$;
    test1();
    test2(argc, argv);
    test3(argv[1]);

    $$;
    return 0;
}
