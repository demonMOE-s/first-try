/*-
 * Copyright (c) 2016 moecmks
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND COnametable_RIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR COnametable_RIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN COnametable_RACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
 
#include "inline.h"
#include <stdarg.h> 
#include <stdio.h> /* for vsprintf */

/* ===================================================================*/
FINLINE
void swap_tebl (struct tile_s *T, 
                const int32_t l, 
                const int32_t r) 
{  
  int32_t rtol_count;
  int32_t ltor_count;
  /*
   * Swap pixels_select, pixels_counts
   */
  _SWAP_OBJECT(int32_t, &T->dattable_sel[l], &T->dattable_sel[r]);
  _SWAP_OBJECT(int32_t, &T->dattable_count[l], &T->dattable_count[r]);

  /*
   * Swap mapper_select table right to left
   */
  for (rtol_count = 0; rtol_count != 64; rtol_count++)
    if (T->maptable_sel[rtol_count] == l) {
        /* Swap, directly */
        T->maptable_sel[rtol_count]  = r;
    } else if (T->maptable_sel[rtol_count] == r) {
        /* Set flags */
        T->maptable_sel[rtol_count]  = -2;      
    }
      
  /*
   * Swap mapper_select table left to right
   */   
  for (ltor_count = 0; ltor_count != 64; ltor_count++)
    if (T->maptable_sel[ltor_count] == -2) {
        /* Swap, at cur flags pos */
        T->maptable_sel[ltor_count]  = l;
    }
}
/* ========================================================== */
FINLINE 
int32_t partition (struct tile_s *T, 
                   int32_t l, 
                   int32_t r) 
{
  int32_t i;
  int32_t c = T->dattable_count[r];
    
  for (i = l - 1; l <= r - 1; l++) 
    if (T->dattable_count[l] >= c)
        /* Swap tile */
        swap_tebl (T, ++i, l);
  /* Last pass */
  swap_tebl (T, ++i, r);
            
  return i;
}
/* ============================================================= */
FINLINE 
void rebedye_Palette_NOwarp(struct core_s *CE, struct tile_s *P) {
    
  int32_t z = 0;
  int32_t g;

  int32_t p;
  int32_t l;
  int32_t r; 
  int32_t top;
  int32_t stack[64];    
 
  int32_t T = CE->bg_trans & 0x00FFFFFF; 
    
  for (; z != 64; z++) {
           
    P->dattable_sel[z] = T;
    P->dattable_count[z] = 0;
    P->maptable_sel[z] = -1;
    P->dattable_nat[z] = 1;
  }       

  P->datcount_type = 0; /* Init Count-type */
  P->datcount_numb = 0; /* Init Count-numb */
       
  for 
  (z = 0; z != 64; z++) {
           
    if (P->dattable_org[z] != T) {
                
        /* Atom pixel */
        P->datcount_numb++;      

        /* Set notrans */
        P->dattable_nat[z] = 0;

        /* Test whether to repeat the color selection list */
        for (g = 0; P->dattable_sel[g] != T; g++)

             if (P->dattable_sel[g] == P->dattable_org[z]) {
              
                 /* Atom cur pixel select table 's count */
                 P->dattable_count[g]++;
              
                 /* Ignore pixel select table */
                 goto repeat_;
             }
                  
             /* No repeat:add new pixel in pixel select table .
              * Set init pixel count, Atom type count, and mapper table
              */
             P->dattable_sel[P->datcount_type] = P->dattable_org[z];
             P->dattable_count[P->datcount_type++] = 1;
              
     repeat_:P->maptable_sel[z] = g;
      
    }
  }  
  /*
   * fully transparent
   */
  if (P->datcount_type == 0)
       return;
  /*
   * Inline tile iterative-quicksort
   */
  top = 1;
  stack[0] = 0;
  stack[1] = P->datcount_type - 1;

  while (top >= 0) {
       
     r = stack[top--];
     l = stack[top--];
     
     p = partition (P, l, r);
     
    /* 
     * Left side of pivot
     */          
     if (p - 1 > l) {
         stack[++top] = l;
         stack[++top] = p - 1;
     }
    /* 
     * Right side of pivot
     */
     if (p + 1 < r) {
         stack[++top] = p + 1;
         stack[++top] = r;
     }
  }
}
/* ===================================================================== */
FINLINE
void rebedye_Primitive_NOwarp (struct core_s *CE, struct tile_s *R)
{
  int32_t i;
    
  for (i = 0; i != 64; i++)
    if (!R->dattable_nat[i])
  /* Copy mapper */
         R->dattable_org[i] = R->dattable_sel[R->maptable_sel[i]];
    else 
         R->dattable_org[i] = CE->bg_trans;         
}
/* =========================================================================== */
FINLINE
uint32_t *decode_tebl (struct core_s *CE, struct tile_s *R, const int bmap)
{
  static 
  int32_t T[64];
    
  int32_t i;
    
  if (!bmap) 
      return memcpy (&T[0], &R->dattable_org[0], 256);
  else for (i = 0; i != 64; i++)
         if (!R->dattable_nat[i])
  /* Copy mapper */
              T[i] = R->dattable_sel[R->maptable_sel[i]];
         else 
              T[i] = CE->bg_trans;
  return &T[0];
}
/* ================================================================= */
FINLINE
uint32_t *decode_tebl_ (struct core_s *CE, struct tile_s *R, const int bmap, int32_t *D)
{
  int32_t i;
    
  if (!bmap) 
      return &R->dattable_org[0];
  else for (i = 0; i != 64; i++)
         if (!R->dattable_nat[i])
  /* Copy mapper */
              D[i] = R->dattable_sel[R->maptable_sel[i]];
         else 
              D[i] = CE->bg_trans;         
  return &D[0];
}
/* ================================================================= */
FINLINE
int8_t *decode_font (uint8_t *R)
{
  static 
  int8_t T[64];
  
  int i;
  for (i = 0; i != 64; i++)
       T[i] = !!(R[i >> 3] & (1 << i % 8));
  return &T[0];
}       
/* ================================================================= */
FINLINE 
uint32_t RGB_concoct (const int32_t data, const uint8_t shirk) 
{
  uint32_t x, y, z;
 
  x = data & 0x000000FF; //
  y = data & 0x0000FF00; //
  z = data & 0x00FF0000; // limit range 
    
  x = x * shirk / 256 & 0x000000FF; //
  y = y * shirk / 256 & 0x0000FF00; //
  z = z * shirk / 256 & 0x00FF0000; // strong reduce | FIXME:div/shift
    
  return (x | y | z);  
}
/* ================================================================= */
FINLINE 
uint32_t saddudt (const uint32_t s, const uint32_t s2) 
{
  uint32_t x, y, z;
  
  x = (s & 0x000000FF) + (s2 & 0x000000FF); //
  y = (s & 0x0000FF00) + (s2 & 0x0000FF00); //
  z = (s & 0x00FF0000) + (s2 & 0x00FF0000); // cross add 
  
  if (x > 0x000000FF) x = 0x000000FF; //
  if (y > 0x0000FF00) y = 0x0000FF00; // 
  if (z > 0x00FF0000) z = 0x00FF0000; // limit range 

  return (x | y | z);  
}
/* ============================================================================== */
FINLINE 
uint32_t RGB_concoct_mix (uint32_t ag, uint32_t ag2, uint8_t ag_s, uint8_t ag_s2) 
{
  return saddudt ( RGB_concoct (ag,  ag_s), 
                   RGB_concoct (ag2, ag_s2));  
}
/* =============================================================================================== */
FINLINE
struct tile_s *tile_domain (struct core_s *CE, uint32_t fk, uint8_t section, uint8_t impact)
{
  return &CE->R_mesh[((uintptr_t)(fk & TEB_CACHE)) / 4 * 65536 + 256 * (uintptr_t)section + (uintptr_t)impact]; 
  // ## FIXME:bad affect type<enum mask> to int32
  // ## FIXME:memory layout dependency    
}
/* ============================================================= */
FINLINE
struct bg_chunk_s *bg_chunk_domain (struct core_s *CE)
{
  return &CE->map[(((uintptr_t)(CE->msc.vram_quad)) << 10) + CE->msc.x_ram_access +
                   (((uintptr_t)(CE->msc.y_ram_access)) << 5)];  
}
/* ============================================================= */
FINLINE
int32_t amclist_hadd (struct sp_amc_s *P, struct sp_amc_s *D)
{
  struct sp_amc_s *N = _MALLOC (sizeof(struct sp_amc_s));
  if (!N) 
    return -1;
  memcpy (N, D, sizeof(struct sp_amc_s));
  N->nst = P->nst;
  P->nst = N;
  return 0;
}
/* ============================================================= */
FINLINE
void amclist_die_gc (struct sp_amc_s *P)
{
  struct sp_amc_s *S;
  struct sp_amc_s *N;
  S = P->nst;
  P->nst = null;
  for (; S != null; S = N)
      N = S->nst, _FREE (S);//, P->isvailed = 0; // FIXME:...-_-
}
/* ============================================================= */
FINLINE
void _amc_destroy (struct core_s *CE)
{
  uint32_t I = 0;
  uint32_t P = CE->amc_limit << 1;
  uint8_t *SP = &CE->amc_coord_slot[2184 << 1];
  struct sp_amc_s *AMC = &CE->amc_pool[2184];
  
  for (; I != P; I += 2)
         amclist_die_gc (&AMC[_CSV(SP[I+1]) + SP[I]]);
     
  CE->amc_limit = 0; 
  memset(&CE->amc_hits[0], 0x00, sizeof(CE->amc_hits));
}
/* ============================================================= */
FINLINE
void _alpha (uint32_t *D, uint32_t DATA, uint8_t *A, uint8_t AP)
{
#define I (_CSV(n)+k)
#define EFINES                   \
  int32_t n, k;                  \
  for (n = 0; n != 240; n++)     \
       for (k = 0; k != 256; k++) 
  EFINES           
  if (!A[I]) D[I] = RGB_concoct_mix(D[I], DATA, AP, 255 - AP);
}
/* ============================================================= */  
FINLINE
void _alpha2 (uint32_t *D, uint32_t DATA, uint8_t AP)
{
  EFINES
  D[I] = RGB_concoct_mix(D[I], DATA, AP, 255 - AP);
}
/* ============================================================= */
FINLINE
void _memcpy (int32_t *D, int32_t *S, int8_t *A)
{
  EFINES 
  if (!A[I]) D[I] = S[I];
         
#undef EFINES
#undef I
}   
           
