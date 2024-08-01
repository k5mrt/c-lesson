#include <stdio.h>
#include <assert.h>

static const char* const input = "123 456  1203";


int main() {
    int answer1 = 0;
    int answer2 = 0;
    int answer3 = 0;


    char ascii_eot = 0;
    char ascii_space = 32;
    char ascii_numbers[10] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };

    int answers[3] = { 0, 0, 0 };
    int index = 0;

    // Traverse string, find digits
    int i = 0;
    while (input[i] != ascii_eot) {
        if (input[i] == ascii_space) {
            i++;
            continue;
        };

        for (int current_number = 0; current_number < 10; current_number++) {
            if (input[i] == ascii_numbers[current_number]) {
                answers[index] = answers[index] * 10 + current_number;
                break;
            };
        };

        if (input[i+1] == ascii_space) {
            index++;
        };
        i++;
    };

    answer1 = answers[0];
    answer2 = answers[1];
    answer3 = answers[2];


    // verity result.
    assert(answer1 == 123);
    assert(answer2 == 456);
    assert(answer3 == 1203);

    return 0;
}