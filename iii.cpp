/*\ -------------------------- opcode 00 ------------------------ \*/
	case 			NOP: 									break; // 00 NOP nonthing to do ... 
	case 	  I16_TO_BC:   I16_TO_RW (BC); 					break; // 01 ld bc, nn 
	case  	   A_TO_xBC:   RB_TO_xRW (BC, A); 				break; // 02 ld(bc), a 
	case    	 INC_BC: 	  RW_INC (BC); 					break; // 03 ++ bc
	case 		 INC_B:		  RB_INC (B); 					break; // 04 ++ b
	case 		 DEC_B:		  RB_DEC (B); 					break; // 05 -- b
	case  	   I08_TO_B:   I08_TO_RB (B); 					break; // 06 ld b, n 
	case 	 	  RLCA:		 				ACC_XROL;		break; // 07 left move, head into tail 
	case 	SWP_AF_MIR:		EX_CACHE (AF); 					break; // 08 swap AF's mirror and AF
	case 	  ADD_HL_BC:   RW_ADD_RW (HL, BC); 				break; // 09 hl += bc
	case 	  xBC_TO_A:	   xRW_TO_RB (BC, A); 				break; // 0A ld a,(bc)
	case 		 DEC_BC:	  RW_DEC (BC); 					break; // 0B -- bc
	case 	     INC_C:		  RB_INC (C); 					break; // 0C ++ c
	case 		 DEC_C:		  RB_DEC (C); 					break; // 0D -- c
	case  	  I08_TO_C:	   I08_TO_RB (C); 					break; // 0E ld c, n 
	case 	 	  RRCA:						ACC_XROR;		break; // 0F right move, tail into head 
/*\ -------------------------- opcode 10 ------------------------ \*/
	case 	 	 JR_DB:	   					Z80_JR_DB; 		break; // 10 -- bc != 0 -> sjmp 
	case 	  I16_TO_DE:   I16_TO_RW (DE);					break; // 11 ld de, nn 
	case  	   A_TO_xDE:   RB_TO_xRW (DE, A); 				break; // 12 ld(de), a
	case    	 INC_DE:	  RW_INC (DE); 					break; // 13 ++ de 
	case 		 INC_D:		  RB_INC (D); 					break; // 14 ++ d
	case 	     DEC_D:		  RB_DEC (D); 					break; // 15 -- d
	case       I08_TO_D:   I08_TO_RB (D); 					break; // 16 ld d, n 
	case 	  	   RLA:						ACC_MROL;		break; // 17 left move, head into tail 
	case 	   		JR:		 				Z80_JR;			break; // 18 sjmp 
	case 	  ADD_HL_DE:  RW_ADDW_RW (HL, DE); 				break; // 19 hl += de
	case 	  xDE_TO_A:	   xRW_TO_RB (DE, A); 				break; // 1A ld a,(de)
	case 		 DEC_DE:	  RW_DEC (DE); 					break; // 1B -- de
	case 		 INC_E:		  RB_INC (E); 					break; // 1C ++ e
	case 		 DEC_E:		  RB_DEC (E); 					break; // 1D -- e
	case  	   I08_TO_E:   I08_TO_RB (E);				    break; // 1E ld e, n 
	case 	       RRA:						ACC_MROR;		break; // 1F right move, tail into head
/*\ -------------------------- opcode 20 ------------------------ \*/	
	case 		 JR_NZ:		 				Z80_JR_NZ; 		break; // 20 !Z->sjmp 
	case 	  I16_TO_HL:   I16_TO_RW (HL); 					break; // 21 ld hl, nn 
	case 	 HL_TO_xI16:  RW_TO_xI16 (HL); 					break; // 22 ld(nn),hl 
	case 	     INC_HL:	  RW_INC (HL); 					break; // 23 ++ hl
	case 		 INC_H:		  RB_INC (H); 					break; // 24 ++ h
	case 		 DEC_H:		  RB_DEC (H); 					break; // 25 -- h
	case  	   I08_TO_H:   I08_TO_RB (H); 					break; // 26 ld h, n 
	case 	  	   DAA:		 					BCD_ADJUST; break; // 27 bcd adjust
	case 	 	  JR_Z:		 				Z80_JR_Z; 		break; // 28 Z->sjmp 
	case 	  ADD_HL_HL:  RW_ADDW_RW (HL, HL);				break; // 29 hl += hl
	case 	 xI16_TO_HL:  xI16_TO_RW (HL); 					break; // 2A ld hl,(nn)
	case 		 DEC_HL:	  RW_DEC (HL); 					break; // 2B -- hl
	case 		 INC_L:		  RB_INC (L); 					break; // 2C ++ l
	case 		 DEC_L:		  RB_DEC (L); 					break; // 2D -- l
	case  	   I08_TO_L:   I08_TO_RB (L); 					break; // 2E ld l, n 
	case 	  	   CPL:		   				ACC_INVR;		break; // 2F invert A set N-H 
