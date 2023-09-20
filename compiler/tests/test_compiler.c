#include "../lexer.h"
#include "../parser.h"
#include "../visitors/compiler.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    load_string("32 - 28 + -5");
    printf("\n");
    expression();
    printf("\n");
    return 0;
}