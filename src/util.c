/*
  util.c -- misc. utility functions

  This is a collection of miscellaneous utility functions.

  - reverse and ustoa adapted from https://www.geeksforgeeks.org/implement-itoa
*/

#include <stdio.h>

// Write str to stdout without appending a newline
void printStr(const char* s) {
  const char* sc = s;
  while (*sc) {
    __putchar(*sc++);
  }
}

// Reverse [str, str+length-1] in-place
void reverse(char* str, unsigned short length) {
  unsigned short start = 0;
  unsigned short end = length -1;
  char temp;

  while (start < end) {
    temp = *(str+start);
    *(str+start) = *(str+end);
    *(str+end) = temp;

    start++;
    end--;
  }
}

// itoa adapted for unsigned short
char* ustoa(unsigned short num, char* str, char base) {
  unsigned short i = 0;

  // Handle 0 explicitly, otherwise empty string is printed for 0
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // Process individual digits
  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
    num = num/base;
  }

  str[i] = '\0'; // Append string terminator

  // Reverse the string
  reverse(str, i);

  return str;
}
