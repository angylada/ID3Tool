#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./fileReader.h"
#include "./hexOps.h"
#include <errno.h>
#include <regex.h>

const char* PATH_TO_FILES="../";


void checkUserInput(char *input)
{
    regex_t rebuffer;
    regmatch_t match;
    regcomp(&rebuffer, ".*\\.mp3", REG_EXTENDED);
    int matches = regexec(&rebuffer, input, 1, &match, 0);

    if (matches == 1) {
        printf("Input '%s' does not contain .mp3 extension", input);
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    char filename[50];
    if (argc != 2) {
        puts("STATE FILENAME TO READ");
        fgets(filename, sizeof(filename), stdin);
    } else {

        strncpy(filename, argv[1], sizeof(filename));
    }

    filename[strcspn(filename, "\n\r")] = 0;

    checkUserInput(filename);

    char *completefilepath;
    completefilepath = malloc(strlen(filename) + strlen(PATH_TO_FILES) +1);
    sprintf(completefilepath, "%s%s\0", PATH_TO_FILES, filename);

    errno = 0;
    FILE *fptr;

    fptr = openFile(completefilepath);

    int revision;
    getId3v2Revision(fptr, &revision);

    if (revision == -1) {
        fprintf(stderr, "Format is not ID3");
        exit(9);
    }
    printf("ID3VERSION: ID3v2.%d\n\n", revision);

    bool hasextendedheader = extendedHeader(fptr);
    if (hasextendedheader) {
        //skipextendedheader();
    }

    unsigned int sizehdr;
    getsizehdr(fptr, &sizehdr);

    int framenamelen;
    framenamelen = 5;
    if(revision < 3) {
        framenamelen = 4;
    }
    unsigned char framenamebuf[framenamelen];
    memset(framenamebuf, 0, sizeof(framenamebuf));

    unsigned char *valbuffer;
    int valuebuffersize = 1024;
    valbuffer = malloc(valuebuffersize);

    for(int i=0; i<=5; i++){
        memset(valbuffer, 0, valuebuffersize);
        memset(framenamebuf, 0, framenamelen);
        getFrameData(fptr, &framenamelen, framenamebuf, valbuffer, valuebuffersize);

        printf("FRAMENAME: %s\nFRAMEVALUE: %s \n\n", framenamebuf, valbuffer);
    }

}
