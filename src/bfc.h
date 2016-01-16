
#ifndef __BFC_H__
#define __BFC_H__

#define MAX_ADDRESS 0x10FF
#define MIN_ADDRESS 0x1000

#define INC_inst 0x03, 0x95
#define DEC_inst 0x0A, 0x95

// LDS - load direct, from data space
#define LDS_inst 0x00, 0x91 // appended with 2 bytes of address
#define STS_inst 0x00, 0x93 // appended with 2 bytes of address

// BRNE - branch if not equal
// #define BRNE_inst 0xF
// BRNE is only limited by +-64 instructions
// will use absolute jumps + brne/breq
/*
 * cpi r16, 0
 * brne .+4
 * jmp DOWN
 */

#define CPI_inst 0x00,  0x30 // compare imidiate r16, 0
#define IN_SREG_inst 0x5f, 0xb7
#define SBRS_inst    0x51, 0xFF // skip if Z bit in register (sreg) is set
#define JMP_inst 0x0C,  0x94 // appended with 2 bytes of address
#define BRNE_inst 0x11, 0xf4 // brne .+4
#define BREQ_inst 0x11, 0xf0 // breq .+4

// 1110KKKKddddKKKK
#define LDI(r, val) ( ((r & 0x0F) << 4) | ((val) & 0x0F)), (0xE0 | (((val) >> 4) & 0x0F))

// (ii) 1001 000d dddd 1101
// (iii) 1001 000d dddd 1110
#define LD_inc(r) (((r & 0x0F) << 4) | 0b1101), (0x90 | (r >> 4))
#define LD_dec(r) (((r & 0x0F) << 4) | 0b1110), (0x90 | (r >> 4))
// (i) 1001 000d dddd 1100
#define LD(r) (((r & 0x0F) << 4) | 0b1100), (0x90 | (r >> 4))

// (i) 1001 001r rrrr 1100
#define ST(r) (((r & 0x0F) << 4) | 0b1100), (0x90 | 0b10 | (r >> 4))

#define BYTE(X) (X & 0xFF), (X >> 8)


#endif
