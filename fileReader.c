#include <string.h>
#include <stdio.h>
#include "./hexOps.h"
#include <errno.h>

//FOR LATER USE
unsigned const int TIT2_TITLE = 0x54495432;
unsigned const int TCON_GENRE = 0x54434f4e;

FILE* openFile(char* filepath)
{
    FILE *fptr = fopen(filepath, "rb");
    if(fptr == NULL) {
        printf("Error opening file '%s', error '%d'", filepath, errno);
        exit(1);
    }
    return fptr;
}

void getFrameData(FILE* fptr, unsigned char *framenamebuf, unsigned char* tagvalue, int tagvaluesize)
{
    // GET FRAME NAME
    fread(framenamebuf, 1, 4, fptr);

    // GET FRAME SIZE
    unsigned int vallen;
    fread(&vallen, 4, 1, fptr);

    // INT VALUE NEEDS TO BE REVERSED
    // OTHERWISE 0x0000000e (14) becomes 0x0e000000 (234881024)
    unsigned int correctvallen = REV(vallen);


    // GET FRAME VALUE
    fseek(fptr, 3, SEEK_CUR);
    memset(tagvalue, 0, tagvaluesize);
    fread(tagvalue, 1, correctvallen-1, fptr);
}