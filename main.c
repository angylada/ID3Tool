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

int main() {
    char filename[50];
    puts("STATE FILENAME TO READ");
    strcpy(filename, "Kuroneko - Uso No Hibana.mp3");
    filename[strcspn(filename, "\n\r")] = 0;

    checkUserInput(filename);

    char *completefilepath;
    completefilepath = malloc(strlen(filename) + strlen(PATH_TO_FILES));
    sprintf(completefilepath, "%s%s", PATH_TO_FILES, filename);

    errno = 0;
    FILE *fptr;

    fptr = openFile(completefilepath);

    unsigned char buffer[3];

    // GET ID3 HEADER
    fread(buffer, 1, 3, fptr);
    //printf("CONTENT: '%s'\n", buffer);
    fseek(fptr, 7, SEEK_CUR);

    unsigned char framenamebuf[4];
    unsigned char *valbuffer;
    int valuebuffersize = 1024;
    valbuffer = malloc(valuebuffersize);

    for(int i=0; i<=8; i++){
        getFrameData(fptr, framenamebuf, valbuffer, valuebuffersize);
        printf("FRAMENAME: %s\nFRAMEVALUE: %s \n\n", framenamebuf, valbuffer);
    }

}
