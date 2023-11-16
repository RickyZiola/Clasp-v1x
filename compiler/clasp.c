#include "lexer.h"
#include "parser.h"
#include "visitors/compiler.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    char *output = "out.s";  // output file
    char *source;            // source code


    if (argc < 2) {  // No arguments
        fprintf(stderr, "Usage: %s <input> [output]", argv[0]);
        exit(1);  // argv[0] is the command name, this allows for renamed executables without changing the code
    }
    if (argc > 2) {  // >2 arguments, we have a specified output
        output = argv[2];
    }

    FILE* input = fopen(argv[1], "r");  // Open the input file

    if (input == NULL) {  // Oh no
        perror("Error opening file");
        return 1;
    }

    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    source = (char*)malloc(file_size + 2);  // Allocate a buffer for the file contents

    if (source == NULL) {   // Allocation failure
        perror("Error allocating memory");
        fclose(input);  // Close the file, no resource leaks here
        return 1;
    }

    size_t bytes_read = fread(source, 1, file_size, input);  // Read the file

    if (bytes_read != file_size) {  // How would this even happen lols
        perror("Error reading file");
        fclose(input);
        free(source);  // Clean up our resources
        return 1;
    }

    fclose(input);  // Close the file

    source[file_size    ] =  ' '; // For whatever reason, the lexer requires whitespace after the program,
    source[file_size + 1] = '\0';   // so add it here.

    load_string(source);  // Load the string into the lexer buffer

    setup_compiler(output);  // Initialize the compiler buffers (hash tables, etc.) and its output file
    compile();               // Compile the program
    teardown_compiler();     // Free the compiler resources
    return 0;
}