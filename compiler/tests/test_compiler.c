#include "../lexer.h"
#include "../parser.h"
#include "../visitors/compiler.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    load_string("#fNOFILE.csp var test: int ");
    setup_compiler("TEMP.s");
    compile();
    teardown_compiler();
    return 0;
}