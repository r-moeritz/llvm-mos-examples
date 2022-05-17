#ifndef UTIL__H
#define UTIL__H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Write str to stdout without appending a newline
void printStr(const ASCIIZ str);

// Reverse [str, str+length) in-place
void reverse(ASCIIZ str, BYTE length);

// itoa adapted for unsigned short
ASCIIZ ustoa(WORD num, ASCIIZ str, BYTE base);

#ifdef __cplusplus
}
#endif

#endif // #ifndef UTIL__H
