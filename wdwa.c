#define spr ppuGL_LIST.sp
#define spr vd
#define ppu ppuGL_LIST
#define ticks ppuGL_LIST.ticks
#define vc spr.voam_c

void spact_inticks1_64(void) {

/*  ppu ticks 1 ~ 64 
    reset secondary_oam */
    memset( &spr.z[0], -1, sizeof(spr.z) );
}

#define OAMCTOSY(n) {           \
                            \
    spr.z[n].y = spr.cache.y;   \
}

#define OAMCTOS(n) {            \
                                    \
    spr.z[n].x = spr.cache.x;   \
    spr.z[n].y = spr.cache.y;       \
    spr.z[n].id = spr.cache.id; \
    spr.z[n].at = spr.cache.at;     \
}

#define OAMPTOC(n) {                \
                                \
    spr.cache.x = spr.m[n].x;       \
    spr.cache.y = spr.m[n].y;   \
    spr.cache.id = spr.m[n].id;     \
    spr.cache.at = spr.m[n].at; \
}

void spact_inticks65_256(void) {
    
/*  ppu ticks 65 ~ 256
    sprite evaluation */ 
    
    if (ppu.ticks & 1) {        
    /*  odd frame 
    ++      select spr.m into cache */      
        if (FALSE == spr.bcomplete
        &&  spr.voam_c > 7)
        /* over read */ {
            if (!(spr.m[spr.poll_c].y + 1 > ppu.scanline /* oam delayed by one scanline */
            &&    spr.m[spr.poll_c].y + 8 < ppu.scanline))
            /* seek fetch */ {
                goto seeklcache;
            } else {    
            /* set in advance */
                spr.bcomplete = TRUE;           
            }
        }       
        OAMPTOC(spr.poll_c);  /* fetch oam */   
        seeklcache:
        if (0 == ++spr.poll_c & 63)     
        {
        /*      
        ++  spr.m addressing complete wait HBLANK
        ++
        even frame action:
            if oam z buffer remain ...
                fill the rest of the z buffer (from the spr.m's zero index) 
            else if sprite > 8 ... 
                the spr.cache will be discarded. */
                
            spr.bcomplete = TRUE;   
            return;
                    }               
    } else {                
    /*  even frame 
    ++  cache to z buffer */                
        if (spr.bcomplete == TRUE)
        {
        /* loop until HBLANK */
            if (spr.voam_c < 8)
            /* can do */ {
                OAMCTOSY(spr.voam_c);
                spr.voam_c++;
                return;
            }
        }
        
        if (spr.cache.y + 1 > ppu.scanline /* oam delayed by one scanline */
        &&  spr.cache.y + 8 < ppu.scanline)     
        /* in range... */ {
            if (spr.voam_c < 8)             
            /* fetch cache */ {         
                if (spr.voam_c == 7)
                /* bug for Bee 52 */ {
                    ppu.io[2] |= 0x20; 
                        }
                OAMCTOS(spr.voam_c);
                spr.voam_c++;
            }   
        }
    }
}

void spact_inticks257_320(void) {
    
/*  ppu ticks 257 ~ 320
    sprite fetches */ 
    
    INT _ticks,
    INT rvaPhase;
    INT mphase,
    INT xphase;
    rvaPhase = ppu.ticks-257;
    
    xphase = rvaPhase % 8;
    mphase = rvaPhase / 8;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}




