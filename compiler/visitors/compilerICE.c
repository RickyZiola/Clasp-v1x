#include "../visitor.h"
#include "compiler.h"
#include "../../dynabuf/dynabuf.h"
#include "ICE.h"
#include <stdio.h>
#include <stdlib.h>

static DynamicBuffer(byte) *codeSegment; // Up to 4GB of code
static uint32_t codeIdx = 0;

static DynamicBuffer(byte) *dataSegment; // Up to 4GB of data
static uint32_t dataIdx = 0;

void compiler_init() {
    codeSegment = newDynamicBuf(byte);
    initDynamicBuf(byte, codeSegment);

    dataSegment = newDynamicBuf(byte);
    initDynamicBuf(byte, dataSegment);
}

char *compiler_get_compiled() { // TODO print the value [TMP]
    return (char *) codeSegment->data;
}
unsigned int compiler_get_compiled_size() {
    return codeIdx;
}

static void emit_byte(byte data) {
    writeDynamicBuf(byte, codeSegment, codeIdx, data); ++codeIdx;
}
static void emit_bytes(byte data1, byte data2) {
    emit_byte(data1);
    emit_byte(data2);
}

void emit_int(long int data) {
    size_t size = sizeof(long int);

    for (size_t i = 0; i < size; ++i) {
        byte current_byte = (byte)((data >> (i * 8)) & 0xFF);
        emit_byte(current_byte);
    }
}

void visitor_literal_int(long int val) {
    // This value is NOT loaded into the data segment for faster access times.
    // In the case of string/list/obj literals, they are loaded into the data segment.

    // ICE assembly for loading a constant onto the stack:
    //               ; Initial,        stack = [ ]
    // const.i <n>   ; Constnant load, stack = [n]

    emit_byte(ICE_CONST_I);
    emit_int(val);
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

            emit_byte(ICE_CONST_0);
            emit_byte(ICE_SWAP);
            emit_byte(ICE_SUB_I);
        } break;
        case TOKEN_BANG: {
            // TODO: type checking

            // ICE assembly for a bitwise NOT:
            //              ; Initial,     stack = [n ]
            // not          ; Bitwise NOT, stack = [!n]

            // This is !n

            emit_byte(ICE_NOT);
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

            emit_byte(ICE_ADD_I);
        } break;
        case TOKEN_MINUS: {
            // TODO: type checking

            // ICE assembly for subtracting 2 numbers:
            //          ; Initial,     stack = [n m]
            // sub.i    ; Subtraction, stack = [n-m]

            // This is n-m

            emit_byte(ICE_SUB_I);
        } break;
        case TOKEN_ASTERIX: {
            // TODO: type checking

            // ICE assembly for multiplying 2 numbers:
            //          ; Initial,        stack = [n m]
            // mul.i    ; Multiplication, stack = [n*m]

            // This is n*m

            emit_byte(ICE_MUL_I);
        } break;
        case TOKEN_SLASH: {
            // TODO: type checking

            // ICE assembly for dividing 2 numbers:
            //          ; Initial,  stack = [n m]
            // div.i    ; Division, stack = [n/m]

            // This is n/m

            emit_byte(ICE_DIV_I);
        } break;
        default: {
            fprintf(stderr, "Compile error: unknown binary operator\n");
            exit(-1);
        }
    }
}