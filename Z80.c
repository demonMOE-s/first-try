#ifndef __MAIN_INSTRUCTION_H
#define __MAIN_INSTRUCTION_H 

// begin 00 
#define NOP   			0x00 // 00   Idle 					-  4 cycles 
#define I16_TO_BC	 	0x01 // 01   BC = imm16 			- 10 cycles 
#define A_TO_$BC 		0x02 // 02  (BC)= A					-  7 cycles
#define INC_BC			0x03 // 03 ++BC						-  6 cycles 
#define INC_B 			0x04 // 04 ++B						-  4 cycles 
#define DEC_B			0x05 // 05 --B						-  4 cycles
#define I8_TO_B			0x06 // 06   B  = imm8				-  7 cycles 
#define RLCA			0x07 // 07 	 			x86's ROL 	-  4 cycles 
#define SWP_AF_MIR		0x08 // 08 	 AF~= AF' 				-  4 cycles 
#define ADD_HL_BC		0x09 // 09 	 HL+= BC				- 11 cycles 
#define $BC_TO_A		0x0A // 0A   A  =(BC) 				-  7 cycles 
#define DEC_BC			0x0B // 0B --BC						-  6 cycles
#define INC_C			0x0C // 0C ++C 						-  4 cycles
#define DEC_C			0x0D // 0D --C						-  4 cycles 
#define I8_TO_C			0x0E // 0E   C  = imm8   			-  7 cycles 
#define RRCA			0x0F // 0F 				x86's ROR 	-  4 cycles 

// begin 10 
#define DJNZ			0x10 // 10 				       !--B -  8 cycles + hit -> 5 cycles 
#define I16_TO_DE		0x11 // 11   DE = imm16			 	- 10 cycles 
#define A_TO_$DE		0x12 // 12  (DE)= A					-  7 cycles 
#define INC_DE			0x13 // 13 ++DE						-  6 cycles 
#define INC_D 			0x14 // 14 ++D						-  4 cycles 
#define DEC_D			0x15 // 15 --D						-  4 cycles
#define I8_TO_D			0x16 // 16   D  = imm8				-  7 cycles 
#define RLA				0x17 // 17 				6502's ROL 	-  4 cycles 
#define JR				0x18 // 18   sjmp					- 12 cycles 
#define ADD_HL_DE		0x19 // 19 	 HL+= DE				- 11 cycles 
#define $DE_TO_A		0x1A // 1A   A  =(DE) 				-  7 cycles 
#define DEC_DE			0x1B // 1B --DE						-  6 cycles
#define INC_E			0x1C // 1C ++E 						-  4 cycles
#define DEC_E			0x1D // 1D --E						-  4 cycles 
#define I8_TO_E			0x1E // 1E   E  = imm8			   	-  7 cycles 
#define RRA				0x1F // 1F 				6502's ROR 	-  4 cycles 

// begin 20 
#define JR_NZ			0x20 // 20   			 		!ZF -  7 cycles + hit -> 5 cycles 
#define I16_TO_HL		0x21 // 21   HL = imm16				- 10 cycles 
#define HL_TO_$I16 		0x22 // 22(imm16)= HL				- 16 cycles 
#define INC_HL			0x23 // 23 ++HL 					-  6 cycles
#define INC_H 			0x24 // 24 ++H 						-  4 cycles 
#define DEC_H 			0x25 // 25 --H 						-  4 cycles 
#define I8_TO_H 		0x26 // 26   H  = imm8				-  7 cycles 
#define DAA				0x27 // 27 			 		  A-BCD -  4 cycles 
#define JR_Z			0x28 // 28 	 			         ZF -  7 cycles + hit -> 5 cycles 
#define ADD_HL_HL 		0x29 // 29   HL+= HL 				- 11 cycles 
#define $I16_TO_HL		0x2A // 2A   HL =(imm16) 			- 16 cycles 
#define DEC_HL			0x2B // 2B --HL 					-  6 cycles 
#define INC_L			0x2C // 2C ++L 						-  4 cycles 
#define DEC_L			0x2D // 2D --L 						-  4 cycles 
#define I8_TO_L 		0x2E // 2E   L  = imm8			  	-  7 cycles 
#define CPL 			0x2F // 2F 						 ~A -  4 cycles 

