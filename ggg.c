#define ROAD_TOP_LEFT  141
#define ROAD_TOP_RIGHT 142
#define ROAD_BOT_LEFT  205
#define ROAD_BOT_RIGHT 206 
	
#define COIN_TOP_LEFT  207 
#define COIN_TOP_RIGHT 208 
#define COIN_BOT_LEFT  271 
#define COIN_BOT_RIGHT 272  

#define ROCK_TOP_LEFT  337
#define ROCK_TOP_RIGHT 338
#define ROCK_BOT_LEFT  401
#define ROCK_BOT_RIGHT 402
	
#define LAWN_LEFT  384 
#define LAWN_RIGHT 387
#define LAWN_MIDDLE 385
#define LAWN_TOPL  (385-64)
#define LAWN_TOPR  (385-63)

#define BRICK_L0 335
#define BRICK_L1 399 

#define CLOUD_L0_1 130
#define CLOUD_L0_2 131 
#define CLOUD_L1_0 193
#define CLOUD_L1_3 196
#define CLOUD_L2_0 (193+64)
#define CLOUD_L2_1 (193+65)
#define CLOUD_L2_2 (193+66)
#define CLOUD_L2_3 (193+67)
#define CLOUD_MIDD 194

#define PIPE_L0_0 213
#define PIPE_L0_1 214
#define PIPE_L0_2 215
#define PIPE_L0_3 216
#define PIPE_L0_4 217
#define PIPE_L1_0 277
#define PIPE_L1_1 278
#define PIPE_L1_2 279
#define PIPE_L1_3 280
#define PIPE_L1_4 281
#define PIPE_L2_0 341
#define PIPE_L2_1 342
#define PIPE_L2_2 343
#define PIPE_L2_3 344
#define PIPE_L2_4 345

#define MOUTIN_L0_2 263 
#define MOUTIN_L0_3 264 
#define MOUTIN_L1_1 326
#define MOUTIN_L1_2 327 
#define MOUTIN_L1_3 328
#define MOUTIN_L1_4 329 
#define MOUTIN_L2_0 389
#define MOUTIN_L2_M 390
#define MOUTIN_L2_5 394

