#ifndef PDP11
#define PDP11

#include <assert.h>
#include <stdio.h>
#include <error.h>

#include <stdint.h>
#include <stdarg.h>

typedef uint8_t Byte;
typedef uint16_t Word;
typedef Word Adr;

#define MEMSIZE (64*1024)

Byte mem[MEMSIZE];


void b_write(Adr adr, Byte b);
Byte b_read(Adr adr);

void w_write(Adr adr, Word w);
Word w_read(Adr adr);

void load_file(const char * filename);
void mem_dump(Adr start, Word n);

#endif //PDP11
