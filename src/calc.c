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
const int BUF_SZ = 100;

// global variables
char *buf;

// function prototypes
unsigned short parseNumber();
unsigned short parseFormulae();
unsigned short parseProduct();
unsigned short parseFactor();
void readInput();

// program entry point
int main() {
  unsigned short result;
  buf = malloc(sizeof(char) * BUF_SZ);

  for (;;) {
    printStr("CALC> ");
    readInput();

    result = parseFormulae();
    ustoa(result, buf, 10);

    puts(buf);
  }

  return 0;
}

void readInput() {
  for (char i = 0; i != BUF_SZ; ++i) {
    buf[i] = getchar();
    if (buf[i] == '\n') {
      break;
    }
  }
}

unsigned short parseFormulae() {
  unsigned short left = parseProduct();

  while (*buf == '+') {
    ++buf;
    unsigned short right = parseProduct();
    left = left + right;
  }

  while (*buf == '-') {
    ++buf;
    unsigned short right = parseProduct();
    left = left - right;
  }

  return left;
}

unsigned short parseProduct() {
  unsigned short left = parseFactor();

  while (*buf == '*') {
    ++buf;
    unsigned short right = parseFactor();
    left = left * right;
  }

  while (*buf == '/') {
    ++buf;
    unsigned short right = parseFactor();
    if(right == 0) {
      puts("CANNOT DIVIDE BY ZERO");
      return left;
    }
    left = left / right;
  }

  return left;
}

unsigned short parseNumber() {
  unsigned short number = 0;

  while(*buf >= '0' && *buf <= '9') {
    number = number * 10;
    number = number + *buf - '0';
    ++buf;
  }

  return number;
}

unsigned short parseFactor() {
  if (*buf >= '0' && *buf <= '9')
    return parseNumber();

  if (*buf == '(') {
    ++buf; // except '('
    unsigned short sum = parseFormulae();
    ++buf; // except ')'
    return sum;
  }

  printStr("EXPECTED DIGIT BUT FOUND ");
  puts(buf);
  return *buf;
}