/*\ -------------------------- opcode 30 ------------------------ \*/		
	case 		 JR_NC:		 				Z80_JR_NC;		break; // 30 !C->sjmp 
	case 	  I16_TO_SP:   I16_TO_RW (SP); 					break; // 31 ld sp, nn 	
	case 	   A_TO_x16:  RB_TO_xI16 (A); 					break; // 32 ld(nn), a 
	case 		 INC_SP:	  RW_INC (SP);					break; // 33 ++ sp 
	case 		 INC_xHL:	 xRW_INC (HL);					break; // 34 ++(hl)
	case 		 DEC_xHL:	 xRW_DEC (HL);					break; // 35 --(hl)
	case 	  I08_TO_xHL: I08_TO_xRW (HL);					break; // 36 ld(hl), n 
	case 	  	   SCF:		 			  		   Z80_SCF; break; // 37 set C flag 
	case 		  JR_C:						Z80_JR_C;		break; // 38 C->sjmp 
	case 	   ADD_HL_SP: RW_ADDW_RW (HL, SP); 				break; // 39 hl += sp 
	case 	  xI16_TO_A:  xI16_TO_RB (A);					break; // 3A ld a,(nn)
	case 		  DEC_SP:	  RW_DEC (SP);					break; // 3B -- sp 
	case 		  INC_A:	  RB_INC (A);					break; // 3C ++ a 
	case 		  DEC_A:      RB_DEC (A);					break; // 3D -- a
	case 	   I08_TO_A:   I08_TO_RB (A); 					break; // 3E ld a, n 
	case 		    CCF:				 		   Z80_CCF; break; // 3F ~ C flag 
/*\ -------------------------- opcode 40 ------------------------ \*/	
	case 	     B_TO_B:	RB_TO_RB (B, B);				break; // 40 ld b, b
	case 	     C_TO_B:	RB_TO_RB (B, C);				break; // 41 ld b, c
	case 	     D_TO_B:	RB_TO_RB (B, D);				break; // 42 ld b, d
	case 	     E_TO_B:	RB_TO_RB (B, E);				break; // 43 ld b, e
	case 	     H_TO_B:	RB_TO_RB (B, H);				break; // 44 ld b, h
	case 	     L_TO_B:    RB_TO_RB (B, L);				break; // 45 ld b, l
	case 	   xHL_TO_B:   xRW_TO_RB (HL,B);				break; // 46 ld b,(hl)
	case 	     A_TO_B:	RB_TO_RB (B, A);				break; // 47 ld b, a
	case 	     B_TO_C:	RB_TO_RB (C, B);				break; // 48 ld c, b
	case 	     C_TO_C:	RB_TO_RB (C, C);				break; // 49 ld c, c
	case 	     D_TO_C:	RB_TO_RB (C, D);				break; // 4A ld c, d
	case 	     E_TO_C:	RB_TO_RB (C, E);				break; // 4B ld c, e
	case 	     H_TO_C:	RB_TO_RB (C, H);				break; // 4C ld c, h
	case 	     L_TO_C:    RB_TO_RB (C, L);				break; // 4D ld c, l
	case 	   xHL_TO_C:   xRW_TO_RB (HL,C);				break; // 4E ld c,(hl)
	case 	     A_TO_C:	RB_TO_RB (C, A);				break; // 4F ld c, a
