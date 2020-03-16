//
// background_demo.c
// Essential tilemap loading: the start of backgroundstar from metroid 1
//
// (20060221 - 20070216, cearn)

#include <string.h>

#include "toolbox.h"
#include "input.h"
#include "background.h"

int main()
{
	// Load palette
	memcpy(pal_bg_mem, backgroundPal, backgroundPalLen);
	// Load tiles into CBB 0
	memcpy(&tile_mem[0][0], backgroundTiles, backgroundTilesLen);
	// Load map into SBB 30
	memcpy(&se_mem[30][0], backgroundMap, backgroundMapLen);

	// set up BG0 for a 4bpp 64x32t map, using
	//   using charblock 0 and screenblock 31
	REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32;
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;
	
	REG_BG0HOFS= 0;
	REG_BG0VOFS= 0;

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