#define AMC_NODONE ((void)0)
#define AMC_INSERT                                 \
  AM.data = DTB2[-1];                              \
  AM.x_coord = AM.x_coord_std + (7 - g);           \
  AM.y_coord = AM.y_coord_std + t;                 \
  AM.x_coord_imp = z & 7;                          \
  AM.y_coord_imp = (z & 56) >> 3;                  \
{                                                  \
  uintptr_t w = _CSV(AM.y_coord) + AM.x_coord;     \
  if (0 == amc_hits[w]) {                          \
      amc_hits[w] = 1;                             \
      amc_coord_slot[CE->amc_limit << 1] = AM.x_coord;         \
      amc_coord_slot[CE->amc_limit  * 2 + 1] = AM.y_coord;     \
      CE->amc_limit++;                            \
  }                                                \
  amclist_hadd (&AS[w], &AM);                      \
}
  
#define BG_RENDER_BANK(fs,cs)                               \
case (fs):                                       \
for (; z != s; /* loop out y count */            \
      ABF = &ABF[264], DBF = &DBF[264], z += k) \
 for (g = 8; /* loop out x count */              \
      g-- != 0; z += a)                          \
      if (*ABF++ = T->dattable_nat[z])        \
          *DBF++ = CE->bg_trans;                        \
      else                                       \
          *DBF++ = (cs);                      \
 break
 
