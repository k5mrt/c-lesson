#include "clesson.h"
#include <string.h>

static char* input;
static int pos = 0;


int cl_getc() {
    if(strlen(input) == pos)
        return EOF;
    return input[pos++];
}

void cl_getc_set_src(char* str) {
    input = str;
    pos = 0;
}