// begin 30 
#define JR_NC			0x30 // 30 	 			        !CF -  7 cycles + hit -> 5 cycles 
#define I16_TO_SP		0x31 // 31 	 SP = imm16			 	- 10 cycles 
#define A_TO_$16		0x32 // 32(imm16)= A 		    	- 13 cycles 
#define INC_SP			0x33 // 33 ++SP 					-  6 cycles 
#define INC_$HL 		0x34 // 34 ++(HL)					- 11 cycles 
#define DEC_$HL 		0x35 // 35 --(HL)					- 11 cycles 
#define I8_TO_$HL		0x36 // 36   (HL)=imm8 				- 10 cycles 
#define SCF				0x37 // 37 					 set CF	-  4 cycles 
#define JR_C			0x38 // 38 	 					 CF -  7 cycles + hit -> 5 cycles 
#define ADD_HL_SP		0x39 // 39   HL+= SP				- 11 cycles 
#define $I16_TO_A		0x3A // 3A   A  =(imm16)  			- 13 cycles 
#define DEC_SP			0x3B // 3B --SP 					-  6 cycles 
#define INC_A			0x3C // 3C ++A 						-  4 cycles 
#define DEC_A			0x3D // 3D --A 						-  4 cycles 
#define I8_TO_A			0x3E // 3E   A  =imm8			 	-  7 cycles 
#define CCF				0x3F // 3F 						^CF -  4 cycles 

// begin 40 
#define B_TO_B			0x40 // 40   B  = B 				-  4 cycles 
#define C_TO_B			0x41 // 41   B  = C 				-  4 cycles 
#define D_TO_B			0x42 // 42   B  = D 				-  4 cycles 
#define E_TO_B			0x43 // 43   B  = E 				-  4 cycles 
#define H_TO_B			0x44 // 44   B  = H 				-  4 cycles 
#define L_TO_B			0x45 // 45   B  = L 				-  4 cycles 
#define $HL_TO_B		0x46 // 46   B  =(HL)    			-  7 cycles 
#define A_TO_B			0x47 // 47   B  = A 				-  4 cycles 
#define B_TO_C			0x48 // 48   C  = B 				-  4 cycles 
#define C_TO_C			0x49 // 49   C  = C 				-  4 cycles 
#define D_TO_C			0x4A // 4A   C  = D 				-  4 cycles 
#define E_TO_C			0x4B // 4B   C  = E 				-  4 cycles
#define H_TO_C			0x4C // 4C   C  = H 				-  4 cycles 
#define L_TO_C			0x4D // 4D   C  = L 				-  4 cycles 
#define $HL_TO_C		0x4E // 4E   C  =(HL)				-  7 cycles 
#define A_TO_C			0x4F // 4F   C  = A 				-  4 cycles 

// begin 50 
#define B_TO_D			0x50 // 50   D  = B 				-  4 cycles 
#define C_TO_D			0x51 // 51   D  = C 				-  4 cycles 
#define D_TO_D			0x52 // 52   D  = D 				-  4 cycles 
#define E_TO_D			0x53 // 53   D  = E 				-  4 cycles 
#define H_TO_D			0x54 // 54   D  = H 				-  4 cycles 
#define L_TO_D			0x55 // 55   D  = L 				-  4 cycles 
#define $HL_TO_D		0x56 // 56   D  =(HL) 				-  7 cycles 
#define A_TO_D			0x57 // 57   D  = A 				-  4 cycles 
#define B_TO_E			0x58 // 58   E  = B 				-  4 cycles 
#define C_TO_E			0x59 // 59   E  = C 				-  4 cycles 
#define D_TO_E			0x5A // 5A   E  = D 				-  4 cycles 
#define E_TO_E			0x5B // 5B   E  = E 				-  4 cycles
#define H_TO_E			0x5C // 5C   E  = H 				-  4 cycles 
#define L_TO_E			0x5D // 5D   E  = L 				-  4 cycles 
#define $HL_TO_E		0x5E // 5E   E  =(HL)				-  7 cycles 
#define A_TO_E			0x5F // 5F   E  = A 				-  4 cycles

// begin 60 
#define B_TO_H			0x60 // 60   H  = B 				-  4 cycles 
#define C_TO_H			0x61 // 61   H  = C 				-  4 cycles 
#define D_TO_H			0x62 // 62   H  = D 				-  4 cycles 
#define E_TO_H			0x63 // 63   H  = E 				-  4 cycles 
#define H_TO_H			0x64 // 64   H  = H 				-  4 cycles 
#define L_TO_H			0x65 // 65   H  = L 				-  4 cycles 
#define $HL_TO_H		0x66 // 66   H  =(HL) 				-  7 cycles 
#define A_TO_H			0x67 // 67   H  = A 				-  4 cycles 
#define B_TO_L			0x68 // 68   L  = B 				-  4 cycles 
#define C_TO_L			0x69 // 69   L  = C 				-  4 cycles 
#define D_TO_L			0x6A // 6A   L  = D 				-  4 cycles 
#define E_TO_L			0x6B // 6B   L  = E 				-  4 cycles
#define H_TO_L			0x6C // 6C   L  = H 				-  4 cycles 
#define L_TO_L			0x6D // 6D   L  = L 				-  4 cycles 
#define $HL_TO_L		0x6E // 6E   L  =(HL)				-  7 cycles 
#define A_TO_L			0x6F // 6F   L  = A 				-  4 cycles

