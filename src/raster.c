#include "types.h"

// memory locations
#define VIC 0xd000
#define NEWVIC1 0xc100
#define NEWVIC2 0xc12f
#define CIA1ICR 0xdc0d
#define CIA2ICR 0xdd0d
#define SCROLY 0xd011
#define VICIRQ 0xd019
#define IRQMSK 0xd01a
#define RASTER 0xd012
#define BORDER 0xd020
#define IRQVEC 0x314

// values
#define GRAY3 15
#define GREEN 5

// global variables
static PTR irqmsk = IRQMSK;
static PTR vicirq = VICIRQ;
static PTR raster = RASTER;
static PTR cia1icr = CIA1ICR;
static PTR cia2icr = CIA2ICR;
static PTR irqvec = IRQVEC;
static PTR scroly = SCROLY;
static PTR border = BORDER;

// function prototypes
void disableAllInterrupts();
void copyVicRegisters();
void setupInterrupts();
void handleInterrupt() __attribute__ ((noreturn));

int main() {
  asm ( "sei" );
  disableAllInterrupts();
  copyVicRegisters();
  setupInterrupts();
  asm ( "cli" );
}

void disableAllInterrupts() {
  *cia1icr = 0x7f;
  *cia2icr = 0x7f;
  *irqmsk = 0;
  *vicirq = 0;

  asm ( "lda %0\n\t"
        "lda %1\n\t"
        "lda %2\n\t"
        : // no outputs
        : "m" (vicirq), "m" (cia1icr), "m" (cia2icr) // inputs
        : "a" // clobbers
        );
}

void copyVicRegisters() {
  BYTE offset = 0x2e;
  PTR vic = VIC + offset;
  PTR newvic1 = NEWVIC1 + offset;
  PTR newvic2 = NEWVIC2 + offset;

  while (vic >= VIC) {
    *newvic1-- = *vic;
    *newvic2-- = *vic--;
  }
}

void setupInterrupts() {
  *irqvec++ = (WORD)&handleInterrupt & (WORD)0xff;
  *irqvec = (WORD)&handleInterrupt >> (WORD)8;

  PTR newvic1 = NEWVIC1 + 0x11;
  PTR newvic2 = NEWVIC2 + 0x11;

  *scroly &= 0x7f;
  *newvic1 = *scroly;
  *newvic2 = *scroly;

  newvic1 = NEWVIC1 + 0x12;
  *newvic1 = 148;

  newvic2 = NEWVIC2 + 0x12;

  *raster = 1;
  *newvic2 = 1;

  newvic1 = NEWVIC1 + 0x19;
  newvic2 = NEWVIC2 + 0x19;

  *newvic1 = 0x81;
  *newvic2 = 0x81;

  newvic1 = NEWVIC1 + 0x1a;
  newvic2 = NEWVIC2 + 0x1a;

  *newvic1 = 0x81;
  *newvic2 = 0x81;

  *vicirq = 0x81;
  *irqmsk = 0x81;
}

void handleInterrupt() {
  BYTE vicOffset = 0;
  BYTE newvicOffset = 0x2e + 47;

  if (*raster > 148) {
    newvicOffset = 0x2e;
    vicOffset = 0x2e;
  }

  PTR newvic = NEWVIC1 + newvicOffset;
  PTR vic = VIC + vicOffset;

  while (vic >= VIC) {
    *vic-- = *newvic--;
  }

  if (newvic == NEWVIC1) {
    *border = GRAY3;
    asm ( "jmp $ea31" );
  }
  else {
    *border = GREEN;
    asm ( "jmp $ea81" );
  }
}
