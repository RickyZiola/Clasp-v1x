#include "../visitor.h"
#include "compiler.h"
#include "ICE.h"
#include "../parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../common/hash_table.h"

static FILE *outf;
static HashTable *variable_ht;

static int num_globals = 0;

void setup_compiler(const char *fname) {
    outf = fopen(fname, "wb");
    variable_ht = createHashTable();
}
void teardown_compiler() {
    fclose(outf);
    freeHashTable(variable_ht);
}

void visitor_num_literal(void *val, Type *type) {
    // This value is NOT loaded into the data segment for faster access times.
    // In the case of string/list/obj literals, they are loaded into the data segment.

    // ICE assembly for loading a constant onto the stack:
    //               ; Initial,        stack = [ ]
    // const.i <n>   ; Constnant load, stack = [n]

    if (strncmp(type->final, "int", 3) == 0)
        fprintf(outf, "const.i %d\n", *((int *)  val));  // Integers
    else if (strncmp(type->final, "float", 5) == 0)
        fprintf(outf, "const.r %f\n", *((float *)val));  // Real numbers (floats)
    else {
        fprintf(stderr, "Compile error: Unknown numeric type \"%s\"", type->final);
        exit(-1);
    }
        
}
void visitor_op_unary(TokenTyp operator_type) {
    switch (operator_type) {
        case TOKEN_MINUS: {
            // TODO: type checking

            // ICE assembly for negating a value on the stack:
            //             ; Initial,         stack = [n  ]
            // const.0     ; Load a constant, stack = [n 0]
            // swap        ; Swap 2 vals,     stack = [0 n]
            // sub.i       ; Subtract,        stack = [0-n]

            // This is equivalent to 0 - n, or just -n

            fprintf(outf, "const.0\nswap\nsub.i\n");
        } break;
        case TOKEN_BANG: {
            // TODO: type checking

            // ICE assembly for a bitwise NOT:
            //              ; Initial,     stack = [n ]
            // not          ; Bitwise NOT, stack = [!n]

            // This is !n
            fprintf(outf, "not\n");
        } break;
        default: {
            fprintf(stderr, "Compile error: Unknown unary operator\n");
            exit(-1);
        }
    }
}

void visitor_op_binary(TokenTyp operator_type) {
    // TODO: bitwise operators
    switch (operator_type) {
        case TOKEN_PLUS: {
            // TODO: type checking

            // ICE assembly for adding 2 numbers:
            //          ; Initial,  stack = [n m]
            // add.i    ; Addition, stack = [n+m]

            // This is n+m
            fprintf(outf, "add.i\n");
        } break;
        case TOKEN_MINUS: {
            // TODO: type checking

            // ICE assembly for subtracting 2 numbers:
            //          ; Initial,     stack = [n m]
            // sub.i    ; Subtraction, stack = [n-m]

            // This is n-m
            fprintf(outf, "sub.i\n");
        } break;
        case TOKEN_ASTERIX: {
            // TODO: type checking

            // ICE assembly for multiplying 2 numbers:
            //          ; Initial,        stack = [n m]
            // mul.i    ; Multiplication, stack = [n*m]

            // This is n*m
            fprintf(outf, "mul.i\n");
        } break;
        case TOKEN_SLASH: {
            // TODO: type checking

            // ICE assembly for dividing 2 numbers:
            //          ; Initial,  stack = [n m]
            // div.i    ; Division, stack = [n/m]

            // This is n/m
            fprintf(outf, "div.i\n");
        } break;
        default: {
            fprintf(stderr, "Compile error: unknown binary operator\n");
            exit(-1);
        }
    }
}

void visitor_var_decl(Token name, Type *typ) {
    // Assume the initializer is already on the stack
    char *name_str = malloc(name.length+1);
    memcpy(name_str, name.str, name.length);
    name_str[name.length] = '\0';
    insert(variable_ht, name_str, num_globals);

    fprintf(outf, "global.w %u\n", num_globals++);
}
void visitor_var_read(Token name) {
    char *name_str = malloc(name.length+1);
    memcpy(name_str, name.str, name.length);
    name_str[name.length] = '\0';

    int idx = get(variable_ht, name_str);
    fprintf(outf, "global.r %u\n", idx);
}