/*
  calc.c -- a simple interactive calculator in C

  This is a simple interactive calculator intended as a PoC for compiling a
  "real world" program for the MOS 6502 using llvm-mos (see
  https://github.com/llvm-mos/llvm-mos-sdk).

  - Adapted from https://github.com/BaseMax/CRecursive-DescentParser
 */

#include "util.h"
#include <stdio.h>
#include <stdlib.h>

// constants
const BYTE BUF_SZ = 0x80;

// global variables
static ASCIIZ buf;

// function prototypes
WORD parseNumber();
WORD parseFormulae();
WORD parseProduct();
WORD parseFactor();
void readInput();
void printResult(WORD result);

// program entry point
int main() {
  WORD result;
  buf = malloc(BUF_SZ);

  for (;;) {
    printStr("CALC> ");
    readInput();

    result = parseFormulae();

    printResult(result);
  }

  return 0;
}

void printResult(WORD result) {
  ustoa(result, buf, 10);
  puts(buf);
}

void readInput() {
  char c;
  BYTE i = 0;

  // read from stdin until newline or buffer full, skipping whitespace
  do {
    c = getchar();

    if (c == '\n') break;

    if (c != ' ' && c != '\0') {
      buf[i++] = c;
    }
  }
  while (i != BUF_SZ-1);

  buf[i] = '\0';
}

WORD parseFormulae() {
  WORD left = parseProduct();

  while (*buf == '+') {
    ++buf;
    WORD right = parseProduct();
    left = left + right;
  }

  while (*buf == '-') {
    ++buf;
    WORD right = parseProduct();
    left = left - right;
  }

  return left;
}

WORD parseProduct() {
  WORD left = parseFactor();

  while (*buf == '*') {
    ++buf;
    WORD right = parseFactor();
    left = left * right;
  }

  while (*buf == '/') {
    ++buf;
    WORD right = parseFactor();
    if(right == 0) {
      puts("CANNOT DIVIDE BY ZERO");
      return left;
    }
    left = left / right;
  }

  return left;
}

WORD parseNumber() {
  WORD number = 0;

  while(*buf >= '0' && *buf <= '9') {
    number = number * 10;
    number = number + *buf - '0';
    ++buf;
  }

  return number;
}

WORD parseFactor() {
  if (*buf >= '0' && *buf <= '9')
    return parseNumber();

  if (*buf == '(') {
    ++buf; // except '('
    WORD sum = parseFormulae();
    ++buf; // except ')'
    return sum;
  }

  printStr("EXPECTED DIGIT BUT FOUND '");
  printStr(buf);
  puts("'");

  return 0;
}
