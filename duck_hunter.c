//
// background_demo.c
// Essential tilemap loading: the start of backgroundstar from ducksoid 1
//
// (20060221 - 20070216, cearn)

#include <string.h>

#include "toolbox.h"
#include "background.h"
#include "duck.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

// testing a few sprite things
// D-pad: move 
// SELECT: switch palette
// START: toggle mapping mode
// A: horizontal flip
// B: vertical flip
// L & R shift starting tile
void obj_test()
{
	int i=0, hx=0, hy=160-32-32;
	int dx[4], dy[4], bx[2], by[2];
	u32 tid= 0, pb= 0;		// tile id, pal-bank
	u32 frame = 0;

	for(i=0; i<4; i++) {
		dx[i]=i*50;
		dy[i]=32;
	}
	
	for(i=0; i<2; i++) {
		bx[i]=-10;
		by[i]=-10;
	}

	OBJ_ATTR *ducks= &obj_buffer[0];
	OBJ_ATTR *hunter= &obj_buffer[4];
	OBJ_ATTR *bullets= &obj_buffer[5];
	
	for(i=0; i<4; i++) {
		obj_set_attr(&ducks[i], 
			ATTR0_SQUARE,
			ATTR1_SIZE_32,
			ATTR2_PALBANK(pb) | tid);
	}

	
	obj_set_attr(hunter, 
		ATTR0_SQUARE,
		ATTR1_SIZE_32,
		ATTR2_PALBANK(0) | (16*3));		// palbank 0, tile 0

	for(i=0; i<2; i++) {
		obj_set_attr(&bullets[i], 
			ATTR0_SQUARE,
			ATTR1_SIZE_8,
			ATTR2_PALBANK(0) | (16*4));
	}

	obj_set_pos(hunter, hx, hy);

	while(1)
	{
		vid_vsync();
		frame++;
		key_poll();

		// move left/right
		hx += 2*key_tri_horz();
		if(frame%2) {
			for(i=0; i<4; i++) {
				dx[i]++;
			}
		}
		
		for(i=0; i<2; i++) {
			if(bx[i]>0) {
				bx[i]++;
				by[i]--;
			}
			if(bx[i]>240 || by[i]<0) {
				bx[i]=-10;
				by[i]=-10;
			}
		}

		// move up/down
		//hy += 2*key_tri_vert();

		// increment/decrement starting tile with R/L
		tid += bit_tribool(key_hit(-1), KI_R, KI_L);

		// flip
		if(key_hit(KEY_R)) {	// horizontally
			hunter->attr1 ^= ATTR1_HFLIP;
			
		}
		if(key_hit(KEY_A)) {
			if(bx[0]<0) {
				by[0]=hy-5;
				bx[0]=hx+25;
			}
		}
		if(key_hit(KEY_B)) {
			if(bx[1]<0) {
				by[1]=hy-5;
				bx[1]=hx+25;
			}
		}
		
		// make it glow (via palette swapping)
		pb= key_is_down(KEY_SELECT) ? 1 : 0;

		// toggle mapping mode
		if(key_hit(KEY_START))
			REG_DISPCNT ^= DCNT_OBJ_1D;

		for(i=0; i<4; i++) {
			ducks[i].attr2= ATTR2_BUILD(frame/16%3*16, i%2, 0);
			obj_set_pos(&ducks[i], dx[i], dy[i]);
		}
		for(i=0; i<2; i++) {
			obj_set_pos(&bullets[i], bx[i], by[i]);
		}
		
		
		obj_set_pos(hunter, hx, hy);

		oam_copy(oam_mem, obj_buffer, 7);	// only need to update one
	}
}

int main()
{
	// Load palette
	memcpy(pal_bg_mem, backgroundPal, backgroundPalLen);
	// Load tiles into CBB 0
	memcpy(&tile_mem[0][0], backgroundTiles, backgroundTilesLen);
	// Load map into SBB 30
	memcpy(&se_mem[30][0], backgroundMap, backgroundMapLen);
	
	
	
	// Load ducks sprites
	memcpy(pal_obj_mem, duckPal, duckPalLen);
	memcpy(&tile_mem[4][0], duckTiles, duckTilesLen);

	oam_init(obj_buffer, 128);
	
	//REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D;
	
	

	// set up BG0 for a 4bpp 64x32t map, using
	//   using charblock 0 and screenblock 31
	REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32;
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
	
	REG_BG0HOFS= 0;
	REG_BG0VOFS= 0;
	
	obj_test();

	// Scroll around some
	int x= 192, y= 64;
	while(1)
	{
		vid_vsync();
		key_poll();

		x += key_tri_horz();
		y += key_tri_vert();

		
	}

	return 0;
}
