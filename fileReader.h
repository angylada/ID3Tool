#include <stdio.h>
#include <stdbool.h>

#ifndef C_TEST_FILE_READER_H
#define C_TEST_FILE_READER_H

#endif //C_TEST_FILE_READER_H


FILE* openFile(char* filepath);
void getFrameData(FILE* fptr, int *framenamelen, unsigned char *framenamebuf, unsigned char* tagvalue, int tagvaluesize);
void getId3v2Revision(FILE* fptr, int *buf);
bool extendedHeader(FILE* fptr);
void getsizehdr(FILE* fptr, unsigned int* dst);