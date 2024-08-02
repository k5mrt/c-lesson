#include "clesson.h"
#include <assert.h>

/*
cc cl_getc.c int_parser_getc.c
*/

enum Type {
    NUMBER,
    SPACE
};
char parse_one(int last_c, int *out_val, enum Type *out_type) {
}

int main() {
    int answer1 = 0;
    int answer2 = 0;

    // write something here.

    // sample for cl_getc() usage.
    int c;

    while((c = cl_getc()) != EOF) {
        printf("%c\n",c );
    }

    // verity result.
    assert(answer1 == 123);
    assert(answer2 == 456);

    return 0;


}