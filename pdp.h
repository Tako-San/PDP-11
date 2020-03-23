#ifndef PDP11
#define PDP11

#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <error.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef word address;

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];


void b_write(address adr, byte b);
byte b_read(address adr);

void w_write(address adr, word w);
word w_read(address adr);

void load_file(const char * filename);
void mem_dump(address start, word n);

#endif //PDP11