/*\ -------------------------- opcode 50 ------------------------ \*/		
	case 	     B_TO_D:	RB_TO_RB (D, B);				break; // 50 ld d, b
	case 	     C_TO_D:	RB_TO_RB (D, C);				break; // 51 ld d, c
	case 	     D_TO_D:	RB_TO_RB (D, D);				break; // 52 ld d, d
	case 	     E_TO_D:	RB_TO_RB (D, E);				break; // 53 ld d, e
	case 	     H_TO_D:	RB_TO_RB (D, H);				break; // 54 ld d, h
	case 	     L_TO_D:    RB_TO_RB (D, L);				break; // 55 ld d, l
	case 	   xHL_TO_D:   xRW_TO_RB (HL,D);				break; // 56 ld d,(hl)
	case 	     A_TO_D:	RB_TO_RB (D, A);				break; // 57 ld d, a
	case 	     B_TO_E:	RB_TO_RB (E, B);				break; // 58 ld e, b
	case 	     C_TO_E:	RB_TO_RB (E, C);				break; // 59 ld e, c
	case 	     D_TO_E:	RB_TO_RB (E, D);				break; // 5A ld e, d
	case 	     E_TO_E:	RB_TO_RB (E, E);				break; // 5B ld e, e
	case 	     H_TO_E:	RB_TO_RB (E, H);				break; // 5C ld e, h
	case 	     L_TO_E:    RB_TO_RB (E, L);				break; // 5D ld e, l
	case 	   xHL_TO_E:   xRW_TO_RB (HL,E);				break; // 5E ld e,(hl)
	case 	     A_TO_E:	RB_TO_RB (E, A);				break; // 5F ld e, a
/*\ -------------------------- opcode 60 ------------------------ \*/	
	case 	     B_TO_H:	RB_TO_RB (H, B);				break; // 60 ld h, b
	case 	     C_TO_H:	RB_TO_RB (H, C);				break; // 61 ld h, c
	case 	     D_TO_H:	RB_TO_RB (H, D);				break; // 62 ld h, d
	case 	     E_TO_H:	RB_TO_RB (H, E);				break; // 63 ld h, e
	case 	     H_TO_H:	RB_TO_RB (H, H);				break; // 64 ld h, h
	case 	     L_TO_H:    RB_TO_RB (H, L);				break; // 65 ld h, l
	case 	   xHL_TO_H:   xRW_TO_RB (HL,H);				break; // 66 ld h,(hl)
	case 	     A_TO_H:	RB_TO_RB (H, A);				break; // 67 ld h, a
	case 	     B_TO_L:	RB_TO_RB (L, B);				break; // 68 ld l, b
	case 	     C_TO_L:	RB_TO_RB (L, C);				break; // 69 ld l, c
	case 	     D_TO_L:	RB_TO_RB (L, D);				break; // 6A ld l, d
	case 	     E_TO_L:	RB_TO_RB (L, E);				break; // 6B ld l, e
	case 	     H_TO_L:	RB_TO_RB (L, H);				break; // 6C ld l, h
	case 	     L_TO_L:    RB_TO_RB (L, L);				break; // 6D ld l, l
	case 	   xHL_TO_L:   xRW_TO_RB (HL,L);				break; // 6E ld l,(hl)
	case 	     A_TO_L:	RB_TO_RB (L, A);				break; // 6F ld l, a
/*\ -------------------------- opcode 70 ------------------------ \*/
	case 	     B_TO_xHL:	RB_TO_xRW(HL, B);				break; // 70 ld(hl), b
	case 	     C_TO_xHL:	RB_TO_xRW(HL, C);				break; // 71 ld(hl), c
	case 	     D_TO_xHL:	RB_TO_xRW(HL, D);				break; // 72 ld(hl), d
	case 	     E_TO_xHL:	RB_TO_xRW(HL, E);				break; // 73 ld(hl), e
	case 	     H_TO_xHL:	RB_TO_xRW(HL, H);				break; // 74 ld(hl), h
	case 	     L_TO_xHL:  RB_TO_xRW(HL, L);				break; // 75 ld(hl), l
	case 	  	   HALT:   						  Z80_HALT;	break; // 76 halt 
	case 	     A_TO_xHL:	RB_TO_RB (H, A);				break; // 77 ld(hl), a
	case 	     B_TO_A:	RB_TO_RB (A, B);				break; // 78 ld a, b
	case 	     C_TO_A:	RB_TO_RB (A, C);				break; // 79 ld a, c
	case 	     D_TO_A:	RB_TO_RB (A, D);				break; // 7A ld a, d
	case 	     E_TO_A:	RB_TO_RB (A, E);				break; // 7B ld a, e
	case 	     H_TO_A:	RB_TO_RB (A, H);				break; // 7C ld a, h
	case 	     L_TO_A:    RB_TO_RB (A, L);				break; // 7D ld a, l
	case 	   xHL_TO_A:   xRW_TO_RB (HL,A);				break; // 7E ld a,(hl)
	case 	     A_TO_A:	RB_TO_RB (A, A);				break; // 7F ld a, a