//=========================================================
// draw_road_oak - base collide unit 
//=========================================================
static 
void draw_road_oak(u32 page, u32 pos_x, u32 pos_y, u32 xnums, BOOL bbottom) {

	u32 index;
	u32 ipwho = 
			bbottom == TRUE 
			? ROAD_BOT_LEFT
			: ROAD_TOP_LEFT;
			
	for (index = 0; index != xnums; index ++) 	
	/* draw road mesh */ {	
		NtaSetWriteTileIdEx(page, pos_x + index, pos_y, ipwho + (index & 1));
	}
}
//=========================================================
// draw_coin_bbp - draw base one
//=========================================================
static 
void draw_coin_bbp(u32 page, u32 pos_x, u32 pos_y) {

	NtaSetWriteTileIdEx(page, pos_x + 0, pos_y + 0, COIN_TOP_LEFT);
	NtaSetWriteTileIdEx(page, pos_x + 1, pos_y + 0, COIN_TOP_RIGHT);
	NtaSetWriteTileIdEx(page, pos_x + 0, pos_y + 1, COIN_BOT_LEFT);
	NtaSetWriteTileIdEx(page, pos_x + 1, pos_y + 1, COIN_BOT_RIGHT);	
}
//=========================================================
// draw_rock_bbp - draw base one
//=========================================================
static 
void draw_rock_bbp(u32 page, u32 pos_x, u32 pos_y) {

	NtaSetWriteTileIdEx(page, pos_x + 0, pos_y + 0, ROCK_TOP_LEFT);
	NtaSetWriteTileIdEx(page, pos_x + 1, pos_y + 0, ROCK_TOP_RIGHT);
	NtaSetWriteTileIdEx(page, pos_x + 0, pos_y + 1, ROCK_BOT_LEFT);
	NtaSetWriteTileIdEx(page, pos_x + 1, pos_y + 1, ROCK_BOT_RIGHT);	
}
//=========================================================
// draw_rock_oak - base collide unit 
//=========================================================
static 
void draw_rock_oak(u32 page, u32 pos_x, u32 pos_y, u32 xnums, BOOL bbottom) {

	u32 index;
	u32 ipwho = 
			bbottom == TRUE 
			? ROCK_BOT_LEFT
			: ROCK_TOP_LEFT;
			
	for (index = 0; index != xnums; index ++) 	
	/* draw rock mesh */ {	
		NtaSetWriteTileIdEx(page, pos_x + index, pos_y, ipwho + (index & 1));
	}
}
//=========================================================
// draw_rock_tri - tri draw
//=========================================================
static 
void draw_rock_tri(u32 page, u32 pos_x, u32 pos_y, u32 levels, BOOL reverseH, BOOL reverseV) {
	
	u32 itoeV = 1;
	u32 itoeH = 1;
	u32 itoeIX = 0;
	u32 itoeIY = 1;
	u32 itoeRX = levels;
	u32 itoeRY = levels + 1;	
	u32 itoeTemp0;
	u32 itoeTemp1;
	u32 itoeTemp2 = 0;
	
	if (reverseH == TRUE) {	
		itoeH = -1;
		itoeIX = levels - 1;
		itoeRX = -1;
	}
	if (reverseV == TRUE) {	
		itoeV = -1;
		itoeIY = levels;
		itoeRY = 0;
	}
	for (itoeIY = itoeIY; itoeIY != itoeRY; itoeIY += itoeV)
	{	
		itoeTemp0 = itoeIY;
		itoeTemp1 = reverseH == TRUE ? levels - 1 : 0;
		
		while (itoeTemp0 --) {
			
			draw_rock_bbp(page, pos_x + itoeTemp1 * 2, pos_y + itoeTemp2 * 2);
			itoeTemp1 += itoeH;
		}
		++ itoeTemp2;
	}
}
//=========================================================
// draw_rock_rect - rect draw
//=========================================================
static 
void draw_rock_rect(u32 page, u32 pos_x, u32 pos_y, u32 xn, u32 yn) {
	
	u32 xi;
	u32 yi;
	
	for (yi = 0; yi != yn; yi ++) 
	{	
		for (xi = 0; xi != xn; xi ++) 
		{
			draw_rock_bbp(page, pos_x + xi * 2, pos_y + yi * 2);
		}
	}
}
//=========================================================
// draw_brick_oak - base collide unit [can break]
//=========================================================
static 
void draw_brick_oak(u32 page, u32 pos_x, u32 pos_y, u32 xnums, BOOL bbottom) {

	u32 index;
	u32 ipwho = 
			bbottom == TRUE 
			? BRICK_L1
			: BRICK_L0;
			
	for (index = 0; index != xnums; index ++) 	
	/* draw brick_oak mesh */ {	
		NtaSetWriteTileIdEx(page, pos_x + index, pos_y, ipwho);
	}
}
//=========================================================
// draw_lawn - easy background unit --- no effect 
//=========================================================
static 
void draw_lawn(u32 page, u32 pos_x, u32 pos_y, u32 xnums) {

	u32 index;
	
	NtaSetWriteTileIdEx(page, pos_x + xnums * 0 + 0, pos_y + 1, LAWN_LEFT); // head 
	NtaSetWriteTileIdEx(page, pos_x + xnums * 2 + 1, pos_y + 1, LAWN_RIGHT); // tail
	
	for (index = 0; index != xnums; index ++) {
		
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 1, pos_y + 0, LAWN_TOPL); 
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 2, pos_y + 0, LAWN_TOPR); 
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 1, pos_y + 1, LAWN_MIDDLE);
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 2, pos_y + 1, LAWN_MIDDLE); 
	}
}
//=========================================================
// draw_cloud - easy background unit --- no effect 
//=========================================================
static 
void draw_cloud(u32 page, u32 pos_x, u32 pos_y, u32 xnums) {

	u32 index;
	
	NtaSetWriteTileIdEx(page, pos_x + xnums * 0 + 0, pos_y + 1, CLOUD_L1_0); // head 
	NtaSetWriteTileIdEx(page, pos_x + xnums * 2 + 1, pos_y + 1, CLOUD_L1_3); // tail
	NtaSetWriteTileIdEx(page, pos_x + xnums * 0 + 0, pos_y + 2, CLOUD_L2_0); // head 
	NtaSetWriteTileIdEx(page, pos_x + xnums * 2 + 1, pos_y + 2, CLOUD_L2_3); // tail

	for (index = 0; index != xnums; index ++) {
		
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 1, pos_y + 0, CLOUD_L0_1); 
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 2, pos_y + 0, CLOUD_L0_2); 
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 1, pos_y + 1, CLOUD_MIDD);
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 2, pos_y + 1, CLOUD_MIDD); 
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 1, pos_y + 2, CLOUD_L2_1);
		NtaSetWriteTileIdEx(page, pos_x + 2 * index + 2, pos_y + 2, CLOUD_L2_2); 
	}
}
//=========================================================
// draw_montin_base_l - easy base one 
//=========================================================
static 
void draw_montin_base_l(u32 page, u32 pos_x, u32 pos_y) {
	
	NtaSetWriteTileIdEx(page, pos_x + 0, pos_y + 0, MOUTIN_L2_0); 
	NtaSetWriteTileIdEx(page, pos_x + 1, pos_y + 0, MOUTIN_L2_M); 
	NtaSetWriteTileIdEx(page, pos_x + 2, pos_y + 0, MOUTIN_L2_M); 
	NtaSetWriteTileIdEx(page, pos_x + 3, pos_y + 0, MOUTIN_L2_M); 
	NtaSetWriteTileIdEx(page, pos_x + 4, pos_y + 0, MOUTIN_L2_M); 	
	NtaSetWriteTileIdEx(page, pos_x + 5, pos_y + 0, MOUTIN_L2_5); 
	NtaSetWriteTileIdEx(page, pos_x + 1, pos_y - 1, MOUTIN_L1_1); 
	NtaSetWriteTileIdEx(page, pos_x + 2, pos_y - 1, MOUTIN_L1_2); 
	NtaSetWriteTileIdEx(page, pos_x + 3, pos_y - 1, MOUTIN_L1_3); 
	NtaSetWriteTileIdEx(page, pos_x + 4, pos_y - 1, MOUTIN_L1_4); 
	NtaSetWriteTileIdEx(page, pos_x + 2, pos_y - 2, MOUTIN_L0_2); 	
	NtaSetWriteTileIdEx(page, pos_x + 3, pos_y - 2, MOUTIN_L0_3); 
	
}
//=========================================================
// draw_montin_l - easy unit 
//=========================================================
static 
void draw_montin_l(u32 page, u32 pos_x, u32 pos_y, u32 levels) {
	
	if (!levels) {
		
		draw_montin_base_l(page, pos_x, pos_y - 1);
		return;
	}
	/* --- draw top -> bottom --- */ {
		
		u32 index;
		u32 tempu0 = 8;
		u32 emsp0;
		u32 xmecs;
		
		draw_montin_base_l(page, pos_x + levels, pos_y - levels - 1);
		
		for (index = 0; index != levels; index ++) {
			
			tempu0 = tempu0 + index * 2;
			NtaSetWriteTileIdEx(page, pos_x + levels - (index + 1)/**/, pos_y - levels + index, MOUTIN_L2_0); 	
			NtaSetWriteTileIdEx(page, pos_x + levels + (index + 6)/**/, pos_y - levels + index, MOUTIN_L2_5); 
			
			for (emsp0 = 0; emsp0 != 6 + index * 2; emsp0 ++) 
			{	
				NtaSetWriteTileIdEx(page, pos_x + levels - index + emsp0/**/, pos_y - levels + index, MOUTIN_L2_M); 	
			}
			if (!(index % 2)) {
				
				for (xmecs = 0; xmecs != (index / 2) + 1; xmecs ++) {
					
					NtaSetWriteTileIdEx(page, pos_x + levels + 1 - xmecs * 2/**/, pos_y - levels + index, MOUTIN_L1_3); 	
					NtaSetWriteTileIdEx(page, pos_x + levels + 4 + xmecs * 2/**/, pos_y - levels + index, MOUTIN_L1_3); 	
					
				}
			}
		}
	}
}
//=========================================================
// draw_pipe - high-level collide unit 
//=========================================================
static 
void draw_pipe(u32 page, u32 pos_x, u32 pos_y, u32 levels) {

	u32 index;
	
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 0, pos_y + 0, PIPE_L0_0);  
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 1, pos_y + 0, PIPE_L0_1); 
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 2, pos_y + 0, PIPE_L0_2); 
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 3, pos_y + 0, PIPE_L0_3); 
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 4, pos_y + 0, PIPE_L0_4); 
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 0, pos_y + 1, PIPE_L1_0);  
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 1, pos_y + 1, PIPE_L1_1); 
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 2, pos_y + 1, PIPE_L1_2); 
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 3, pos_y + 1, PIPE_L1_3); 
	NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 4, pos_y + 1, PIPE_L1_4); 

	for (index = 0; index != levels; index ++) {
		
		NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 1, pos_y + 2 + index, PIPE_L2_1); 
		NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 2, pos_y + 2 + index, PIPE_L2_2); 
		NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 3, pos_y + 2 + index, PIPE_L2_3); 
		NtaSetWriteTileIdEx(page, pos_x + levels * 0 + 4, pos_y + 2 + index, PIPE_L2_4); 
	}
}
