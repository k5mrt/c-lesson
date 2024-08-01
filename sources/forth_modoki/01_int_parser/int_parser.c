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

    int reversed_answers[3] = { 0, 0, 0 };
    int index = 0;
    int digit = 0;

    // Traverse string, find digits, convert to reversed number, store in reversed_answers
    int i = 0;
    while (input[i] != ascii_eot) {
        if (input[i] == ascii_space) {
            i++;
            continue;
        };

        for (int current_number = 0; current_number < 10; current_number++) {
            if (input[i] == ascii_numbers[current_number]) {
                digit++;
                int pow_of_number = 1;
                for (int current_digit = 1; current_digit < digit; current_digit++) {
                    pow_of_number *= 10;
                };
                reversed_answers[index] += pow_of_number * current_number;
                break;
            };
        };

        if (input[i+1] == ascii_space) {
            index++;
            digit = 0;
        };
        i++;
    };

    // Reverse number of reversed_answers number
    int answers[3] = { 0, 0, 0 };
    for (int i = 0; i < 3; i++) {
        int answer = 0;
        while (reversed_answers[i] != 0) {
            int digit = reversed_answers[i] % 10;
            answer = answer * 10 + digit;
            reversed_answers[i] /= 10;
        };
        answers[i] = answer;
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