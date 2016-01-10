/*
** Z80 CPU Emu 
** Copyright (C) 2015 xuanqi liang
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
** Library General Public License for more details.  To obtain a 
** copy of the GNU Library General Public License, write to the Free 
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/

#ifndef __CPU_ACTION_H
#define __CPU_ACTION_H

#define S_FLAG      0x80       /* 1: Result negative         */
#define Z_FLAG      0x40       /* 1: Result is zero          */
#define H_FLAG      0x10       /* 1: Halfcarry/Halfborrow    */
#define P_FLAG      0x04       /* 1: Result is even          */
#define V_FLAG      0x04       /* 1: Overflow occured        */
#define N_FLAG      0x02       /* 1: Subtraction occured     */
#define C_FLAG      0x01       /* 1: Carry/Borrow occured    */

/*\ --------------------------------- Mem/Reg Read/Write ---------------------------------------- \*/
#define I08_TO_RB(x)    CPUs->x  = Z80_RB (CPUs->PC++)          /* regByte = imm08 */
#define I16_TO_RW(x)    CPUs->TL = Z80_RB (CPUs->PC++);         /* regWord = imm16 */               \
                        CPUs->TH = Z80_RB (CPUs->PC++);                                             \
                        CPUs->x  =         CPUs->TP  
#define RB_TO_xI16(x)   CPUs->AL = Z80_RB (CPUs->PC++);         /* (imm16) = regByte */             \
                        CPUs->AH = Z80_RB (CPUs->PC++);                                             \
                                   Z80_WR (CPUs->AP++, CPUs->x )                       
#define RW_TO_xI16(x)   CPUs->TP =         CPUs->x;             /* (imm16) = regWord */             \
        RB_TO_xI16(TL);                                                                             \
                                   Z80_WR (CPUs->AP,   CPUs->TH)
#define xI16_TO_RB(x)   CPUs->AL = Z80_RB (CPUs->PC++);         /* regByte = (imm16) */             \
                        CPUs->AH = Z80_RB (CPUs->PC++);                                             \
                        CPUs->x  = Z80_RB (CPUs->AP++)                      
#define xI16_TO_RW(x)                                           /* regWord = (imm16) */             \
        xI16_TO_RB(TL);                                                                             \
                        CPUs->TH = Z80_RB (CPUs->AP);                                               \
                        CPUs->x  =         CPUs->TP                     
#define I08_TO_xRW(x)   CPUs->IL = Z80_RB (CPUs->PC++);         /* (regWord) = imm08 */             \
                        CPUs->AP =         CPUs->x;                                                 \
                                   Z80_WR (CPUs->AP++ ,                                             \
                                           CPUs->IL                                                 \
                                )       
#define I16_TO_xRW(x)   CPUs->TP =         CPUs->x;             /* (regWord) = imm16 */             \
        I08_TO_xRW(TP);                                                                             \
                        CPUs->IH = Z80_RB (CPUs->PC++);                                             \
                                   Z80_WR (CPUs->AP,                                                \
                                           CPUs->IH                                                 \
                                )                          
#define xRW_TO_RB(x, y) CPUs->AP =         CPUs->x;             /* regByte = (regWord) */           \
                        CPUs->y  = Z80_RB (CPUs->AP++)  
#define xRW_TO_RW(x, y)                                         /* regWord = (regWord) */           \
        xRW_TO_RB(x,IL);                                                                            \
                        CPUs->IH = Z80_RB (CPUs->AP);                                               \
                        CPUs->y  =         CPUs->IP
#define RB_TO_xRW(x, y) CPUs->AP =         CPUs->x;             /* (regWord) = regByte */           \
                                   Z80_WR (CPUs->AP++, CPUs->y )                                   
#define RW_TO_xRW(x, y) CPUs->TP =         CPUs->y;             /* (regWord) = regWord */           \
        RB_TO_xRW(x,TL);                                                                            \
                                   Z80_WR (CPUs->AP  , CPUs->TH)                                                       
#define RB_TO_RB(x, y)  CPUs->x  =         CPUs->y              /* regByte = regByte */
#define RW_TO_RW(x, y)  CPUs->x  =         CPUs->y              /* regWord = regWord */ 
/*\ --------------------------------- Mem/Reg Arith Opr ----------------------------------------- \*/
#define RW_INC(x)                         (CPUs->x ++)          /* regWord ++ */
#define RW_DEC(x)                         (CPUs->x --)          /* regWord -- */ 
#define RB_INC(x)       CPUs->TL =        (CPUs->x ++);         /* regByte ++ */                    \
                        CPUs->F  =        (CPUs->F & C_FLAG)                                        \
                                 |       ((CPUs->x & H_MASK) ? 0 : H_FLAG)                          \
                                 |       ((CPUs->x & (~CPUs->TL) & V_MASK) >> 5) | ZST[CPUs->x]
