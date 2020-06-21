#include <stdio.h>

#ifndef C_TEST_FILE_READER_H
#define C_TEST_FILE_READER_H

#endif //C_TEST_FILE_READER_H


FILE* openFile(char* filepath);
void getFrameData(FILE* fptr, unsigned char *framenamebuf, unsigned char* tagvalue, int tagvaluesize);