#define SP_RENDER_BANK(fs,cs,am)                     \
case (fs):                                       \
t = 0;                                               \
for (; z != s; t += 1, /* loop out y count */    \
      ATB2 = &ATB2[264], DTB2 = &DTB2[264], z += k)  \
 for (g = 8; /* loop out x count */              \
      g-- != 0; z += a)                          \
      if ((*ATB2 != _flags)                          \
      && (0 == T->dattable_nat[z])) {            \
          *ATB2++ = T->dattable_nat[z];          \
          *DTB2++ = cs;                          \
           am;                                   \
      } else {                                   \
           ATB2++;                               \
           DTB2++;                               \
      }                                          \
      break
      
/* ============================================================= */
static //FIXME
void bgticks (struct core_s *CE)
{
  uintptr_t ISR0, _ISR0, ISR2, ISR7;
  uintptr_t LFF0, LFF2, LFF7;  
  uintptr_t i, x, y = 31, mask;
  uint32_t *DBF; 
  uint8_t *ABF;
  
  struct tile_s *T; 
  struct bg_chunk_s *B, *I, *H, *R;   
      
  ISR7 = (CE->msc.nametable_quad & 3) << 10; 
  ISR0 = ISR7 & 1024; 
  ISR2 = ISR7 & 2048;
 _ISR0 = ISR0 ^ 1024;
 
  LFF2 =(CE->msc.y_map_scroll >> 3) << 5;
  LFF0 = CE->msc.x_map_scroll >> 3;
  LFF7 = LFF0; 
  
  i = CE->msc.y_map_scroll & 7;
  i = 2184 - _CSV(i) - (CE->msc.x_map_scroll & 7);
  
  B = &CE->map[0]; 
  H = &B[ISR0 + LFF0]; 
  I = &H[ISR2 + LFF2];  
  R = &B[ISR2 + LFF2 + _ISR0]; 
  
  /* calc init offset screen pixel pointer/misc param */
  DBF = &CE->sub_data[i]; 
  ABF = &CE->sub_slot[i]; 

  /* render <33*31 Tiles[264*248]>
     this could be a very slow process */
  do {
      /* main loop, each scan 33 tiles */
      for (x = 33; x != 0; x--) {
          
         uintptr_t s, z; 
         uintptr_t g, k, a;
         
         /* Get tile_s 's mask */
         mask = I->mask;
         
         /* do CACHE deal, if use cache, we will 
            read data from RW_mesh */
         T = 
         tile_domain (CE, mask & TEB_CACHE, 
                I->section, I->impact); // FIXME:myabe,...more value
                    
         /* Hori/Vert mapper */
         switch (mask & 
         (TEB_HFLIP | TEB_VFLIP)) {
             
         case 0:
            s = 64;
            z = 0;
            a = 1;
            k = 0;
            break;
            
         case TEB_HFLIP:
            s = 71;
            z = 7;
            a =-1;
            k = 16;
            break;
            
         case TEB_VFLIP:
            s = -8;
            z = 56;
            a = 1;
            k =-16;
            break;
            
         case (TEB_HFLIP | TEB_VFLIP):
            s = -1;
            z = 63;
            a = -1;
            k =  0;
            break;
         }

         /* Draw buffer. it may not be so efficient */
         switch (mask & 
         (TEB_MAPPER | TEB_ALPHA)) {
                        
         /*
          * MAPPER:
          *
          * use palette mode, first check cur tile chunk
          * (8*8 pixel martix) 's attr, if trans then nodraw
          * second,  
Use a selection table to map a lookup table to get a real pixel
          */      
         BG_RENDER_BANK(TEB_MAPPER, T->dattable_sel[T->maptable_sel[z]]);
           
         /*
          * ALPHA:
          *
          * simple vector normalization
          *
          * formula:
          * result(rR/rG/rB) = alpha*(dR/dG/dB)+(255-alpha)*(sR/sG/sB)
          * 
          * des:background pixels of the current coordinates
          * src:transparent color of the current ppu element
          */             
         BG_RENDER_BANK(TEB_ALPHA, RGB_concoct_mix(CE->bg_trans, T->dattable_org[z], 
                0xFF ^ I->blend, I->blend));                          
    
         /*
          * ALPHA && MAPPER:
          */               
         BG_RENDER_BANK(TEB_MAPPER | TEB_ALPHA, RGB_concoct_mix(CE->bg_trans, 
                T->dattable_sel[T->maptable_sel[z]], 0xFF ^ I->blend, I->blend));   
                
         /*
          * noaffect
          */       
         BG_RENDER_BANK(0, T->dattable_org[z]);
#undef   BG_RENDER_BANK         
         }
         
         /* if LFF7 equal 32, then next action will cross
            x page, switch hori nametable */
         I = ++LFF7 != 32 ? &I[1] : &R[0];  
         
         /* back to correctly buffer */
         DBF = &DBF[-2168];
         ABF = &ABF[-2168];
      }         
      /* if LFF2 equal 960, then next action will cross
         y page, switch vert nametable */
      if ((LFF2 += 32) != 960)                      
           I = &H[LFF2 + ISR2];                     
      else {                                                      
           I = &H[LFF2];  
           
           ISR2 ^= 2048;                         
           LFF2 = 0;               
      }            
      
      /* back to correctly buffer */      
      DBF = &DBF[1912];
      ABF = &ABF[1912];
      
      /* reset cross x page ptr */
      R = &B[ISR2 + _ISR0 + LFF2];
      
      /* reset scroll y */
      LFF7 = LFF0;
        
  } while (--y);
}
/* ============================================================= */
static 
void spticks (struct core_s *CE)
{     
  uintptr_t x_coord, y_coord, mask, blend;
  uintptr_t i = 255, u, t, chan;
  uint32_t *DTB, *DTB2, *TBUF; 
  uint8_t _flags, *ATB, *ATB2, *amc_hits, *amc_coord_slot;
  uint32_t dt_cache[64];
  
  struct tile_s *T; 
  struct sp_chunk_s *P;
  struct sp_amc_s AM, *AS;  
  
  /* Init screen pos */
  ATB = &CE->sub_slot[2184];
  DTB = &CE->sub_data[2184];
  /* Init AMC */
  AS = &CE->amc_pool[2184];
  AM.nst = null;  
  /* Init SPROBB */
  P = &CE->oam[255];
  /* clear hit area */
  amc_hits = &CE->amc_hits[2184];
  /* lock init slot */
  amc_coord_slot = &CE->amc_coord_slot[2184 << 1];
  /* Rebuild init status */
  _amc_destroy(CE);
  
  do {
      uintptr_t s, z; 
      uintptr_t g, k, a;
         
      /* channel index */
      chan = P->chan & 7;
      
      if (P->mask_common & TES_FLAGS_GLOBAL)
           mask = P->mask_common & ~TES_FLAGS_GLOBAL;
      else 
           mask = P->mask[chan];

      if (mask & TES_CLOSE)
            goto __final;
        
      if (mask & TES_SEAT_GLOBAL) 
           x_coord = P->x_coord_common, y_coord = P->y_coord_common;
      else
           x_coord = P->x_coord[chan], y_coord = P->y_coord[chan];          
      
      if (y_coord > 239)
            goto __final;
       
      if (mask & TES_ALPHA_GLOBAL) 
           blend = P->l_blend_common;
      else
           blend = P->blend[chan];   
       
      if (mask & TES_BACK)
          _flags = 0;
      else 
          _flags = 0xDF;      
      
      u = _CSV(y_coord) + x_coord; // FIXME:mul

      /* Hori/Vert mapper */
      switch (mask & 
      (TES_HFLIP | TES_VFLIP)) {
         
      case 0:
        s = 64;
        z = 0;
        a = 1;
        k = 0;
        break;
        
      case TES_HFLIP:
        s = 71;
        z = 7;
        a =-1;
        k = 16;
        break;
        
      case TES_VFLIP:
        s = -8;
        z = 56;
        a = 1;
        k =-16;
        break;
        
      case (TES_HFLIP | TES_VFLIP):
        s = -1;
        z = 63;
        a = -1;
        k =  0;
        break;
      }
       
      AM.x_coord_std = x_coord;
      AM.y_coord_std = y_coord;  
      AM.section = P->section[chan];
      AM.impact = P->impact[chan];
      AM.slot = i; // slot 
      AM.chan = chan; // channel mask
      AM.mask = mask; // flags mask
      
      ATB2 = &ATB[u];
      DTB2 = &DTB[u];    
      
      T = &P->cache[chan];

      TBUF = decode_tebl_(CE, T, mask & TES_MAPPER, &dt_cache[0]);    
      
      switch (mask &
      (TES_ALPHA | TES_AMC_APPEND)) {

      /*
       * ALPHA:
       *
       * simple vector normalization
       *
       * formula:
       * result(rR/rG/rB) = alpha*(dR/dG/dB)+(255-alpha)*(sR/sG/sB)
       * 
       * des:background pixels of the current coordinates
       * src:sprite pixels of the current coordinates
       */             
      SP_RENDER_BANK(TES_ALPHA, RGB_concoct_mix(*DTB2, TBUF[z], 
            0xFF ^ blend, blend), AMC_NODONE);   
            
      /*
       * AMC_APPEND:
       *
       * Add a collision chain information for the current pixel.
       * This is a very slow process, there is no need not to try
       */ 
      SP_RENDER_BANK(TES_AMC_APPEND, TBUF[z], AMC_INSERT);
    
      /*
       * ALPHA && AMC_APPEND:
       */  
      SP_RENDER_BANK(TES_ALPHA | TES_AMC_APPEND, RGB_concoct_mix(*DTB2, TBUF[z], 
            0xFF ^ blend, blend), AMC_INSERT); 
            
      /*
       * noaffect:
       */        
      SP_RENDER_BANK(0, TBUF[z], AMC_NODONE);   
#undef SP_RENDER_BANK

      }
      
  __final:
	  P = &P[-1];
      
  } while (--i != -1);
}  
/* ============================================================= */  
struct core_s *init_ppu (void) {
  /* try malloc */
  int i, m;
  struct core_s *CE = malloc (sizeof(struct core_s));
  if (CE) {
    memset (CE, 0x00, sizeof(struct core_s));
  //memset (&CE->spramc[0], 0x00, sizeof(CE->spramc));

	for (i = 0; i != 256; i++) {
		 for (m = 0; m != 8; m++)
		      CE->oam[i].y_coord[m] = 0xFF;
		 CE->oam[i].y_coord_common = 0xFF;
	}
    CE->bg_trans = 0;

    memset(&CE->sub_slot[0], 0x01, sizeof(CE->sub_slot));
    memset(&CE->lft_slot[0], 0x01, sizeof(CE->lft_slot));
  }
  return CE;
}
/* ============================================================= */
void uninit_ppu (struct core_s *CE) {
  /* try malloc */
        _amc_destroy (CE);
        free (CE);
}
#define GETFTTYPEBUF(i) (&common_letter0[0])
static int64_t common_letter0[128] = {
/* mapper D7-D0<->Right-Left */
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
0x0000000000000000, 0x0018001818181818, 0x0000000000363636, 0x00367F36367F3600, 
0x00183E603C067C18, 0x0062660C18306646, 0x00DC66D61C386C38, 0x0000000000303030, 
0x0060301818183060, 0x00060C1818180C06, 0x0000663CFF3C6600, 0x000018187E181800, 
0x060C0C0000000000, 0x000000007E000000, 0x0006060000000000, 0x0002060C18306040, 
0x001C26676373321C, 0x007E181818181C18, 0x007F071E3C70633E, 0x003E63603C18307E, 
0x0030307F33363C38, 0x003E6360603F033F, 0x003E63633F03063C, 0x000C0C0C1830637F, 
0x003E61611E27231E, 0x001E30607E63633E, 0x0018180000181800, 0x0618180000181800, 
0x0000180C060C1800, 0x00007E00007E0000, 0x0000183060301800, 0x000C000C3860633E, 
0x007C06765676663C, 0x0063637F6363361C, 0x003F63633F63633F, 0x003C66030303663C, 
0x001F33636363331F, 0x007F03033F03037F, 0x000303033F03037F, 0x007C66637303067C, 
0x006363637F636363, 0x003C18181818183C, 0x003E636360606078, 0x0063331B0F1B3363, 
0x007E060606060606, 0x0063636B7F7F7763, 0x0063737B7F6F6763, 0x003E63636363633E, 
0x000303033F63633F, 0x006E335B6363633E, 0x0063331B3F63633F, 0x003E63603E03633E, 
0x000C0C0C0C0C0C3F, 0x003E636363636363, 0x00081C3E77636363, 0x0063777F7F6B6363, 
0x0063773E1C3E7763, 0x001818183C666666, 0x007F070E1C38707F, 0x0078181818181878, 
0x00406030180C0602, 0x003C30303030303C, 0x0000000063361C08, 0x007F000000000000, 
0x00000000000C0603, 0x006E333E301E0000, 0x001F3333331F0303, 0x001E3303331E0000, 
0x003E3333333E3030, 0x001E033F331E0000, 0x000C0C0C1E0C0C38, 0x1E303E33333E0000, 
0x00333333331F0303, 0x000C0C0C0C000C00, 0x0E18181818001800, 0x00331B0F1B330303, 
0x000C0C0C0C0C0C0C, 0x006B6B6B7F370000, 0x00333333371B0000, 0x003C6666663C0000, 
0x03031F33331F0000, 0x30303E33333E0000, 0x00030303371B0000, 0x001F301E031E0000, 
0x00380C0C0C3E0C00, 0x00363B3333330000, 0x000C1E3333330000, 0x00367F6B6B6B0000, 
0x00331E0C1E330000, 0x1E303E3333330000, 0x003F060C183F0000, 0x007018180C181870, 
0x0018181818181818, 0x000E18183018180E, 0x0000000030794F06, 0x0000000000000000
};
/* ============================================================= */
void ppu_render (struct core_s *CE) {
    
  if (CE->mask & PPU_BG_VISABLE) {     
      bgticks (CE);     
      if (CE->mask & PPU_BG_ALPHA)
          _alpha (&CE->sub_data[2184], CE->bg_trans, &CE->sub_slot[2184], CE->bg_blend);
  } else {
      memset  (&CE->sub_slot[0], 0x01,                    sizeof(CE->sub_slot));
      memsetd (&CE->sub_data[0], CE->bg_trans & 0xFFFFFF, sizeof(CE->sub_slot));
  }
  if (CE->mask & PPU_SP_VISABLE) {
     //_amc_destroy (CE);
           spticks (CE); 
  }  
  if (CE->mask & PPU_FT_VISABLE) {  
      _memcpy (&CE->sub_data[2184], &CE->lft_data[2184], &CE->lft_slot[2184]);
       memset (&CE->lft_slot[0],     0x01,         sizeof(CE->lft_slot));
  }
  if (CE->mask & PPU_UN_ALPHA)
      _alpha2 (&CE->sub_data[2184], CE->union_trans, CE->union_blend);      
}
/* ============================================================= */
COMISLGC 
void mpadding (struct core_s *CE, 
    uint32_t *VMR_base,
    uint32_t STP_base, uint32_t MR_sec)
{
  uint32_t *l_VMR;
  uint32_t  l_STP = STP_base >> 2;

  struct tile_s *S = &CE->R_mesh[MR_sec << 8];
  struct tile_s *P;

  int32_t x;
  int32_t y;
  int32_t z;
  int32_t g;

  int32_t p;
  int32_t l;
  int32_t r; 
  int32_t top;
  int32_t stack[64];

  int32_t T = CE->bg_trans & 0x00FFFFFF;  

  for (y = 0; y != 16; y++) {
      
    for (x = 0; x != 16; x++) { 
     
       /* Set init-coord buffer */
       l_VMR = &VMR_base[l_STP * y * 8 + x * 8];
       
       /* Set init-coord tile */
       P = &S[x + y * 16];
       
       /*
        * Clear tebl's infos, reset all status 
        */
       for (z = 0; z != 64; z++) {
           
          P->dattable_org[z] = l_VMR[z / 8 * l_STP + z % 8] & 0x00FFFFFF;
          P->dattable_sel[z] = T;
          P->dattable_count[z] = 0;
          P->maptable_sel[z] = -1;
          P->dattable_nat[z] = 1;
       }       

       P->isvailed_tebl = 1; /* Set vaild flag */
       P->datcount_type = 0; /* Init Count-type */
       P->datcount_numb = 0; /* Init Count-numb */
       
       /* Collect infos */
       for (z = 0; z != 64; z++) {
           
          if (P->dattable_org[z] != T) {
                
              /* Atom pixel */
              P->datcount_numb++;      

              /* Set notrans */
              P->dattable_nat[z] = 0;

              /* Test whether to repeat the color selection list */
              for (g = 0; P->dattable_sel[g] != T; g++)

                  if (P->dattable_sel[g] == P->dattable_org[z]) {
                      
                      /* Atom cur pixel select table 's count */
                      P->dattable_count[g]++;
                      
                      /* Ignore pixel select table */
                      goto repeat_;
                  }
                  
              /* No repeat:add new pixel in pixel select table .
               * Set init pixel count, Atom type count, and mapper table
               */
              P->dattable_sel[P->datcount_type] = P->dattable_org[z];
              P->dattable_count[P->datcount_type++] = 1;
              
      repeat_:P->maptable_sel[z] = g;
      
          }
       }  
      /*
       * fully transparent
       */
       if (P->datcount_type == 0)
           continue;
      /*
       * Inline tile iterative-quicksort
       */
       top = 1;
       stack[0] = 0;
       stack[1] = P->datcount_type - 1;

       while (top >= 0) {
           
         r = stack[top--];
         l = stack[top--];
         
         p = partition (P, l, r);
         
        /* 
         * Left side of pivot
         */          
         if (p - 1 > l) {
             stack[++top] = l;
             stack[++top] = p - 1;
         }
        /* 
         * Right side of pivot
         */
         if (p + 1 < r) {
             stack[++top] = p + 1;
             stack[++top] = r;
         }
       }
    }
  }
}
/* ============================================================= */
COMISLGC void
#ifndef __GNUC__
__cdecl
#else 
__attribute__((__cdecl__))
#endif    
_textout (struct core_s *CE, uint8_t t, 
          uint8_t screen_x, 
          uint8_t screen_y, 
          int32_t data, const char *fmt, ...)
{     
  int screen_x2, screen_y2, screen_x3, screen_y3;
  va_list args; 
  char buf[1024];
  int i = 0, x, y;

  uint64_t *lft_buf;
  int8_t *clft_buf, *adt_buf = &CE->lft_slot[2184];
  int32_t *bdt_buf = &CE->lft_data[2184];

  /* Test enable */
  if (!(CE->mask & PPU_FT_VISABLE))
      return;
  
  screen_x2 = screen_x;
  screen_y2 = screen_y;

  if (screen_y2 > 239)
      screen_y2 -= 240;
  
  screen_x3 = screen_x2;
  screen_y3 = screen_y2;
  
  va_start(args, fmt);
  (void)vsprintf(&buf[0], fmt, args);
  va_end(args);

  /* get font type */
  lft_buf = GETFTTYPEBUF(t);

  for 
  (; buf[i]; i++) {
    
     /* limit standard ascii *.*/
     buf[i] &= 0x7F;
      
     /* we only deal '\n' escape character */ 
     if 
     (buf[i] == '\n') {
          
        screen_y3 += 8;
      
        if 
        (screen_y3 > 239) screen_y3 -= 240;
      
        screen_x2 = screen_x3; // FIXME:move BUG
        screen_y2 = screen_y3;
          
     } else {
        int screen_x4 = screen_x2;
        int screen_y4 = screen_y2;
          
        /* Get token<ascii> buffer */
        clft_buf = (uint8_t *)decode_font (&lft_buf[buf[i]]);

        for /* draw font martix(8*8 pixel) */
        (y = 0; y != 8; y++) {
              
            for /* draw one line per */
            (x = 0; x != 8; x++) {
                  
                if 
                (clft_buf[y * 8 + x]) {    

                    bdt_buf[_CSV(screen_y2) + screen_x2] = data;
                    adt_buf[_CSV(screen_y2) + screen_x2] = 0;
                }
                  
                /* Tst, deal x overflow 
                 * if hit, x reset. Tst, deal y overflow                
                 */
                if 
                (++screen_x2 == 256) {
                      
                   screen_x2  = 0;  
                   screen_y2 += 8;
                      
                   if 
                   (screen_y2 > 239)
                    screen_y2 -= 240;
                } 
            }
            /* do step-y. 
             * Tst, deal y overflow. and reset 
             */
            if (++screen_y4 >= 240)
                  screen_y4 -= 240; 
               
            screen_x2 = screen_x4;
            screen_y2 = screen_y4;                
        }
        /* Tst, deal x overflow 
         * if hit, x reset. Tst, deal y overflow again... 
         * an font scan complete..
         */ 
        screen_x4 += 8;
        screen_y2 = screen_y4 - 8;  
          
        if 
        (screen_x4 > 255) {
              
          screen_x4 -= 256;  
          screen_y2 += 8;
        }             

        screen_x2 = screen_x4;
    }
  }
} 
/* ============================================================= */
COMISLGC       
struct vrmscr_s *vsread (struct core_s *CE) {
    