#define RB_DEC(x)       CPUs->TL =        (CPUs->x --);         /* regByte -- */                    \
                        CPUs->F  =        (CPUs->F & C_FLAG)                                        \
                                 |                   N_FLAG                                         \
                                 |      (((CPUs->x & H_MASK)== H_MASK) ? H_FLAG : 0)                \
                                 |      (((CPUs->TL& V_MASK & (CPUs->x ^ CPUs->TL))) >> 5)          \
                                                                                 | ZST[CPUs->x]
#define xI16_INC        CPUs->AL = Z80_RB (CPUs->PC++);         /* (imm16) ++ */                    \
                        CPUs->AH = Z80_RB (CPUs->PC++);                                             \
                        CPUs->IL = Z80_RB (CPUs->AP);                                               \
        RB_INC (IL);                                                                                \
                                   Z80_WR (CPUs->AP,                                                \
                                           CPUs->IL                                                 \
                                   )
#define xI16_DEC        CPUs->AL = Z80_RB (CPUs->PC++);         /* (imm16) -- */                    \
                        CPUs->AH = Z80_RB (CPUs->PC++);                                             \
                        CPUs->IL = Z80_RB (CPUs->AP);                                               \
        RB_DEC (IL);                                                                                \
                                   Z80_WR (CPUs->AP,                                                \
                                           CPUs->IL                                                 \
                                   )
#define xRW_INC(x)      CPUs->IL = Z80_RB (CPUs->x);            /* (regWord) ++ */                  \
         RB_INC(IL);                                                                                \
                                   Z80_WR (CPUs->x,                                                 \
                                           CPUs->IL                                                 \
                                   )
#define xRW_DEC(x)      CPUs->IL = Z80_RB (CPUs->x);            /* (regWord) -- */                  \
         RB_DEC(IL);                                                                                \
                                   Z80_WR (CPUs->x,                                                 \
                                           CPUs->IL                                                 \
                                   )
#define ACC_ADD(x)      CPUs->IP =       (uint16_t) x;          /* A += imm08/regByte */            \
                        CPUs->TP =         CPUs->IP +                                               \
                                 (uint16_t)CPUs->A;                                                 \
                        CPUs->F  =    (((~(CPUs->A ^     CPUs->IL))                                 \
                                 &        (CPUs->TL^     CPUs->IL) & V_MASK) >> 5)                  \
                                 |       ((CPUs->A ^     CPUs->IL  ^ CPUs->TL) & H_FLAG)            \
                                 |        (CPUs->TH    & C_FLAG)   | ZST[CPUs->TL];                 \
                        CPUs->A  =         CPUs->TL         
#define ACC_ADC(x)                                              /* A += imm08/regByte + C_Flag */   \
        ACC_ADD(((x) + (CPUs->F & C_FLAG)))                     
#define RW_ADD_RW(x, y) CPUs->LPD=             (uint32_t)CPUs->x;/* RegWord += RegWord + C_Flag */  \
                                 +             (uint32_t)CPUs->y;                                   \
                        CPUs->F &=                (~(N_FLAG                                         \
                                                   | H_FLAG                                         \
                                                   | C_FLAG)                                        \
                                                  );                                                \
                        CPUs->F  =       ((CPUs->x ^     CPUs->y ^ CPUs->LPW0) & 0x1000 ? H_FLAG : 0)\
                                 |       (           C_FLAG      & CPUs->LPB2);                     \
                        CPUs->x  =                                 CPUs->LPW0                                           
#define ACC_SUB(x)      CPUs->IP =       (uint16_t) x           /* A -= imm08/regByte */            \
                        CPUs->TP =       - CPUs->IP +                                               \
                                 (uint16_t)CPUs->A;                                                 \
                        CPUs->F  =     ((((CPUs->A ^ CPUs->IL))                                     \
                                 &        (CPUs->A ^ CPUs->TL) & V_MASK) >> 5)                      \
                                 |       ((CPUs->A ^ CPUs->TL) & H_FLAG   & CPUs->IL)               \
                                 |                ((~CPUs->TH) & C_FLAG)       | ZST[CPUs->TL];     \
                        CPUs->A  =                   CPUs->TL