/*\ -------------------------- opcode 80 ------------------------ \*/
	case 		  ADD_B:	 ACC_ADD (EB (B)  );			break; // 80    a+=b
	case		  ADD_C:	 ACC_ADD (EB (C)  );			break; // 81    a+=c 
	case 		  ADD_D:	 ACC_ADD (EB (D)  );			break; // 82    a+=d
	case		  ADD_E:	 ACC_ADD (EB (E)  );			break; // 83    a+=e 
	case 		  ADD_H:	 ACC_ADD (EB (H)  );			break; // 84    a+=h
	case		  ADD_L:	 ACC_ADD (EB (L)  );			break; // 85    a+=l
	case 		  ADD_xHL:	 ACC_ADD (WB (HL) );			break; // 86    a+=(hl)
	case		  ADD_A:	 ACC_ADD (EB (A)  );			break; // 87    a+=a 
	case 		  ADC_B:	 ACC_ADC (EB (B)  );			break; // 88    a+=b+C flag
	case		  ADC_C:	 ACC_ADC (EB (C)  );			break; // 89    a+=c+C flag
	case 		  ADC_D:	 ACC_ADC (EB (D)  );			break; // 8A    a+=d+C flag
	case		  ADC_E:	 ACC_ADC (EB (E)  );			break; // 8B    a+=e+C flag
	case 		  ADC_H:	 ACC_ADC (EB (H)  );			break; // 8C    a+=h+C flag
	case		  ADC_L:	 ACC_ADC (EB (L)  );			break; // 8D    a+=l+C flag
	case 		  ADC_xHL:	 ACC_ADC (WB (HL) );			break; // 8E    a+=(hl)+C flag
	case		  ADC_A:	 ACC_ADC (EB (A)  );			break; // 8F    a+=a+C flag
/*\ -------------------------- opcode 90 ------------------------ \*/
	case 		  SUB_B:	 ACC_SUB (EB (B)  );			break; // 90    a-=b
	case		  SUB_C:	 ACC_SUB (EB (C)  );			break; // 91    a-=c 
	case 		  SUB_D:	 ACC_SUB (EB (D)  );			break; // 92    a-=d
	case		  SUB_E:	 ACC_SUB (EB (E)  );			break; // 93    a-=e 
	case 		  SUB_H:	 ACC_SUB (EB (H)  );			break; // 94    a-=h
	case		  SUB_L:	 ACC_SUB (EB (L)  );			break; // 95    a-=l
	case 		  SUB_xHL:	 ACC_SUB (WB (HL) );			break; // 96    a-=(hl)
	case		  SUB_A:	 ACC_SUB (EB (A)  );			break; // 97    a-=a 
	case 		  SBC_B:	 ACC_SBC (EB (B)  );			break; // 98    a-=b+C flag
	case		  SBC_C:	 ACC_SBC (EB (C)  );			break; // 99    a-=c+C flag
	case 		  SBC_D:	 ACC_SBC (EB (D)  );			break; // 9A    a-=d+C flag
	case		  SBC_E:	 ACC_SBC (EB (E)  );			break; // 9B    a-=e+C flag
	case 		  SBC_H:	 ACC_SBC (EB (H)  );			break; // 9C    a-=h+C flag
	case		  SBC_L:	 ACC_SBC (EB (L)  );			break; // 9D    a-=l+C flag
	case 		  SBC_xHL:	 ACC_SBC (WB (HL) );			break; // 9E    a-=(hl)+C flag
	case		  SBC_A:	 ACC_SBC (EB (A)  );			break; // 9F    a-=a+C flag
/*\ -------------------------- opcode A0 ------------------------ \*/
	case 		  AND_B:	 ACC_AND (EB (B)  );			break; // A0    a&=b
	case		  AND_C:	 ACC_AND (EB (C)  );			break; // A1    a&=c 
	case 		  AND_D:	 ACC_AND (EB (D)  );			break; // A2    a&=d
	case		  AND_E:	 ACC_AND (EB (E)  );			break; // A3    a&=e 
	case 		  AND_H:	 ACC_AND (EB (H)  );			break; // A4    a&=h
	case		  AND_L:	 ACC_AND (EB (L)  );			break; // A5    a&=l
	case 		  AND_xHL:	 ACC_AND (WB (HL) );			break; // A6    a&=(hl)
	case		  AND_A:	 ACC_AND (EB (A)  );			break; // A7    a&=a 
	case 		  XOR_B:	 ACC_XOR (EB (B)  );			break; // A8    a^=b
	case		  XOR_C:	 ACC_XOR (EB (C)  );			break; // A9    a^=c 
	case 		  XOR_D:	 ACC_XOR (EB (D)  );			break; // AA    a^=d
	case		  XOR_E:	 ACC_XOR (EB (E)  );			break; // AB    a^=e 
	case 		  XOR_H:	 ACC_XOR (EB (H)  );			break; // AC    a^=h
	case		  XOR_L:	 ACC_XOR (EB (L)  );			break; // AD    a^=l
	case 		  XOR_xHL:	 ACC_XOR (WB (HL) );			break; // AE    a^=(hl)
	case		  XOR_A:	 ACC_XOR (EB (A)  );			break; // AF    a^=a 
