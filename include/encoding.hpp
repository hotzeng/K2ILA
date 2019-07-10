// 05-27-2019
// Author: Yu Zeng

#ifndef __RISCV_ENCODING_HPP__
#define __RISCV_ENCODING_HPP__
#include <math.h>


#define GPR_NUM     16
#define SEG_REG_NUM 6
#define EFLAGS_LEN  32
#define EIP_LEN     32 // equals XLEN

#define GPR_BITS    log2(GPR_BITS)    

#define MEM_WORD          8
#define PHY_MEM_ADDR_LEN  36

// values for mode
#define PROTECTED   0
#define REAL        1
#define SMM         2

// encodings
#define NULL_BYTE   0x00
#define PFX_CS      0x2E
#define PFX_SS      0x36
#define PFX_DS      0x3E
#define PFX_ES      0x26
#define PFX_FS      0x64
#define PFX_GS      0x65
#define PFX_ADR     0x67 // address-size override
#define PFX_LOCK    0xF0
#define PFX_OPR     0x66
#define PFX_REP     0xF2 //string prefix, repeat
#define PFX_REPNZ   0xF3 // string prefix, repeat-not-zero




#endif