#define ACC_SBC(x)                                              /* A -= imm08/regByte + C_Flag */   \
        ACC_SUB(((x) + (CPUs->F & C_FLAG)))                 
/*\ --------------------------------- Mem/Reg Shift Opr ----------------------------------------- \*/
#define ACC_XROL        CPUs->F &=                (~(N_FLAG     /* same as X86's ROL */             \
                                                   | H_FLAG                                         \
                                                   | C_FLAG)                                        \
                                                  );                                                \
                        CPUs->TL =        (CPUs->A>>7);                                             \
                        CPUs->A<<= 1;                                                               \
                        CPUs->A |=         CPUs->TL;                                                \
                        CPUs->F |=         CPUs->TL
#define ACC_XROR        CPUs->F &=                (~(N_FLAG      /* same as X86's ROR */            \
                                                   | H_FLAG                                         \
                                                   | C_FLAG)                                        \
                                                  );                                                \
                        CPUs->TL =        (CPUs->A &1);                                             \
                        CPUs->A>>= 1;                                                               \
                        CPUs->A |=        (CPUs->TL<<7);                                            \
                        CPUs->F |=         CPUs->TL
#define ACC_MROL        CPUs->TH =        (CPUs->F &1);         /* save as MOS6502's ROL */         \
                        CPUs->F &=                (~(N_FLAG                                         \
                                                   | H_FLAG                                         \
                                                   | C_FLAG)                                        \
                                                  );                                                \
                        CPUs->TL =         CPUs->A>>7;                                              \
                        CPUs->A<<= 1;                                                               \
                        CPUs->A |=         CPUs->TH;                                                \
                        CPUs->F |=         CPUs->TL 
    
#define ACC_MROR        CPUs->TH =         CPUs->F<<7;          /* save as MOS6502's ROR */         \
                        CPUs->F &=                (~(N_FLAG                                         \
                                                   | H_FLAG                                         \
                                                   | C_FLAG)                                        \
                                                  );                                                \
                        CPUs->TL =         CPUs->A &1;                                              \
                        CPUs->A>>= 1;                                                               \
                        CPUs->A |=         CPUs->TH;                                                \
                        CPUs->F |=         CPUs->TL
/*\ --------------------------------- Mem/Reg Logic Opr ----------------------------------------- \*/
#define ACC_AND(x)      CPUs->A &= (x);                         /* A &= imm08/regByte */            \
                        CPUs->F  = PZST[   CPUs->A ]                                                \
                                                   | H_FLAG     
#define ACC_OR(x)       CPUs->A |= (x);                         /* A |= imm08/regByte */            \
                        CPUs->F  = PZST[   CPUs->A ]                            
#define ACC_XOR(x)      CPUs->A ^= (x);                         /* A ^= imm08/regByte */            \
                        CPUs->F  = PZST[   CPUs->A ]    
#define ACC_CMP(x)      CPUs->NL =         CPUs->A;             /* A !? imm08/regByte */            \
        ACC_SUB(x);                                                                                 \
                        CPUs->A  =         CPUs->NL
/*\ --------------------------------- Mem/Reg Stack Opr ----------------------------------------- \*/
#define MM_PULLB(x)     CPUs->x  = Z80_RB (CPUs->SP++)          /* regByte = (Stack++) */           \
#define MM_PULLW(x)                                             /* regWord = (Stack++)[Word] */     \
        MM_PULLB(TL);                                                                               \
        MM_PULLB(TH);                                                                               \
                        CPUs->x  =         CPUs->TP                     
#define MM_PUSHB(x)                Z80_WR (CPUs->SP-1, CPUs->x);/* regByte = (--Stack) */           \
                        CPUs->SP-= 1
#define MM_PUSHW(x)     CPUs->TP =         CPUs->x;             /* regWord = (--Stack)[Word] */     \
        MM_PUSHB(TH);                                                                               \
        MM_PUSHB(TL)
/*\ --------------------------- factory Opr [JCC/PROC...etc] ------------------------------------ \*/
#define Z80_JR          CPUs->PC+= 1;                           /* short jmp */                     \
                        CPUs->PC+=                                                                  \
                        (sint16_t) Z80_RB (CPUs->PC)                    
#define Z80_JRF(x)  if (x) {                                    /* JCC (short) */                   \
                        Z80_JR;                                                                     \
    BURNING_CYCLE(5); /* --- hit + 5 cycles --- */                                                  \
            } else {                                                                                \
                        CPUs->PC+= 1;                                                               \
            }           
