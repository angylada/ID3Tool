#include <string.h>
#include "./fileReader.h"
#include "./hexOps.h"
#include <stdbool.h>

// FOR LATER USE
bool isEqual(unsigned const char* val, unsigned char* comparestring)
{
    for (int i=0;i< strlen(comparestring);i++) {
        if (val[i] != comparestring[i]) {
            return 0;
        }
    }
    return 1;
}

// FOR LATER USE
bool isEqualHex(unsigned const char* val, unsigned int comparehex, int bytecount)
{
    for (int i=0; i < bytecount; i++) {
        unsigned char singlehexval;
        if(i==0) singlehexval=(comparehex & 0xFF);
        else singlehexval=((comparehex >> i * 8) & 0xFF);

        if(singlehexval != val[bytecount - 1 - i]){
            return 0;
        }
    }
    return 1;
}