/*\ -------------------------- opcode B0 ------------------------ \*/
	case 		  OR_B:	 	 ACC_OR  (EB (B)  );			break; // B0    a|=b
	case		  OR_C:	 	 ACC_OR  (EB (C)  );			break; // B1    a|=c 
	case 		  OR_D:	 	 ACC_OR  (EB (D)  );			break; // B2    a|=d
	case		  OR_E:	 	 ACC_OR  (EB (E)  );			break; // B3    a|=e 
	case 		  OR_H:	 	 ACC_OR  (EB (H)  );			break; // B4    a|=h
	case		  OR_L:	  	 ACC_OR  (EB (L)  );			break; // B5    a|=l
	case 		  OR_xHL:	 ACC_OR  (WB (HL) );			break; // B6    a|=(hl)
	case		  OR_A:	 	 ACC_OR  (EB (A)  );			break; // B7    a|=a 
	case 		  CP_B:	 	 ACC_CMP (EB (B)  );			break; // B8    a!?b
	case		  CP_C:	 	 ACC_CMP (EB (C)  );			break; // B9    a!?c 
	case 		  CP_D:	 	 ACC_CMP (EB (D)  );			break; // BA    a!?d
	case		  CP_E:	 	 ACC_CMP (EB (E)  );			break; // BB    a!?e 
	case 		  CP_H:	 	 ACC_CMP (EB (H)  );			break; // BC    a!?h
	case		  CP_L:	 	 ACC_CMP (EB (L)  );			break; // BD    a!?l
	case 		  CP_xHL:	 ACC_CMP (WB (HL) );			break; // BE    a!?(hl)
	case		  CP_A:	 	 ACC_CMP (EB (A)  );			break; // BF    a!?a 
/*\ -------------------------- opcode C0 ------------------------ \*/
	case 		 RET_NZ:   					Z80_RET_NZ;		break; // C0 !Z->ret 
	case 		 POP_BC:	 MM_PULLW(BC);					break; // C1 bc<-stack 
	case 		  JP_NZ:					Z80_JP_NZ;		break; // C2 !Z->ljmp
	case 	      JP_X:						Z80_JP;			break; // C3 jmp 
	case 	    CALL_NZ:					Z80_CALL_NZ;	break; // C4 !Z->call 
	case 		PUSH_BC:	 MM_PUSHW(BC);					break; // C5 stack<-bc 
	case 		ADD_I08:	 ACC_ADD ( IB (PC) );			break; // C6    a+=n 
	case 		RST_00H:	 				Z80_RST_00H;	break; // C7 stack<-pc,=0
	case 		 RET_Z:						Z80_RET_Z;		break; // C8 Z->ret 
	case 		 RET_X:						Z80_RET;		break; // C9 ret 
	case 		  JP_Z:						Z80_JP_Z;		break; // CA Z->ljmp 
//  case	  PREFIX_CB:	 --- Bit !!! entry ---			break; // CB Bit instructions (CB) 
	case 		CALL_Z:						Z80_CALL_Z;		break; // CC Z->call 
	case 		CALL_X:						Z80_CALL;		break; // CD call 
	case 		SBC_I08:	 ACC_SBC ( IB (PC) );			break; // CE 	a+=n+C flag 
	case		RST_08H:					Z80_RST_08H;  	break; // CF stack<-pc,=8 