#define Z80_JP          CPUs->AL = Z80_RB (CPUs->PC++);         /* far jmp */                       \
                        CPUs->AH = Z80_RB (CPUs->PC);                                               \
                        CPUs->PC =         CPUs->AP                             
#define Z80_JPF     if (x) {                                    /* JCC (far) */                     \
                        Z80_JP;                                                                     \
            } else {                                                                                \
                        CPUs->PC+= 2;                                                               \
            }
#define Z80_CALL        CPUs->AL = Z80_RB (CPUs->PC++);         /* proc use */                      \
                        CPUs->AH = Z80_RB (CPUs->PC++);                                             \
        MM_PUSHW (PC);                                                                              \
                        CPUs->PC =         CPUs->AP         
#define Z80_CALLF(x)if (x) {                                    /* CCC */                           \
                        Z80_CALL;                                                                   \
    BURNING_CYCLE(7); /* --- hit + 7 cycles --- */                                                  \
            } else {                                                                                \
                        CPUs->PC+= 2;                                                               \
            }
#define Z80_RET                                                 /* proc ret */                      \
        MM_PULLW (PC)   
#define Z80_RETF(x) if (x) {                                    /* RCC */                           \
                        Z80_RET;                                                                    \
    BURNING_CYCLE(6); /* --- hit + 6 cycles --- */                                                  \
            } 
#define RST_NN(x)                                               /* push PC, =x */                   \
        MM_PUSHW(PC);   CPUs->PC = x
        
#define Z80_JR_DB                  Z80_JRF          (--CPUs->B)
#define Z80_JR_Z                   Z80_JRF          ( (CPUs->F & Z_FLAG))
#define Z80_JR_NZ                  Z80_JRF          (!(CPUs->F & Z_FLAG))   
#define Z80_JR_C                   Z80_JRF          ( (CPUs->F & C_FLAG))
#define Z80_JR_NC                  Z80_JRF          (!(CPUs->F & C_FLAG))       
#define Z80_JR_PE                  Z80_JRF          ( (CPUs->F & P_FLAG))
#define Z80_JR_PO                  Z80_JRF          (!(CPUs->F & P_FLAG))           
#define Z80_JR_M                   Z80_JRF          ( (CPUs->F & S_FLAG))
#define Z80_JR_P                   Z80_JRF          (!(CPUs->F & S_FLAG))   
#define Z80_JP_Z                   Z80_JPF          ( (CPUs->F & Z_FLAG))
#define Z80_JP_NZ                  Z80_JPF          (!(CPUs->F & Z_FLAG))   
#define Z80_JP_C                   Z80_JPF          ( (CPUs->F & C_FLAG))
#define Z80_JP_NC                  Z80_JPF          (!(CPUs->F & C_FLAG))   
#define Z80_JP_PE                  Z80_JPF          ( (CPUs->F & P_FLAG))
#define Z80_JP_PO                  Z80_JPF          (!(CPUs->F & P_FLAG))   
#define Z80_JP_M                   Z80_JPF          ( (CPUs->F & S_FLAG))
#define Z80_JP_P                   Z80_JPF          (!(CPUs->F & S_FLAG))   
#define Z80_CALL_Z                 Z80_CALLF        ( (CPUs->F & Z_FLAG))
#define Z80_CALL_NZ                Z80_CALLF        (!(CPUs->F & Z_FLAG))   
#define Z80_CALL_C                 Z80_CALLF        ( (CPUs->F & C_FLAG))
#define Z80_CALL_NC                Z80_CALLF        (!(CPUs->F & C_FLAG))   
#define Z80_CALL_PE                Z80_CALLF        ( (CPUs->F & P_FLAG))
#define Z80_CALL_PO                Z80_CALLF        (!(CPUs->F & P_FLAG))   
#define Z80_CALL_M                 Z80_CALLF        ( (CPUs->F & S_FLAG))
#define Z80_CALL_P                 Z80_CALLF        (!(CPUs->F & S_FLAG))
#define Z80_RET_Z                  Z80_RETF         ( (CPUs->F & Z_FLAG))
#define Z80_RET_NZ                 Z80_RETF         (!(CPUs->F & Z_FLAG))   
#define Z80_RET_C                  Z80_RETF         ( (CPUs->F & C_FLAG))
#define Z80_RET_NC                 Z80_RETF         (!(CPUs->F & C_FLAG))   
#define Z80_RET_PE                 Z80_RETF         ( (CPUs->F & P_FLAG))
#define Z80_RET_PO                 Z80_RETF         (!(CPUs->F & P_FLAG))   
#define Z80_RET_M                  Z80_RETF         ( (CPUs->F & S_FLAG))
#define Z80_RET_P                  Z80_RETF         (!(CPUs->F & S_FLAG))
#define Z80_RST_00H                RST_NN(0x00)
#define Z80_RST_08H                RST_NN(0x08) 
#define Z80_RST_10H                RST_NN(0x10)
#define Z80_RST_18H                RST_NN(0x18)
#define Z80_RST_20H                RST_NN(0x20)
#define Z80_RST_28H                RST_NN(0x28) 
#define Z80_RST_30H                RST_NN(0x30)
#define Z80_RST_38H                RST_NN(0x38)
/*\ ------------------------------------- MISC Opr ---------------------------------------------- \*/
/*\ ---> swap(~)reg/mem <--- \*/     
#define EX_TO_RB(x, y)  CPUs->TL =         CPUs->x;                                                 \
                        CPUs->x  =         CPUs->y;                                                 \
                        CPUs->y  =         CPUs->TL                     
