#include "../lexer.h"
#include "../parser.h"
#include "../visitors/compiler.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *outf = fopen("out.ice", "wb");

    compiler_init();

    load_string("32 - 28 + -5");
    expression();
    printf("%u\n", compiler_get_compiled_size());
    fwrite(compiler_get_compiled(), compiler_get_compiled_size(), 1, outf);
    fclose(outf);
    return 0;
}