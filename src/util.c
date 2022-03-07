/*
  util.c -- misc. utility functions

  This is a collection of miscellaneous utility functions.

  - reverse and ustoa adapted from https://www.geeksforgeeks.org/implement-itoa
*/

#include "types.h"
#include <stdio.h>

// Write str to stdout without appending a newline
void printStr(const ASCIIZ str) {
  while (*str) {
    __putchar(*str++);
  }
}

// Reverse [str, str+length) in-place
void reverse(ASCIIZ str, BYTE length) {
  BYTE start = 0;
  BYTE end = length - 1;
  BYTE temp;

  while (start < end) {
    temp = *(str+start);
    *(str+start) = *(str+end);
    *(str+end) = temp;

    ++start;
    --end;
  }
}

// itoa adapted for unsigned short
char* ustoa(WORD num, ASCIIZ str, BYTE base) {
  BYTE i = 0;

  // Handle 0 explicitly, otherwise empty string is printed for 0
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // Process individual digits
  while (num != 0) {
    BYTE rem = num % base;
    str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
    num = num / base;
  }

  str[i] = '\0'; // Append string terminator

  // Reverse the string
  reverse(str, i);

  return str;
}