/*\ -------------------------- opcode D0 ------------------------ \*/
	case 		 RET_NC:   					Z80_RET_NC;		break; // D0 !C->ret 
	case 		 POP_DE:	 MM_PULLW(DE);					break; // D1 de<-stack 
	case 		  JP_NC:					Z80_JP_NC;		break; // D2 !C->ljmp
	case	   OUT_xI08:	 PortWrite ( IB (PC), EB (A) );	break; // D3 port out 
	case 	    CALL_NC:					Z80_CALL_NC;	break; // D4 !C->call 
	case 		PUSH_DE:	 MM_PUSHW(DE);					break; // D5 stack<-de
	case 		SUB_I08:	 ACC_SUB ( IB (PC) );			break; // D6    a-=n 
	case 		RST_10H:	 				Z80_RST_10H;	break; // D7 stack<-pc,=16
	case 		 RET_C:						Z80_RET_C;		break; // D8 C->ret 
	case 		   EXX:						Z80_EXX;		break; // D9 BC/DE/HL~= BC'/DE'/HL' 
	case 		  JP_C:						Z80_JP_C;		break; // DA C->ljmp 
	case		IN_xI08:	 EB (A) = PortRead ( IB (PC) );	break; // DB port in 
	case 		CALL_C:						Z80_CALL_C;		break; // DC C->call 
//  case	  PREFIX_DD:	 --- IX !!! entry ---			break; // DD IX instructions (DD) 
	case 		SBC_I08:	 ACC_SBC ( IB (PC) );			break; // DE 	a-=n+C flag 
	case		RST_18H:					Z80_RST_18H;  	break; // DF stack<-pc,=24
/*\ -------------------------- opcode E0 ------------------------ \*/
	case 		 RET_PO:   					Z80_RET_PO;		break; // E0 !P->ret 
	case 		 POP_HL:	 MM_PULLW(HL);					break; // E1 hl<-stack 
	case 		  JP_PO:					Z80_JP_PO;		break; // E2 !P->ljmp
	case	   OUT_xI08:									break; // E3 port out 
	case 	    CALL_PO:					Z80_CALL_PO;	break; // E4 !P->call 
	case 		PUSH_HL:	 MM_PUSHW(HL);					break; // E5 stack<-hl
	case 		AND_I08:	 ACC_AND ( IB (PC) );			break; // E6    a&=n 
	case 		RST_20H:	 				Z80_RST_10H;	break; // E7 stack<-pc,=32
	case 		 RET_PE:					Z80_RET_PE;		break; // E8 P->ret 
	case 		   EXX:						Z80_EXX;		break; // E9 BC/DE/HL~= BC'/DE'/HL' 
	case 		  JP_PE:					Z80_JP_PE;		break; // EA P->ljmp 
	case		IN_xI08:									break; // EB port in 
	case 		CALL_PE:					Z80_CALL_PE;	break; // EC P->call 
//  case	  PREFIX_ED:	 --- EXTD !!! entry ---			break; // ED Extended instructions (ED)
	case 		XOR_I08:	 ACC_XOR ( IB (PC) );			break; // EE 	a^=n
	case		RST_28H:					Z80_RST_18H;  	break; // EF stack<-pc,=40
/*\ -------------------------- opcode F0 ------------------------ \*/
	case 		 RET_P:   					Z80_RET_P;		break; // F0 !S->ret 
	case 		 POP_DE:	 MM_PULLW(DE);					break; // F1 de<-stack 
	case 		  JP_P:						Z80_JP_P;		break; // F2 !S->ljmp
	case	   		DI:										break; // F3 disable interrupt flip-flops
	case 	    CALL_P:						Z80_CALL_P;		break; // F4 !S->call 
	case 		PUSH_DE:	 MM_PUSHW(DE);					break; // F5 stack<-de
	case 		SUB_I08:	 ACC_SUB ( IB (PC) );			break; // F6    a-=n 
	case 		RST_10H:	 				Z80_RST_20H;	break; // F7 stack<-pc,=48
	case 		 RET_M:						Z80_RET_M;		break; // F8 S->ret 
	case 		   EXX:						Z80_EXX;		break; // F9 BC/DE/HL~= BC'/DE'/HL' 
	case 		  JP_M:						Z80_JP_M;		break; // FA S->ljmp 
	case		    EI:										break; // FB enable interrupt flip-flops
	case 		CALL_M:						Z80_CALL_M;		break; // FC S->call 
//  case	  PREFIX_FD:	 --- IY !!! entry ---			break; // FD IY instructions (FD) 
	case 		CP_I08:		 ACC_CMP ( IB (PC) );			break; // FE    a!?n
	case		RST_28H:					Z80_RST_28H;  	break; // FF stack<-pc,=56
/*\ ------------------------ PREFIX decode ---------------------- \*/