  static 
  struct vrmscr_s T;   
  
  T.nametable_quad = CE->msc.nametable_quad;
  T.x_map_scroll = CE->msc.x_map_scroll;  
  T.y_map_scroll = CE->msc.y_map_scroll;
  T.vram_quad = CE->msc.vram_quad;
  T.x_ram_access = CE->msc.x_ram_access;
  T.y_ram_access = CE->msc.y_ram_access;  
  
  return &T;
}
/* ============================================================= */
COMISLGC   
void vswrite (struct core_s *CE, const struct vrmscr_s *R) {
                                
  CE->msc.nametable_quad = R->nametable_quad;
  CE->msc.x_map_scroll = R->x_map_scroll;  
  CE->msc.y_map_scroll = R->y_map_scroll;
  CE->msc.vram_quad = R->vram_quad;
  CE->msc.x_ram_access = R->x_ram_access;
  CE->msc.y_ram_access = R->y_ram_access;  
}
/* ============================================================= */
COMISLGC       
struct tnslen_s *tlread (struct core_s *CE) {
    
  static 
  struct tnslen_s T;   
  
  T.bg_trans = CE->bg_trans;
  T.union_trans = CE->union_trans;  
  T.bg_blend = CE->bg_blend;
  T.union_blend = CE->union_blend;
  