// begin 70 
#define B_TO_$HL 		0x70 // 70  (HL)= B 				-  7 cycles 
#define C_TO_$HL		0x71 // 71  (HL)= C 				-  7 cycles 
#define D_TO_$HL 		0x72 // 72  (HL)= D 				-  7 cycles 
#define E_TO_$HL		0x73 // 73  (HL)= E 				-  7 cycles 
#define H_TO_$HL 		0x74 // 74  (HL)= H 				-  7 cycles 
#define L_TO_$HL		0x75 // 75  (HL)= L 				-  7 cycles 
#define HALT 			0x76 // 76 		    stop : interrupt-  4 cycles 
#define A_TO_$HL		0x77 // 77  (HL)= A 				-  7 cycles 
#define B_TO_A			0x78 // 78   A  = B 				-  4 cycles 
#define C_TO_A			0x79 // 79   A  = C 				-  4 cycles 
#define D_TO_A 			0x7A // 7A   A  = D 				-  4 cycles 
#define E_TO_A 			0x7B // 7B   A  = E 				-  4 cycles 
#define H_TO_A 			0x7C // 7C   A  = H 				-  4 cycles 
#define L_TO_A 			0x7D // 7D   A  = L 				-  4 cycles 
#define $HL_TO_A 		0x7E // 7E   A  =(HL)				-  7 cycles 
#define A_TO_A 			0x7F // 7F   A  = A 				-  4 cycles

// begin 80
#define ADD_B			0x80 // 80   A += B 				-  4 cycles 
#define ADD_C			0x81 // 81   A += C 				-  4 cycles 
#define ADD_D			0x82 // 82   A += D 				-  4 cycles 
#define ADD_E			0x83 // 83   A += E 				-  4 cycles 
#define ADD_H			0x84 // 84   A += H 				-  4 cycles 
#define ADD_L 			0x85 // 85   A += L 				-  4 cycles 
#define ADD_$HL 		0x86 // 86   A +=(HL)				-  7 cycles 
#define ADD_A			0x87 // 87   A += A 				-  4 cycles 
#define ADC_B			0x88 // 88   A += B   + CF			-  4 cycles 
#define ADC_C			0x89 // 89   A += C   + CF			-  4 cycles 
#define ADC_D			0x8A // 8A   A += D   + CF			-  4 cycles 
#define ADC_E			0x8B // 8B   A += E   + CF			-  4 cycles 
#define ADC_H			0x8C // 8C   A += H   + CF			-  4 cycles 
#define ADC_L 			0x8D // 8D   A += L   + CF			-  4 cycles 
#define ADC_$HL 		0x8E // 8E   A +=(HL) + CF			-  7 cycles 
#define ADC_A			0x8F // 8F   A += A   + CF			-  4 cycles 
	
// begin 90 
#define SUB_B			0x90 // 90 	 A -= B 				-  4 cycles 
#define SUB_C			0x91 // 91   A -= C 				-  4 cycles 
#define SUB_D			0x92 // 92   A -= D 				-  4 cycles 
#define SUB_E			0x93 // 93   A -= E 				-  4 cycles 
#define SUB_H			0x94 // 94   A -= H 				-  4 cycles 
#define SUB_L 			0x95 // 95   A -= L 				-  4 cycles 
#define SUB_$HL 		0x96 // 96   A -=(HL)				-  7 cycles 
#define SUB_A			0x97 // 97   A -= A 				-  4 cycles 
#define SBC_B			0x98 // 98   A -= B   + CF			-  4 cycles 
#define SBC_C			0x99 // 99   A -= C   + CF			-  4 cycles 
#define SBC_D			0x9A // 9A   A -= D   + CF			-  4 cycles 
#define SBC_E			0x9B // 9B   A -= E   + CF			-  4 cycles 
#define SBC_H			0x9C // 9C   A -= H   + CF			-  4 cycles 
#define SBC_L 			0x9D // 9D   A -= L   + CF			-  4 cycles 
#define SBC_$HL 		0x9E // 9E   A -=(HL) + CF			-  7 cycles 
#define SBC_A			0x9F // 9F   A -= A   + CF			-  4 cycles 

