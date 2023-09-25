#include "lexer.h"
#include "parser.h"
#include "visitors/compiler.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    char *output = "out.s";
    char *source;


    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input> [output]", argv[0]);
        exit(1);
    }
    if (argc > 2) {
        output = argv[2];
    }

    FILE* input = fopen(argv[1], "r");

    if (input == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    source = (char*)malloc(file_size + 1);

    if (source == NULL) {
        perror("Error allocating memory");
        fclose(input);
        return 1;
    }

    size_t bytes_read = fread(source, 1, file_size, input);

    if (bytes_read != file_size) {
        perror("Error reading file");
        fclose(input);
        free(source);
        return 1;
    }

    fclose(input);

    source[file_size - 1] = ' ';
    source[file_size]     = '\0';

    load_string(source);

    setup_compiler(output);
    compile();
    teardown_compiler();
    return 0;
}