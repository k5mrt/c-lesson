#include "clesson.h"
#include <assert.h>

/*
cc cl_getc.c int_parser_getc.c
*/

const char ascii_numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

enum Type {
    NUMBER,
    SPACE
};
char parse_one(int last_c, int *out_val, enum Type *out_type) {
    int val;
    enum Type type;

    if(last_c == ' ') {
        while(last_c == ' ') {
            last_c = cl_getc();
        }
        type = SPACE;
        val = ' ';
    } else {
        val = 0;
        for(int i = 0; i < 10; i++) {
            if(last_c == ascii_numbers[i]) {
                val = i;
                break;
            }
        }
        while(last_c != ' ') {
            last_c = cl_getc();
            if (last_c == EOF) {
                break;
            }
            for(int i = 0; i < 10; i++) {
                if(last_c == ascii_numbers[i]) {
                    val = val * 10 + i;
                    break;
                }
            }
        }
        type = NUMBER;
    }

    *out_val = val;
    *out_type = type;

    return last_c;
}

int main() {
    int answer1 = 0;
    int answer2 = 0;

    // write something here.

    int answers[2] = {0, 0};
    int answer_index = 0;

    int next_c = cl_getc();
    while(next_c != EOF) {
        int out_val;
        enum Type out_type;
        next_c = parse_one(next_c, &out_val, &out_type);
        if(out_type == NUMBER) {
            answers[answer_index] = out_val;
            answer_index++;
        }
    }

    answer1 = answers[0];
    answer2 = answers[1];

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