// begin A0 
#define AND_B			0xA0 // A0   A &= B 				-  4 cycles 
#define AND_C			0xA1 // A1   A &= C 				-  4 cycles 
#define AND_D			0xA2 // A2   A &= D 				-  4 cycles 
#define AND_E			0xA3 // A3   A &= E 				-  4 cycles 
#define AND_H			0xA4 // A4   A &= H 				-  4 cycles 
#define AND_L 			0xA5 // A5   A &= L 				-  4 cycles 
#define AND_$HL 		0xA6 // A6   A &=(HL)				-  7 cycles 
#define AND_A			0xA7 // A7   A &= A 				-  4 cycles 
#define XOR_B			0xA8 // A8   A ^= B 	          	-  4 cycles 
#define XOR_C			0xA9 // A9   A ^= C 	          	-  4 cycles 
#define XOR_D			0xAA // AA   A ^= D 	          	-  4 cycles 
#define XOR_E			0xAB // AB   A ^= E 	          	-  4 cycles 
#define XOR_H			0xAC // AC   A ^= H 	          	-  4 cycles 
#define XOR_L 			0xAD // AD   A ^= L 	          	-  4 cycles 
#define XOR_$HL 		0xAE // AE   A ^=(HL)	          	-  7 cycles 
#define XOR_A			0xAF // AF   A ^= A 	          	-  4 cycles 

// begin B0 
#define OR_B			0xB0 // B0   A |= B 				-  4 cycles 
#define OR_C			0xB1 // B1   A |= C 				-  4 cycles 
#define OR_D			0xB2 // B2   A |= D 				-  4 cycles 
#define OR_E			0xB3 // B3   A |= E 				-  4 cycles 
#define OR_H			0xB4 // B4   A |= H 				-  4 cycles 
#define OR_L 			0xB5 // B5   A |= L 				-  4 cycles 
#define OR_$HL 			0xB6 // B6   A |=(HL)				-  7 cycles 
#define OR_A			0xB7 // B7   A |= A 				-  4 cycles 
#define CP_B			0xB8 // B8   A !? B 	          	-  4 cycles 
#define CP_C			0xB9 // B9   A !? C 	          	-  4 cycles 
#define CP_D			0xBA // BA   A !? D 	          	-  4 cycles 
#define CP_E			0xBB // BB   A !? E 	          	-  4 cycles 
#define CP_H			0xBC // BC   A !? H 	          	-  4 cycles 
#define CP_L 			0xBD // BD   A !? L 	          	-  4 cycles 
#define CP_$HL 			0xBE // BE   A !?(HL)	          	-  7 cycles 
#define CP_A			0xBF // BF   A !? A 	          	-  4 cycles 

// begin C0 
#define RET_NZ			0xC0 // C0 	 				    !ZF -  5 cycles + hit -> 6 cycles 
#define POP_BC			0xC1 // C1   BC =(SP), += 2  		- 10 cycles 
#define JP_NZ			0xC2 // C2   					!ZF - 10 cycles 
#define JP 				0xC3 // C3 		  			jmp 	- 10 cycles 
#define CALL_NZ			0xC4 // C4 	 					!ZF - 10 cycles + hit -> 7 cycles 
#define PUSH_BC			0xC5 // C5 	   -= 2, (SP) = BC 		- 10 cycles 
#define ADD_I8			0xC6 // C6 	 A += imm8 				-  7 cycles 
#define RST_00H 		0xC7 // C7 			   push PC, = 0 - 11 cycles 
#define RET_Z			0xC8 // C8   					 ZF -  5 cycles + hit -> 6 cycles
#define RET 			0xC9 // C9 		 		    ret 	- 10 cycles 
#define JP_Z			0xCA // CA 	 					 ZF - 10 cycles 
#define PREFIX_CB		0xCB // CB   --- Bit !!! entry --- 	-N/A cycles 
#define CALL_Z			0xCC // CC   					 ZF - 10 cycles + hit -> 7 cycles 
#define CALL 			0xCD // CD 		  			call  	- 17 cycles 
#define ADC_I8			0xCE // CE 	 A += imm8  + CF		-  7 cycles
#define RST_08H			0xCF // CF 			   push PC, = 8 - 11 cycles

