//
// background_demo.c
// Essential tilemap loading: the start of backgroundstar from metroid 1
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
	int x= 96, y= 32;
	u32 tid= 0, pb= 0;		// tile id, pal-bank

	OBJ_ATTR *metr= &obj_buffer[0];
	OBJ_ATTR *hunter= &obj_buffer[1];
	obj_set_attr(metr, 
		ATTR0_SQUARE,				// Square, regular sprite
		//ATTR1_SIZE_64,					// 64x64p, 
		ATTR1_SIZE_32,					// duck is 32x32p, 
		ATTR2_PALBANK(pb) | tid);		// palbank 0, tile 0

	
	obj_set_attr(hunter, 
		ATTR0_SQUARE,
		ATTR1_SIZE_32,
		ATTR2_PALBANK(0) | (16*3));		// palbank 0, tile 0


	// position sprite (redundant here; the _real_ position
	// is set further down
	obj_set_pos(metr, x, y);
	obj_set_pos(hunter, 50, 50);

	while(1)
	{
		vid_vsync();
		key_poll();

		// move left/right
		x += 2*key_tri_horz();

		// move up/down
		y += 2*key_tri_vert();

		// increment/decrement starting tile with R/L
		tid += bit_tribool(key_hit(-1), KI_R, KI_L);

		// flip
		if(key_hit(KEY_A))	// horizontally
			metr->attr1 ^= ATTR1_HFLIP;
		if(key_hit(KEY_B))	// vertically
			metr->attr1 ^= ATTR1_VFLIP;
		
		// make it glow (via palette swapping)
		pb= key_is_down(KEY_SELECT) ? 1 : 0;

		// toggle mapping mode
		if(key_hit(KEY_START))
			REG_DISPCNT ^= DCNT_OBJ_1D;

		// Hey look, it's one of them build macros!
		metr->attr2= ATTR2_BUILD(tid, pb, 0);
		obj_set_pos(metr, x, y);

		oam_copy(oam_mem, obj_buffer, 2);	// only need to update one
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