  return &T;
}
/* ============================================================= */
COMISLGC   
void tlwrite (struct core_s *CE, const struct tnslen_s *R) {
                                
  CE->bg_trans = R->bg_trans;
  CE->union_trans = R->union_trans;  
  CE->bg_blend = R->bg_blend;
  CE->union_blend = R->union_blend;
}
/* =========================================================================================== */
COMISLGC uint32_t fmskread (struct core_s *CE) { return CE->mask; } 
COMISLGC void fmskwrite (struct core_s *CE, uint32_t mask) { CE->mask = mask; } 
COMISLGC void fmskxor (struct core_s *CE, uint32_t mask) { CE->mask ^= mask; } 
COMISLGC void fmskor (struct core_s *CE, uint32_t mask) { CE->mask |= mask; } 
COMISLGC void fmskand (struct core_s *CE, uint32_t mask) { CE->mask &= mask; } 
/* ============================================================= */
COMISLGC 
struct back_s *ksmread (struct core_s *CE)
{
  static 
  struct bg_chunk_s T;
  
  return MEMCPY_BGCK_s (&T, bg_chunk_domain(CE));
} 
/* ============================================================= */
COMISLGC 
void ksmwrite (struct core_s *CE, const struct bg_chunk_s *R)
{
  MEMCPY_BGCK_s (bg_chunk_domain(CE), R);
}
/* ============================================================= */
COMISLGC 
void vestomas (struct core_s *CE, uint8_t d_chunk,  uint8_t d_callon,
               uint8_t s_chunk,  
               uint8_t s_callon)
{
  MEMCPY_TILE_s 
  (tile_domain(CE, TEB_CACHE, d_chunk, d_callon),
   tile_domain(CE, 0,         s_chunk, s_callon));
}
/* ============================================================= */
COMISLGC 
void mastomas (struct core_s *CE, uint8_t d_chunk, uint8_t d_callon,
               uint8_t s_chunk, 
               uint8_t s_callon)
{
  MEMCPY_TILE_s 
  (tile_domain(CE, TEB_CACHE, d_chunk, d_callon),
   tile_domain(CE, TEB_CACHE, s_chunk, s_callon));
}
/* ========================================================================== */
COMISLGC 
struct tile_s *vesread (struct core_s *CE, uint8_t section, uint8_t impact)
{
  static 
  struct tile_s T;
  
