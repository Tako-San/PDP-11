#include "pdp.h"

void head();

int main()
{
    //test1
    head();
    byte b1 = 0x0b;
    b_write(2, b1);
    printf("%02hhx = %02hhx\n", b_read(2), b1);

    //test2
    head();
    word w1 = 0xACAB;
    w_write(4, w1);
    printf("%02hx = %02hx\n", w_read(4), w1);

    //test3
    head();
    byte b2 = 0xB0;
    byte b3 = 0xC0;

    b_write(6, b2);
    b_write(7, b3);
    printf("%02hx = %02hhx%02hhx\n", w_read(6), b2, b3);




    return 0;
}

void head()
{
    static uint16_t counter;
    counter++;
    printf("--------------test%d--------------\n", counter);
}