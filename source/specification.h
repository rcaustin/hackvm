#include <stdint.h>

/* Register Size == 16bit */
#define BYTE uint8_t
#define WORD uint16_t

/* Memory Size = 2^15 = 32K */
#define MEMSIZE 32768

/* Signals */
#define SGNL_QUIT 0x8800 // 1000 1000 0000 0000

/* Instruction Masks */
#define INST_A    0x7FFF // 0--- ---- ---- ----
#define INST_C    0xE000 // 111- ---- ---- ----
#define COMP_MASK 0x1FC0 // ---1 1111 11-- ----
#define DEST_MASK 0xE038 // ---- ---- --11 1---
#define JUMP_MASK 0x0007 // ---- ---- ---- -111
#define SIGN_MASK 0x8000 // 1--- ---- ---- ----

/* C-Instruction: Comp Field */
#define COMP_ZERO 0x0980 // ---0 1010 10-- ----
#define COMP_POS1 0x0FC0 // ---0 1111 11-- ----
#define COMP_NEG1 0x0E80 // ---0 1110 10-- ----
#define COMP_D    0x0300 // ---0 0011 00-- ----
#define COMP_A    0x0C00 // ---0 1100 00-- ----
#define COMP_CMPD 0x0340 // ---0 0011 01-- ----
#define COMP_CMPA 0x0C40 // ---0 1100 01-- ----
#define COMP_NEGD 0x03C0 // ---0 0011 11-- ----
#define COMP_NEGA 0x0CC0 // ---0 1100 11-- ----
#define COMP_INCD 0x07C0 // ---0 0111 11-- ----
#define COMP_INCA 0x0DC0 // ---0 1101 11-- ----
#define COMP_DECD 0x0380 // ---0 0011 10-- ----
#define COMP_DECA 0x0C80 // ---0 1100 10-- ----
#define COMP_DPA  0x0080 // ---0 0000 10-- ----
#define COMP_DMA  0x04C0 // ---0 0100 11-- ----
#define COMP_AMD  0x01C0 // ---0 0001 11-- ----
#define COMP_DAA  0x0000 // ---0 0000 00-- ----
#define COMP_DOA  0x0540 // ---0 0101 01-- ----

#define COMP_M    0x1C00 // ---1 1100 00-- ----
#define COMP_CMPM 0x1C40 // ---1 1100 01-- ----
#define COMP_NEGM 0x1CC0 // ---1 1100 11-- ----
#define COMP_INCM 0x1DC0 // ---1 1101 11-- ----
#define COMP_DECM 0x1C80 // ---1 1100 10-- ----
#define COMP_DPM  0x1080 // ---1 0000 10-- ----
#define COMP_DMM  0x14C0 // ---1 0100 11-- ----
#define COMP_MMD  0x11C0 // ---1 0001 11-- ----
#define COMP_DAM  0x1000 // ---1 0000 00-- ----
#define COMP_DOM  0x1540 // ---1 0101 01-- ----

/* C-Instruction: Dest Field */
#define DEST_NUL  0xE000 // ---- ---- --00 0---
#define DEST_M    0xE008 // ---- ---- --00 1---
#define DEST_D    0xE010 // ---- ---- --01 0---
#define DEST_MD   0xE018 // ---- ---- --01 1---
#define DEST_A    0xE020 // ---- ---- --10 0---
#define DEST_AM   0xE028 // ---- ---- --10 1---
#define DEST_AD   0xE030 // ---- ---- --11 0---
#define DEST_AMD  0xE038 // ---- ---- --11 1---

/* C-Instruction: Jump Field */
#define JUMP_NUL  0x0000 // ---- ---- ---- -000
#define JUMP_JGT  0x0001 // ---- ---- ---- -001
#define JUMP_JEQ  0x0002 // ---- ---- ---- -010
#define JUMP_JGE  0x0003 // ---- ---- ---- -011
#define JUMP_JLT  0x0004 // ---- ---- ---- -100
#define JUMP_JNE  0x0005 // ---- ---- ---- -101
#define JUMP_JLE  0x0006 // ---- ---- ---- -110
#define JUMP_JMP  0x0007 // ---- ---- ---- -111
