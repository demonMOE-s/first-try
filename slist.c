#define _HEAP_ALLOC_ROUNTINE_ malloc 
#define _HEAP_FREE_ROUNTINE_ free 
#define __ALLOC_ _HEAP_ALLOC_ROUNTINE_
#define __FREE_ _HEAP_FREE_ROUNTINE_
#define _SIZE1_  (sizeof(int *)*1)
#define _SIZE2_ (sizeof(int *)*2)
#define _BYTE_(x) ((unsigned char)(x))
#define _BYTEP_(x) ((unsigned char *)(x))
#define _BYTEPP_(x) ((unsigned char **)(x))
#define _SIZE_(x) ((unsigned int)(x))
#define _SIZEP_(x) ((unsigned int *)(x))
#define _SIZEPP_(x) ((unsigned int **)(x))
#define _VOIDP_(x) ((void *)(x))
#define _VOIDPP_(x) ((void **)(x))
#define _uint_t unsigned int 
#define _void_t void 
#define _voidp_t void *
#define _voidpp_t void **
#define _bool_t int 
#define true 1 
#define false 0 
#define NULL ((void *)0)
#define __SOME_THING__(x)               \
_voidpp_t boak[x];                      \
if (ref)                                \
  boak[0] = &boak[3];                   \
else                                    \
{                                       \
  boak[0] = &obrp;                      \
  size = 0;                             \
}                                       \
  boak[2] = __ALLOC_ (_SIZE2_ + size);  \
if (                                    \
 !boak[2]                               \
)                                       \
return                                  \
false;                                  \
boak[3] = &_BYTEP_(boak[2])[_SIZE2_]

extern void *malloc (unsigned int size);
extern void free (void *ptr);

// ======================================================
// n3_slist_get_nogc --- xxx
// ======================================================
_void_t 
n3_slist_get_nogc (_voidpp_t __pp_) 
{
    __pp_[0] = __ALLOC_ (_SIZE2_); 
if (__pp_[0]) 
{
    _VOIDPP_(__pp_[0])[0] = NULL; 
    _VOIDPP_(__pp_[0])[1] = NULL; 
}
}
// ======================================================
// n3_slist_insert_head --- xxx
// ======================================================
_bool_t 
n3_slist_insert_head (_voidp_t root, 
                      _voidp_t obrp, 
                      _bool_t ref,
                      _uint_t size) 
{
__SOME_THING__(4);

  _VOIDPP_(boak[2])[0] = _VOIDPP_(boak[0])[0]; // ob into block  
  _VOIDPP_(boak[2])[1] = _VOIDPP_(root)[1]; // link first
  _VOIDPP_(root)[1] = _VOIDP_(boak[2]); // link root
   
  while (size--) {
   _BYTEP_(boak[3])[0] = _BYTEP_(obrp)[0];
    boak[3] = (_BYTEP_(boak[3]) + 1);
    obrp = (_BYTEP_(obrp) + 1);
  }

return 
true; 
}
// ======================================================
// n3_slist_insert_tail --- xxx
// ======================================================
_bool_t  
n3_slist_insert_tail (_voidp_t root, 
                      _voidp_t obrp, 
                      _bool_t ref,
                      _uint_t size)
{
__SOME_THING__(8);

boak[5] = root;
boak[6] = _VOIDPP_(root)[1];

  _VOIDPP_(boak[2])[0] = _VOIDPP_(boak[0])[0]; // ob into block  
  _VOIDPP_(boak[2])[1] = NULL; // link first
  
  while (size--) {
   _BYTEP_(boak[3])[0] = _BYTEP_(obrp)[0];
    boak[3] = (_BYTEP_(boak[3]) + 1);
    obrp = (_BYTEP_(obrp) + 1);
  }

while (boak[6]) 
  boak[4] = boak[5],
  boak[5] = boak[6],
  boak[6] = _VOIDPP_(boak[6])[1]; 
_VOIDPP_(boak[5])[1] = boak[2];
return 
true;
}
// ======================================================
// n3_slist_insert_node:
// ======================================================
_bool_t  
n3_slist_insert_node (_voidp_t root, 
                      _voidp_t obrp, 
                      _uint_t size,
                      _bool_t ref,
                      _uint_t pos)
{
__SOME_THING__(8);

boak[5] = root;
boak[6] = _VOIDPP_(root)[1];

  _VOIDPP_(boak[2])[0] = _VOIDPP_(boak[0])[0]; // ob into block  
  _VOIDPP_(boak[2])[1] = NULL; // link first
 
  while (size--) {
   _BYTEP_(boak[3])[0] = _BYTEP_(obrp)[0];
    boak[3] = (_BYTEP_(boak[3]) + 1);
    obrp = (_BYTEP_(obrp) + 1);
  }

while (pos && boak[6]) 
  boak[4] = boak[5],
  boak[5] = boak[6],
  boak[6] = _VOIDPP_(boak[6])[1],
  pos -= 1;
if (!pos && boak[5]) // enable?
{
boak[6] = 
_VOIDPP_(boak[5])[1];
_VOIDPP_(boak[5])[1] = boak[2];
_VOIDPP_(boak[2])[1] = boak[6];
return 
true;
}
return 
false;
}
// ======================================================
// n3_slist_remove_head:
// ======================================================
_bool_t 
n3_slist_remove_head (_voidp_t root) 
{
_voidp_t x0 = _VOIDPP_(root)[1]; // first 
    
   if (!x0) // empty list ?
    return false;
    
   _VOIDPP_(root)[1] = _VOIDPP_(x0)[1]; // second 

   __FREE_ (x0); // free object, block 
return 
   true;
}
// ======================================================
// n3_slist_remove_tail:
// ======================================================
_bool_t 
n3_slist_remove_tail (_voidp_t root)
{
    _voidp_t m0 = root; // base 
    _voidp_t m1 = _VOIDPP_(m0)[1]; // middle 
    _voidp_t m2 = NULL; // fastest 
    
    if (!m1) // empty list ? 
        return false;
    
    // loop-entry 
    for ( m2 = _VOIDPP_(m1)[1]; 
          m2!= NULL; 
          m0 = m1, 
          m1 = m2,
          m2 = _VOIDPP_(m2)[1] ) {;}
          
   __FREE_ (m1); // free object and block 
   _VOIDPP_(m0)[1] = NULL;
return 
    true;
}
// ======================================================
// n3_slist_remove_node
// ======================================================
_bool_t 
n3_slist_remove_node (_voidp_t root, 
                      _uint_t pos)
{
_uint_t n = 0;
  for ( pos += 1; 
       (pos && _VOIDPP_(root)[1] != NULL); 
        n+= 1,
        pos -= 1,
    root  =    _VOIDPP_(root)[1]
  ) {;}
 if (!(!pos && root))
   return false;
 __FREE_(_VOIDPP_(root)[0]);
return true;
}
// ======================================================
// n3_slist_get_count
// ======================================================
_uint_t 
n3_slist_get_count (_voidp_t root) 
{
_uint_t n;
  for ( n = 0; _VOIDPP_(root)[1] != NULL; 
        n+= 1,           
    root  =    _VOIDPP_(root)[1]
  ) {;}
 return n;
}
// ======================================================
// n3_slist_get_node
// ======================================================
_voidp_t 
n3_slist_get_node (_voidp_t root, _uint_t pos) 
{
_uint_t n = 0;
  for ( pos += 1; 
       (pos && _VOIDPP_(root)[1] != NULL); 
        n+= 1,
        pos -= 1,
    root  =    _VOIDPP_(root)[1]
  ) {;}
 if (!pos && root)
   return _VOIDPP_(root)[0];
return NULL;
}
// ======================================================
// n3_slist_get_head
// ======================================================
_voidp_t 
n3_slist_get_head (_voidp_t root) 
{
return 
   _VOIDPP_(root)[1];
}
// ======================================================
// n3_slist_get_tail
// ======================================================
_voidp_t 
n3_slist_get_tail (_voidp_t root)
{
    _voidp_t m0 = root; // base 
    _voidp_t m1 = _VOIDPP_(m0)[1]; // middle 
    _voidp_t m2 = NULL; // fastest 
    
    if (!m1) // empty list ? 
        return NULL;
    
    // loop-entry 
    for ( m2 = _VOIDPP_(m1)[1]; 
          m2!= NULL; 
          m0 = m1, 
          m1 = m2,
          m2 = _VOIDPP_(m2)[1] ) {;}

   return m1;
}
// ======================================================
// n3_slist_destroy_nogc
// ======================================================
_void_t 
n3_slist_destroy_nogc (_voidp_t root) 
{
    _voidp_t prev = _VOIDP_(root);
    _voidp_t next = _VOIDPP_(root)[1];
    // first 
    __FREE_ (root);

while (1)
    if (!next) return;
else {
    prev = _VOIDPP_(next)[1];
           __FREE_ (next); // release block, object ptr
                    next = prev; // thaw node
}
}
// ======================================================
// n3_slist_is_empty
// ======================================================
_bool_t 
n3_slist_is_empty (_voidp_t root) 
{
return 
_VOIDPP_(root)[1] 
? false
: true;
}

