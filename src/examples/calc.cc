#include "examples/calc.hh"
#include "util.h"
#include <stdio.h>

// ==================================================
//                     main
// ==================================================

// function prototypes
void printResult(WORD result, ASCIIZ buffer);

int main() {
  WORD result;
  examples::Calculator calc;
  char buf[10];

  for (;;) {
    printStr("CALC> ");
    result = calc.parseFormulae();
    printResult(result, buf);
  }

  return 0;
}

void printResult(WORD result, ASCIIZ buffer) {
  ustoa(result, buffer, 10);
  puts(buffer);
}

// ==================================================
//                   calculator
// ==================================================

examples::Calculator::Calculator()
  : m_pBuf(new char[BUFFER_SIZE]) {}

examples::Calculator::~Calculator() {
  delete[] m_pBuf;
}

void examples::Calculator::readInput() {
  char c;
  BYTE i = 0;

  // read from stdin until newline or buffer full, skipping whitespace
  do {
    c = getchar();

    if (c == '\n') break;

    if (c != ' ' && c != '\0') {
      m_pBuf[i++] = c;
    }
  }
  while (i != BUFFER_SIZE-1);

  m_pBuf[i] = '\0';
}

WORD examples::Calculator::parseFormulae() {
  readInput();
  WORD left = parseProduct();

  while (*m_pBuf == '+') {
    ++m_pBuf;
    WORD right = parseProduct();
    left = left + right;
  }

  while (*m_pBuf == '-') {
    ++m_pBuf;
    WORD right = parseProduct();
    left = left - right;
  }

  return left;
}

WORD examples::Calculator::parseProduct() {
  WORD left = parseFactor();

  while (*m_pBuf == '*') {
    ++m_pBuf;
    WORD right = parseFactor();
    left = left * right;
  }

  while (*m_pBuf == '/') {
    ++m_pBuf;
    WORD right = parseFactor();
    if(right == 0) {
      puts("CANNOT DIVIDE BY ZERO");
      return left;
    }
    left = left / right;
  }

  return left;
}

WORD examples::Calculator::parseNumber() {
  WORD number = 0;

  while(*m_pBuf >= '0' && *m_pBuf <= '9') {
    number = number * 10;
    number = number + *m_pBuf - '0';
    ++m_pBuf;
  }

  return number;
}

WORD examples::Calculator::parseFactor() {
  if (*m_pBuf >= '0' && *m_pBuf <= '9')
    return parseNumber();

  if (*m_pBuf == '(') {
    ++m_pBuf; // except '('
    WORD sum = parseFormulae();
    ++m_pBuf; // except ')'
    return sum;
  }

  printStr("EXPECTED DIGIT BUT FOUND '");
  printStr(m_pBuf);
  puts("'");

  return 0;
}
