#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "./hexOps.h"
#include <errno.h>
#include <netinet/in.h>

//FOR LATER USE
unsigned const int TIT2_TITLE = 0x54495432;
unsigned const int TCON_GENRE = 0x54434f4e;
unsigned const int ID3_ID = 0x494433;

FILE* openFile(char* filepath)
{
    FILE *fptr = fopen(filepath, "rb");
    if(fptr == NULL) {
        printf("Error opening file '%s', error '%d'", filepath, errno);
        exit(1);
    }
    return fptr;
}

void moveStartingNullToEnd(unsigned char* chararray)
{
    chararray[0] = '_';
    unsigned char tmp[strlen(chararray)];
    memset(tmp, 0, strlen(chararray));

    for(int i = 0; i < strlen(chararray) -1; i++) {
        tmp[i] = chararray[i+1];
    }
    strcpy(chararray, tmp);
}

bool getFrameData(FILE* fptr, int *framenamelen, unsigned char *framenamebuf, unsigned char* tagvalue, int tagvaluesize)
{
    // GET FRAME NAME
    fread(framenamebuf, 1, (*framenamelen) - 1, fptr);

    if (strlen(framenamebuf) == 0) {
        return false;
    }
    // GET FRAME SIZE
    unsigned int vallen;
    fread(&vallen, 4, 1, fptr);

    // INT VALUE NEEDS TO BE REVERSED
    // OTHERWISE 0x0000000e (14) becomes 0x0e000000 (234881024)
    unsigned int correctvallen = ntohl(vallen);
    // GET FRAME VALUE
    fseek(fptr, 2, SEEK_CUR);
    memset(tagvalue, 0, tagvaluesize);
    fread(tagvalue, 1, correctvallen, fptr);
    if (tagvalue[0] == '\0') {
        moveStartingNullToEnd(tagvalue);
    }
    return true;
}


void getId3v2Revision(FILE* fptr, int *buf)
{
    unsigned char id3identifierbuffer[3];
    fread(id3identifierbuffer, 1, 3, fptr);

    if (!isEqualHex(id3identifierbuffer, ID3_ID, 3)) {
        *buf = -1;
    }

    unsigned int id3versionbuffer;
    fread(&id3versionbuffer, 1, 2, fptr);
    *buf = (int)id3versionbuffer;
}

bool extendedHeader(FILE* fptr)
{
    unsigned char flagbyte ;
    fread(&flagbyte, 1, 1, fptr);

    return (flagbyte >> 6) & 0x1;
}

void getsizehdr(FILE* fptr, unsigned int* dst)
{
    unsigned int len;
    fread(&len, 1, 4, fptr);
    *dst = ntohl(len);
}