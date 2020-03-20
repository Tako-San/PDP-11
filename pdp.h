#ifndef PDP11
#define PDP11

#include <stdint.h>
#include <assert.h>
#include <stdio.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef word Adress;

/*uint64_t Lvl = 0;

#define $   Lvl++;                                                               \
            printf("\n%s [%02d]%*s >>> %s\n", __FILE__, 4 * Lvl, "", __LINE__);

#define return(thing)   Lvl--;       \
                        return thing \
*/

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];


void b_write(Adress adr, byte b);
byte b_read(Adress adr);

void w_write(Adress adr, word w);
word w_read(Adress adr);

void load_file();


#endif //PDP11