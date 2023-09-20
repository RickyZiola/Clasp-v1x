#include "../lexer.h"
#include "../parser.h"
#include "../visitors/compiler.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    load_string(" 15 - 1 * (213 + 5) ");
    setup_compiler("TEMP.s");
    compile();
    return 0;
}