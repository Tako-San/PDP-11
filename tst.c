#include "pdp.h"
#include "tst.h"


void head();

void test1()
{$;
    //test1
    head();
    byte b1 = 0x0b;
    b_write(2, b1);
    //printf("\n%02hhx = %02hhx\n", b_read(2), b1);

    //test2
    head();
    word w1 = 0xACAB;
    w_write(4, w1);
    //printf("\n%02hx = %02hx\n", w_read(4), w1);

    //test3
    head();
    byte b2 = 0xcd;
    byte b3 = 0xab;

    b_write(6, b2);
    b_write(7, b3);
    //printf("\n%04hx = %02hhx%02hhx\n", w_read(6), b3, b2);

    //test3
    head();
    word w2 = 0x0a0b;
    w_write(8, w2);
    //printf("\n%04hx = %04hx\n", w_read(8), w2);

    //test4
    head();
    uint16_t x = 1; /* 0x0001 */
    //printf("%s\n", *((uint8_t *) &x) == 0 ? "big-endian" : "little-endian");

$$;}

void head()
{$;
    static uint16_t counter;
    counter++;
    //printf("\n-----------------------test%d------------------------\n", counter);
$$;}