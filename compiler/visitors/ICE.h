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

static const char ICE_HALT    = 0x00;
static const char ICE_REST    = 0x01;

static const char ICE_CONST_B = 0x02;
static const char ICE_CONST_W = 0x03;
static const char ICE_CONST_D = 0x04;
static const char ICE_CONST_Q = 0x05;

static const char ICE_CONST_N = 0x05;
static const char ICE_CONST_I = 0x05;
static const char ICE_CONST_R = 0x05;
static const char ICE_CONST_C = 0x05;

// 0 = 0
// F = false
// L = low

// 1 = 1
// T = true
// H = high

static const char ICE_CONST_0 = 0x06;
static const char ICE_CONST_F = 0x06;
static const char ICE_CONST_L = 0x06;

static const char ICE_CONST_1 = 0x07;
static const char ICE_CONST_T = 0x07;
static const char ICE_CONST_H = 0x07;

static const char ICE_SWAP    = 0x08;

// Empty instruction 0x09

// N here means num, not natural.
// Clone / drop the top of the stack N times

static const char ICE_CLONE_N = 0x0A;
static const char ICE_DROP_N  = 0x0B;
static const char ICE_CLONE   = 0x0C;
static const char ICE_DROP    = 0x0D;

// Empty instructions 0x0E-0x0F

static const char ICE_ADD_N   = 0x10;
static const char ICE_ADD_I   = 0x11;
static const char ICE_ADD_R   = 0x12;
static const char ICE_ADD_C   = 0x13;

static const char ICE_SUB_N   = 0x14;
static const char ICE_SUB_I   = 0x15;
static const char ICE_SUB_R   = 0x16;
static const char ICE_SUB_C   = 0x17;

static const char ICE_MUL_N   = 0x18;
static const char ICE_MUL_I   = 0x19;
static const char ICE_MUL_R   = 0x1A;
static const char ICE_MUL_C   = 0x1B;

static const char ICE_DIV_N   = 0x1C;
static const char ICE_DIV_I   = 0x1D;
static const char ICE_DIV_R   = 0x1E;
static const char ICE_DIV_C   = 0x1F;

static const char ICE_MOD_N   = 0x20;
static const char ICE_MOD_I   = 0x21;
static const char ICE_MOD_R   = 0x22;
// static const char ICE_MOD_C     = 0x23;  // Not implemented

static const char ICE_POW_N   = 0x24;
static const char ICE_POW_I   = 0x25;
static const char ICE_POW_R   = 0x26;
// static const char ICE_POW_C   = 0x27;  // Not implemented

static const char ICE_INC_N   = 0x28;
static const char ICE_INC_I   = 0x29;
static const char ICE_INC_R   = 0x30;
// static const char ICE_INC_C   = 0x31;  // Not implemented

static const char ICE_DEC_N   = 0x32;
static const char ICE_DEC_I   = 0x33;
static const char ICE_DEC_R   = 0x34;
// static const char ICE_DEC_C   = 0x35;  // Not implemented

static const char ICE_MAGNITUDE = 0x36;
static const char ICE_CONJUGATE = 0x37;
static const char ICE_COMBINE   = 0x38;
static const char ICE_PROJECT   = 0x39;
static const char ICE_PROJECT_R = 0x3A;
static const char ICE_PROJECT_I = 0x3B;

// Empty instructions 0x3C-0x3F
static const char ICE_MASK_B  = 0x40;
static const char ICE_MASK_W  = 0x41;
static const char ICE_MASK_D  = 0x42;
static const char ICE_MASK_Q  = 0x43;

// G = get
// S = set
// R = reset (clear)

static const char ICE_BIT_G   = 0x44;
static const char ICE_BIT_S   = 0x45;
static const char ICE_BIT_R   = 0x46;

// L = low
// H = high
// S = swap

static const char ICE_NIBBLE_L  = 0x47;
static const char ICE_NIBBLE_H  = 0x48;
static const char ICE_NIBBLE_S  = 0x49;

static const char ICE_BUFFER  = 0x01; // Same as REST, buffer gate

static const char ICE_AND     = 0x4A;
static const char ICE_OR      = 0x4B;
static const char ICE_NOT     = 0x4C;
static const char ICE_NOR     = 0x4D;
static const char ICE_NAND    = 0x4E;
static const char ICE_XOR     = 0x4F;
static const char ICE_XNOR    = 0x50;
static const char ICE_XAND    = 0x50; // Same as XNOR

static const char ICE_INVERT     = 0x51;
static const char ICE_REVERSE    = 0x52;
static const char ICE_COMPLEMENT = 0x53;

// The argument here is the amount to shift, it's limited to 6 bits.
static const char ICE_SHIFT_R    = 0x54;
static const char ICE_SHIFT_L    = 0x55;

// The argument here is the amount to rotate, it's limited to 5 bits.
static const char ICE_ROTATE_R   = 0x56;
static const char ICE_ROTATE_L   = 0x57;

// Empty instructions 0x58-0x5F

// TODO: jumps, once those are sorted out.

#endif