#undef _HEAP_ALLOC_ROUNTINE_ 
#undef _HEAP_FREE_ROUNTINE_  
#undef __ALLOC_ 
#undef __FREE_ 
#undef _SIZE1_ 
#undef _SIZE2_ 
#undef _BYTE_
#undef _BYTEP_
#undef _BYTEPP_
#undef _SIZE_
#undef _SIZEP_
#undef _SIZEPP_
#undef _VOIDP_
#undef _VOIDPP_
#undef _uint_t
#undef _void_t 
#undef _voidp_t 
#undef _voidpp_t
#undef _bool_t 
#undef true  
#undef false 
#undef NULL

#if 1

int main (void) 
{
    typedef struct lst {
      int x;
      struct lst *next;
    } xxx;
    typedef struct zgt {
      int x;
      int y;
    } yyy;
    typedef struct yinlst {
      struct zgt *objt;
      struct yinlst *next;
    } zzz;
int n;
    xxx * ppc;
    yyy xxa = {8,7};
    zzz * mmc;
    
    n3_slist_get_nogc(&ppc);

    // __asm int 3
    for (n = 0; n != 2; n++)
        n3_slist_insert_tail (ppc, n, 0, 0);
    // for (n = 0; n != 5; n++)
        // n3_slist_remove_head (ppc);

    n = n3_slist_get_count (ppc); 
    n3_slist_destroy_nogc(ppc);
    
    
    n3_slist_get_nogc(&mmc);

    for (n = 0; n != 5; n++)
        n3_slist_insert_tail (mmc, &xxa, 1, sizeof(yyy));
    for (n = 0; n != 5; n++)
        n3_slist_remove_head (mmc);

    n = n3_slist_get_count (mmc); 
    n3_slist_destroy_nogc(mmc);


}

#endif
