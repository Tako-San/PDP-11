#include "../headers/pdp.h"
#include "../headers/tst.h"
#include "../headers/cmd.h"

void test_rw_bw()
{$;
    //test1
    head("Byte w/r");
    Byte b1 = 0x0b;
    b_write(2, b1);
    printf("\n%02hhx = %02hhx\n", b_read(2), b1);

    //test2
    head("Word w/r");
    Word w1 = 0xACAB;
    w_write(4, w1);
    printf("\n%02hx = %02hx\n", w_read(4), w1);

    //test3
    head("Byte write Word read");
    Byte b2 = 0xcd;
    Byte b3 = 0xab;

    b_write(6, b2);
    b_write(7, b3);
    printf("\n%04hx = %02hhx%02hhx\n", w_read(6), b3, b2);

    //test3
    head("Word w/r");
    Word w2 = 0x0a0b;
    w_write(8, w2);
    printf("\n%04hx = %04hx\n", w_read(8), w2);

    //test4
    head("little/big endian");
    uint16_t x = 1; /* 0x0001 */
    printf("%s\n", *((uint8_t *) &x) == 0 ? "big-endian" : "little-endian");

$$;}

void test_argv(int argc, const char ** argv)
{$;
    for(int i = 0; i <argc; i++)
        printf("%s\n", argv[i]);
$$;}

void test_file(const char * filename)
{$;
    load_file(filename);
    mem_dump(64, 2);
$$;}

void test_run(const char * filename)
{$;
   load_file(filename);
   mem_dump(01000, 6);
   run();
$$;}




void head(const char * msg)
{
    static uint16_t counter;
    counter++;
    //printf("\n-----------------------%s test%d------------------------\n", msg, counter);
}

void DBG(const char * file, const char * func, int line, int relay)
{
    static int lvl = 0;

    if(relay == 1)
    {
        lvl++;
        printf("%11s [%02d]%*s >>> %s\n", file, line, 4 * lvl, "", func);
    }
    else if(relay == 2)
    {
        printf("%*s", 4*lvl + 22, "");
    }
    else
    {
        lvl--;
    }
}