// begin D0 
#define RET_NC			0xD0 // D0   					!CF -  5 cycles + hit -> 6 cycles 
#define POP_DE			0xD1 // D1   DE =(SP), += 2  		- 10 cycles 
#define JP_NC			0xD2 // D2 	 					!CF - 10 cycles 
#define OUT_$I8 		0xD3 // D3   port[imm8] = A			- 11 cycles 
#define CALL_NC			0xD4 // D4   					!CF - 10 cycles + hit -> 7 cycles 
#define PUSH_DE			0xD5 // D5 	   -= 2, (SP) = DE 		- 10 cycles 
#define SUB_I8			0xD6 // D6 	 A -= imm8 				-  7 cycles 
#define RST_10H 		0xD7 // D7 			   push PC, =16 - 11 cycles 
#define RET_C			0xD8 // D8   					 CF -  5 cycles + hit -> 6 cycles
#define EXX 			0xD9 // D9 	 BC/DE/HL~= BC'/DE'/HL'	- 10 cycles 
#define JP_C			0xDA // DA 	 					 CF - 10 cycles 
#define IN_$I8			0xDB // DB 	 A = port[imm8]			- 11 cycles 
#define CALL_C			0xDC // DC   					 CF - 10 cycles + hit -> 7 cycles 
#define PREFIX_DD 		0xDD // DD 	 --- IX !!! entry ---   -N/A cycles 
#define SBC_I8			0xDE // DE   A -= imm8  + CF		-  7 cycles
#define RST_18H			0xDF // DF 			   push PC, =24 - 11 cycles

// begin E0 
#define RET_PO			0xE0 // E0   					!PF -  5 cycles + hit -> 6 cycles
#define POP_HL			0xE1 // E1   HL =(SP), += 2  		- 10 cycles 
#define JP_PO			0xE2 // E2 	 					!PF - 10 cycles 
#define SWP_$SP_HL		0xE3 // E3 (SP)~= HL 				- 19 cycles 
#define CALL_PO			0xE4 // E4 	 					!PF	- 10 cycles + hit -> 7 cycles
#define PUSH_HL			0xE5 // E5 	   -= 2, (SP) = HL 		- 10 cycles 
#define AND_I8			0xE6 // E6 	 A ^= imm8 				-  7 cycles 
#define RST_20H 		0xE7 // E7 			push PC, PC =32 - 11 cycles 
#define RET_PE			0xE8 // E8   					 PF -  5 cycles + hit -> 6 cycles
#define JP_HL 			0xE9 // E9 	 jmp  HL 				- 10 cycles 
#define JP_PE			0xEA // EA   					 PF - 10 cycles 
#define SWP_DE_HL		0xEB // EB   DE~= HL				- 11 cycles 
#define CALL_PE			0xEC // EC   					 PF	- 10 cycles + hit -> 7 cycles 
#define PREFIX_ED 		0xED // ED 	 --- EXTD !!! entry --- -N/A cycles 
#define XOR_I8			0xEE // EE   A ^= imm8  			-  7 cycles
#define RST_28H			0xEF // EF  		   push PC, =40 - 11 cycles

// begin F0 
#define RET_P			0xF0 // F0   					!SF	-  5 cycles + hit -> 6 cycles
#define POP_AF			0xF1 // F1   AF =(SP), += 2   		- 10 cycles 
#define JP_P			0xF2 // F2   					!SF - 10 cycles 
#define DI				0xF3 // F3 		  disable interrupt -  4 cycles 
#define CALL_P			0xF4 // F4   					!SF - 10 cycles + hit -> 7 cycles
#define PUSH_AF			0xF5 // F5     -= 2, (SP) = AF		- 10 cycles 
#define OR_I8			0xF6 // F6   A |= imm8 				-  7 cycles 
#define RST_30H 		0xF7 // F7 			   push PC, =48 - 11 cycles
#define RET_M			0xF8 // F8   					 SF	-  5 cycles + hit -> 6 cycles
#define HL_TO_SP 		0xF9 // F9   SP = HL 				-  6 cycles 
#define JP_M			0xFA // FA   					 SF	- 10 cycles 
#define EI				0xFB // FB 		  enable interrupt	- 11 cycles 
#define CALL_M			0xFC // FC   					 SF - 10 cycles + hit -> 7 cycles 
#define PREFIX_FD 		0xFD // FD 	 --- IY !!! entry ---   -N/A cycles
#define CMP_I8			0xFE // FE   A !? imm8  			-  7 cycles
#define RST_38H			0xFF // FF 		       push PC, =56 - 11 cycles







#endif 




























































































