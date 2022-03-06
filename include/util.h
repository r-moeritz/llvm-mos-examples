#ifndef UTIL__H
#define UTIL__H

// Write str to stdout without appending a newline
void printStr(const char* str);

// Reverse [str, str+length-1] in-place
void reverse(char* str, unsigned short length);

// itoa adapted for unsigned short
char* ustoa(unsigned short num, char* str, char base);

#endif // #ifndef UTIL__H
