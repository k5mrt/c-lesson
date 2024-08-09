#include "clesson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum LexicalType {
    NUMBER,
    SPACE,
    EXECUTABLE_NAME,
    LITERAL_NAME,
    OPEN_CURLY,
    CLOSE_CURLY, 
    END_OF_FILE,
    UNKNOWN
};



struct Token {
    enum LexicalType ltype;
    union {
        int number;
        char onechar;
        char *name;
    } u;
};

#define NAME_SIZE 256

static int is_space(int ch) {
    return ch == ' ';
}

static int is_number(int ch) {
    return '0' <= ch && ch <= '9';
}

static int is_lowercase_alphabet(int ch) {
    return ('a' <= ch && ch <= 'z');
}

static int is_slash(int ch) {
    return ch == '/';
}

static int is_open_curly(int ch) {
    return ch == '{';
}

static int is_close_curly(int ch) {
    return ch == '}';
}

int parse_one(int prev_ch, struct Token *out_token) {
    if(prev_ch == EOF) {
        prev_ch = cl_getc();
        if (prev_ch == EOF) {
            out_token->ltype = END_OF_FILE;
            return EOF;
        }
    }
    if(is_space(prev_ch)) {
        out_token->ltype = SPACE;
        out_token->u.onechar = ' ';
        while(is_space(prev_ch)) {
            prev_ch = cl_getc();
        }
        return prev_ch;
    } else if(is_number(prev_ch)) {
        out_token->ltype = NUMBER;
        out_token->u.number = prev_ch - '0';
        while(is_number(prev_ch)) {
            prev_ch = cl_getc();
            if (!is_number(prev_ch)) {
                break;
            }
            out_token->u.number = out_token->u.number * 10 + (prev_ch - '0');
        }
        return prev_ch;
    } else if(is_lowercase_alphabet(prev_ch) || is_slash(prev_ch)) {
        out_token->u.name = malloc(NAME_SIZE);
        int len = 0;
        if(is_slash(prev_ch)) {
            out_token->ltype = LITERAL_NAME;
            prev_ch = cl_getc();
        } else {
            out_token->ltype = EXECUTABLE_NAME;
        }
        do {
            out_token->u.name[len] = prev_ch;
            len++;
            prev_ch = cl_getc();
        } while(is_lowercase_alphabet(prev_ch));
        out_token->u.name[len] = '\0';
        return prev_ch;
    } else if(is_open_curly(prev_ch)) {
        out_token->ltype = OPEN_CURLY;
        out_token->u.onechar = prev_ch;
        return cl_getc();
    } else if(is_close_curly(prev_ch)) {
        out_token->ltype = CLOSE_CURLY;
        out_token->u.onechar = prev_ch;
        return cl_getc();
    }

    out_token->ltype = UNKNOWN;
    return EOF;
}


void parser_print_all() {
    int ch = EOF;
    struct Token token = {
        UNKNOWN,
        {0}
    };

    do {
        ch = parse_one(ch, &token);
        if(token.ltype != UNKNOWN) {
            switch(token.ltype) {
                case NUMBER:
                    printf("num: %d\n", token.u.number);
                    break;
                case SPACE:
                    printf("space!\n");
                    break;
                case OPEN_CURLY:
                    printf("Open curly brace '%c'\n", token.u.onechar);
                    break;
                case CLOSE_CURLY:
                    printf("Close curly brace '%c'\n", token.u.onechar);
                    break;
                case EXECUTABLE_NAME:
                    printf("EXECUTABLE_NAME: %s\n", token.u.name);
                    break;
                case LITERAL_NAME:
                    printf("LITERAL_NAME: %s\n", token.u.name);
                    break;

                default:
                    printf("Unknown type %d\n", token.ltype);
                    break;
            }
        }
    }while(ch != EOF);
}





static void test_parse_one_number() {
    char *input = "123";
    int expect = 123;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);

    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == NUMBER);
    assert(expect == token.u.number);
}

static void test_parse_one_empty_should_return_END_OF_FILE() {
    char *input = "";
    int expect = END_OF_FILE;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect);
}

static void test_parse_one_executable_name() {
    char* input = "add";
    char* expect_name = "add";
    int expect_type = EXECUTABLE_NAME;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(strcmp(token.u.name, expect_name) == 0);
}

static void test_parse_one_literal_name() {
    char* input = "/some";
    char* expect_name = "some";
    int expect_type = LITERAL_NAME;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(strcmp(token.u.name, expect_name) == 0);
}

static void test_parse_one_open_curly() {
    char* input = "{";
    char expect_onechar = '{';
    int expect_type = OPEN_CURLY;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(token.u.onechar == expect_onechar);
}

static void test_parse_one_close_curly() {
    char* input = "}";
    char expect_onechar = '}';
    int expect_type = CLOSE_CURLY;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(token.u.onechar == expect_onechar);
}

static void test_parse_number_and_space() {
    char* input = "123 45";

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == ' ');
    assert(token.ltype == NUMBER);
    assert(token.u.number == 123);

    ch = parse_one(ch, &token);

    assert(ch == '4');
    assert(token.ltype == SPACE);
    assert(token.u.onechar == ' ');

    ch = parse_one(ch, &token);

    assert(ch == EOF);
    assert(token.ltype == NUMBER);
    assert(token.u.number == 45);
}


static void unit_tests() {
    test_parse_one_empty_should_return_END_OF_FILE();
    test_parse_one_number();
    test_parse_one_executable_name();
    test_parse_one_literal_name();
    test_parse_one_open_curly();
    test_parse_one_close_curly();
    test_parse_number_and_space();
}

int main() {
    unit_tests();

    cl_getc_set_src("123 45 add /some { 2 3 add } def");
    parser_print_all();
    return 0;
}