  return 
  MEMCPY_TILE_s ( &T, tile_domain(CE, 0, section, impact) );
}
/* ========================================================================= */
COMISLGC 
struct tile_s *masread (struct core_s *CE, uint8_t section, uint8_t impact)
{
  static 
  struct tile_s T;
  
  return 
  MEMCPY_TILE_s ( &T, tile_domain(CE, TEB_CACHE, section, impact) );
}
/* ================================================================================ */
COMISLGC 
struct sp_amc_s *amcread (struct core_s *CE, uint8_t x, uint8_t y)
{
  static 
  struct sp_amc_s T;
  
  return 
  MEMCPY_AMCK_s ( &T, &CE->amc_pool[2184 + _CSV(y) + x] );
}
/* ====================================================================================== */
COMISLGC 
void maswrite (struct core_s *CE, struct tile_s *R, uint8_t section, uint8_t impact)
{
  MEMCPY_TILE_s 
  ( tile_domain(CE, TEB_CACHE, section, impact), R);   
}
/* ============================================================= */
COMISLGC void oamwrite (struct core_s *CE, uint8_t slot, int chan, 
          int source, int section, int impact) 
{ 
  MEMCPY_TILE_s 
  (&CE->oam[slot].cache[chan & 7], tile_domain(CE, source ? 0 : TEB_CACHE, section, impact));   
  (&CE->oam[slot])->section[chan] = section;
  (&CE->oam[slot])->impact[chan] = impact; 
}
/* =================================================================== */
COMISLGC void rebedye0b (struct core_s *CE, int section, int impact) {
    struct tile_s *P =     tile_domain(CE, TEB_CACHE, section, impact);
    rebedye_Palette_NOwarp(CE, P);
}
/* =================================================================== */
COMISLGC void rebedye2b (struct core_s *CE, int section, int impact) {
    struct tile_s *P =     tile_domain(CE, TEB_CACHE, section, impact);
    rebedye_Primitive_NOwarp(CE, P);
}
/* =================================================================== */
COMISLGC void rebedye0s (struct core_s *CE, uint8_t slot, int chan) {
    rebedye_Palette_NOwarp(CE, &CE->oam[slot].cache[chan]);
}
/* =================================================================== */
COMISLGC void rebedye2s (struct core_s *CE, uint8_t slot, int chan) {
    rebedye_Primitive_NOwarp(CE, &CE->oam[slot].cache[chan]);    
}
