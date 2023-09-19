#ifndef ICE_H
#define ICE_H

// B = byte
// W = word
// D = dword
// Q = qword

// N = natural (int > 0)
// I = integer
// R = real (floating-poing)
// C = complex (sum of real and imaginary)

#define ICE_HALT    0x00
#define ICE_REST    0x01

#define ICE_CONST_B 0x02
#define ICE_CONST_W 0x03
#define ICE_CONST_D 0x04
#define ICE_CONST_Q 0x05

#define ICE_CONST_N 0x05
#define ICE_CONST_I 0x05
#define ICE_CONST_R 0x05
#define ICE_CONST_C 0x05

// 0 = 0
// F = false
// L = low

// 1 = 1
// T = true
// H = high

#define ICE_CONST_0 0x06
#define ICE_CONST_F 0x06
#define ICE_CONST_L 0x06

#define ICE_CONST_1 0x07
#define ICE_CONST_T 0x07
#define ICE_CONST_H 0x07

#define ICE_SWAP    0x08

// Empty instruction 0x09

// N here means num, not natural.
// Clone / drop the top of the stack N times

#define ICE_CLONE_N 0x0A
#define ICE_DROP_N  0x0B
#define ICE_CLONE   0x0C
#define ICE_DROP    0x0D

// Empty instructions 0x0E-0x0F

#define ICE_ADD_N   0x10
#define ICE_ADD_I   0x11
#define ICE_ADD_R   0x12
#define ICE_ADD_C   0x13

#define ICE_SUB_N   0x14
#define ICE_SUB_I   0x15
#define ICE_SUB_R   0x16
#define ICE_SUB_C   0x17

#define ICE_MUL_N   0x18
#define ICE_MUL_I   0x19
#define ICE_MUL_R   0x1A
#define ICE_MUL_C   0x1B

#define ICE_DIV_N   0x1C
#define ICE_DIV_I   0x1D
#define ICE_DIV_R   0x1E
#define ICE_DIV_C   0x1F

#define ICE_MOD_N   0x20
#define ICE_MOD_I   0x21
#define ICE_MOD_R   0x22
// #define ICE_MOD_C   0x23  // Not implemented

#define ICE_POW_N   0x24
#define ICE_POW_I   0x25
#define ICE_POW_R   0x26
// #define ICE_POW_C   0x27  // Not implemented

#define ICE_INC_N   0x28
#define ICE_INC_I   0x29
#define ICE_INC_R   0x30
// #define ICE_INC_C   0x31  // Not implemented

#define ICE_DEC_N   0x32
#define ICE_DEC_I   0x33
#define ICE_DEC_R   0x34
// #define ICE_DEC_C   0x35  // Not implemented

#define ICE_MAGNITUDE 0x36
#define ICE_CONJUGATE 0x37
#define ICE_COMBINE   0x38
#define ICE_PROJECT   0x39 // TODO: switch R and I so that they match the rest of the opcodes (?)
#define ICE_PROJECT_R 0x3A
#define ICE_PROJECT_I 0x3B

// Empty instructions 0x3C-0x3F
#define ICE_MASK_B  0x40
#define ICE_MASK_W  0x41
#define ICE_MASK_D  0x42
#define ICE_MASK_Q  0x43

// G = get
// S = set
// R = reset (clear)

#define ICE_BIT_G   0x44
#define ICE_BIT_S   0x45
#define ICE_BIT_R   0x46

// L = low
// H = high
// S = ??

#define ICE_NIBBLE_L  0x47
#define ICE_NIBBLE_H  0x48
#define ICE_NIBBLE_S  0x49

#define ICE_BUFFER  0x01 // Same as REST, buffer gate

#define ICE_AND     0x4A
#define ICE_OR      0x4B
#define ICE_NOT     0x4C
#define ICE_NOR     0x4D
#define ICE_NAND    0x4E
#define ICE_XOR     0x4F
#define ICE_XNOR    0x50
#define ICE_XAND    0x50 // Same as XNOR

#define ICE_INVERT     0x51
#define ICE_REVERSE    0x52
#define ICE_COMPLEMENT 0x53

// The argument here is the amount to shift, it's limited to 6 bits.
#define ICE_SHIFT_R    0x54
#define ICE_SHIFT_L    0x55

// The argument here is the amount to rotate, it's limited to 5 bits.
#define ICE_ROTATE_R   0x56
#define ICE_ROTATE_L   0x57

// Empty instructions 0x58-0x5F

// TODO: jumps, once those are sorted out.

#endif