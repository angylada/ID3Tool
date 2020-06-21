#include <stdbool.h>

#ifndef C_TEST_HEXOPS_H
#define C_TEST_HEXOPS_H

#endif //C_TEST_HEXOPS_H

#define REV(n) ((n << 24) | (((n>>16)<<24)>>16) | (((n<<16)>>24)<<16) | (n>>24))

bool isEqual(unsigned const char* val, unsigned char* comparestring);
bool isEqualHex(unsigned const char* val, unsigned int comparehex, int bytecount);