#define EX_TO_RW(x, y)  CPUs->TP =         CPUs->x;                                                 \
                        CPUs->x  =         CPUs->y;                                                 \
                        CPUs->y  =         CPUs->TP
#define EX_CACHE(x)                                                                                 \
        EX_TO_RW(x, x##_Cache)                      
#define Z80_EXX                                                                                         \
        EX_CACHE(BC);                                                                               \
        EX_CACHE(DE);                                                                               \
        EX_CACHE(HL)
#define MMWB_RB_EX(x, y)CPUs->TL = Z80_RB (CPUs->x);                                                \
                        CPUs->TH =         CPUs->y;                                                 \
                        CPUs->y  =         CPUs->TL;                                                \
                                   Z80_WR (CPUs->x , CPUs->TH)                             
#define MMWW_RW_EX(x, y)CPUs->TL = Z80_RB (CPUs->x++);                                              \
                        CPUs->TH = Z80_RB (CPUs->x--);                                              \
                        CPUs->AP =         CPUs->y;                                                 \
                                   Z80_WR (CPUs->x++,CPUs->AL);                                     \
                                   Z80_WR (CPUs->x--,CPUs->AH);                                     \
                        CPUs->y  =         CPUs->TP 
#define ACC_INVR        CPUs->A  =       ~ CPUs->A;                 /* invert A */                  \
                        CPUs->F |=                ( (N_FLAG                                         \
                                                   | H_FLAG                                         \
                                                  ) 
#define Z80_SCF                            CPUs->F|=  C_FLAG;       /* set C Flag */                \
                                           CPUs->F&=~(N_FLAG | H_FLAG)                                                 
#define Z80_CCF                            CPUs->F^=  C_FLAG;       /* invert C Flag */             \
                                           CPUs->F&=~(N_FLAG | H_FLAG);                             \
                                           CPUs->F|=(                                               \
                                           CPUs->F &  C_FLAG)                                       \
                                                   ?  0                                             \
                                                   :  H_FLAG                            
#define BCD_ADJUST                   if   (CPUs->F &  C_FLAG)CPUs->TH = 0x100; /* BCD hack */       \
                                     if   (CPUs->F &  H_FLAG)CPUs->TH|= 0x200;                      \
                                     if   (CPUs->F &  N_FLAG)CPUs->TH|= 0x400;                      \
                                                             CPUs->TL = CPUs->A;                    \
                                           CPUs->AF= DAAT[   CPUs->TP]  
#define EB(x)           CPUs->##x       
#define MB(x)                      Z80_RB (EB(HL)) 
#define WB(x)                      Z80_RB (CPUs->x)
#define IB(x)                      Z80_RB (CPUs->x++)

#define BURNING_CYCLE(x)CPUs->IL             = x;                                                   \
                        CPUs->Remain_Cycles -= CPUs->IL;                                            \
                        CPUs->Elapse_Cycles += CPUs->IL

#define ASK_NWPC(x)    (CPUs->PC+= (x))     
#define CLR_FLAG(x)    (CPUs->F &= (x))
#define SET_FLAG(x)    (CPUs->F |= (x))
#define NEG_FLAG(x)    (CPUs->F ^= (x))
#define TST_FLAG(x)    (CPUs->F  & (x))
