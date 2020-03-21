#ifndef PDP11
#define PDP11

#include <stdint.h>
#include <assert.h>
#include <stdio.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef word Adress;

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];


void b_write(Adress adr, byte b);
byte b_read(Adress adr);

void w_write(Adress adr, word w);
word w_read(Adress adr);

void load_file();

#endif //PDP11