#include "headers/pdp.h"
#include "headers/tst.h"
#include "headers/cmd.h"
#include "headers/dbg.h"

void test_rw_bw()
{$;
    //test1
    head(0, "Byte w/r");
    Byte b1 = 0x0b;
    b_write(2, b1);
    trace(0, "\n%02hhx = %02hhx\n", b_read(2), b1);

    //test2
    head(0, "Word w/r");
    Word w1 = 0xACAB;
    w_write(4, w1);
    trace(0, "\n%02hx = %02hx\n", w_read(4), w1);

    //test3
    head(0, "Byte write Word read");
    Byte b2 = 0xcd;
    Byte b3 = 0xab;

    b_write(6, b2);
    b_write(7, b3);
    trace(0, "\n%04hx = %02hhx%02hhx\n", w_read(6), b3, b2);

    //test3
    head(0, "Word w/r");
    Word w2 = 0x0a0b;
    w_write(8, w2);
    trace(0, "\n%04hx = %04hx\n", w_read(8), w2);

    //test4
    head(0, "little/big endian");
    uint16_t x = 1; /* 0x0001 */
    trace(0, "%s\n", *((uint8_t *) &x) == 0 ? "big-endian" : "little-endian");

$$;}

void test_argv(int argc, const char ** argv)
{$;
    for(int i = 0; i <argc; i++)
        printf("%s\n", argv[i]);
    printf("\n");
$$;}

void test_file(const char * filename)
{$;
    load_file(filename);
    mem_dump(64, 2);
$$;}

void test_run(const char * filename)
{$;
   load_file(filename);
   //mem_dump(01000, 6);
   run();
   //mem_dump(0, 65*4);
$$;}

void head(int pr, const char * msg)
{
    static uint16_t counter;
    counter++;
    trace(pr, "\n------------------------%s------------------------\n", msg);
}
