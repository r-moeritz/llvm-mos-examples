#include "types.h"

// memory locations
const WORD VIC = 0xd000;
const WORD NEWVIC1 = 0xc100;
const WORD NEWVIC2 = 0xc12f;
const WORD CIA1ICR = 0xdc0d;
const WORD CIA2ICR = 0xdd0d;
const WORD SCROLY = 0xd011;
const WORD VICIRQ = 0xd019;
const WORD IRQMSK = 0xd01a;
const WORD RASTER = 0xd012;
const WORD BORDER = 0xd020;
const WORD IRQVEC = 0x314;

// values
const BYTE GRAY3 = 15;
const BYTE GREEN = 5;

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

  return 0;
}

void disableAllInterrupts() {
  PTR cia1icr = CIA1ICR;
  PTR cia2icr = CIA2ICR;
  PTR irqmsk = IRQMSK;
  PTR vicirq = VICIRQ;

  *cia1icr = 0x7f;
  *cia2icr = 0x7f;
  *irqmsk = 0;
  *vicirq = 0;

  asm ( "lda $d019\n\t"
        "lda $dc0d\n\t"
        "lda $dd0d" );
}

void copyVicRegisters() {
  PTR vic = VIC + 0x2e;
  PTR newvic1 = NEWVIC1 + 0x2e;
  PTR newvic2 = NEWVIC2 + 0x2e;

  while (vic >= VIC) {
    *newvic1 = *vic;
    --newvic1;
    *newvic2 = *vic;
    --newvic2;
    --vic;
  }
}

void setupInterrupts() {
  PTR vicirq = VICIRQ;
  PTR irqmsk = IRQMSK;
  PTR raster = RASTER;
  PTR scroly = SCROLY;
  PTR newvic1 = NEWVIC1 + 0x11;
  PTR newvic2 = NEWVIC2 + 0x11;
  WPTR irqvec = IRQVEC;

  *irqvec = &handleInterrupt;

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
  PTR raster = RASTER;
  PTR border = BORDER;

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
