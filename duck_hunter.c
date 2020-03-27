//
// background_demo.c
// Essential tilemap loading: the start of backgroundstar from ducksoid 1
//
// (20060221 - 20070216, cearn)

#include <string.h>
#include <tonc.h>

#include "background.h"
#include "duck.h"

#define DUCKS_SIZE 4
#define BULLETS_SIZE 2


struct duck_s {
    int x,y;
    OBJ_ATTR *object;
};

struct bullet_s {
    int x,y,vx,vy;
    OBJ_ATTR *object;
};

struct hunter_s {
    int x,y, flip;
    OBJ_ATTR *object;
};

struct game_s {
    struct duck_s ducks[DUCKS_SIZE];
    struct bullet_s bullets[2];
    struct hunter_s hunter;
    int objects;
    int frame;
};

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

struct game_s game;
u32 frame = 0;

void init_game() {
    int i=0;
    game.objects=0;
    
    for(i=0; i<DUCKS_SIZE; i++) {
		game.ducks[i].x=i*50;
		game.ducks[i].y=32;
        game.ducks[i].object=&obj_buffer[game.objects++];
        obj_set_attr(game.ducks[i].object, 
			ATTR0_SQUARE,
			ATTR1_SIZE_32,
			ATTR2_PALBANK(0) | 0);
	}
    
    game.hunter.x=0;
    game.hunter.y=160-32-32;
    game.hunter.flip=1;
    game.hunter.object=&obj_buffer[game.objects++];
    obj_set_attr(game.hunter.object, 
		ATTR0_SQUARE,
		ATTR1_SIZE_32,
		ATTR2_PALBANK(0) | (16*3));
    	
	for(i=0; i<BULLETS_SIZE; i++) {
		game.bullets[i].x=-10;
		game.bullets[i].y=-10;
        game.bullets[i].object=&obj_buffer[game.objects++];
        obj_set_attr(game.bullets[i].object, 
			ATTR0_SQUARE,
			ATTR1_SIZE_8,
			ATTR2_PALBANK(0) | (16*4));
	}
    
}

void render_frame() {
    int i;
    
    for(i=0; i<DUCKS_SIZE; i++) {
        game.ducks[i].object->attr2= ATTR2_BUILD(frame/16%3*16, i%2, 0);
        obj_set_pos(game.ducks[i].object, game.ducks[i].x, game.ducks[i].y);
    }
    for(i=0; i<BULLETS_SIZE; i++) {
        obj_set_pos(game.bullets[i].object, game.bullets[i].x, game.bullets[i].y);
    }
    
    obj_set_pos(game.hunter.object, game.hunter.x, game.hunter.y);

    oam_copy(oam_mem, obj_buffer, game.objects);
}

// testing a few sprite things
// D-pad: move 
// SELECT: switch palette
// START: toggle mapping mode
// A: horizontal flip
// B: vertical flip
// L & R shift starting tile
void obj_test()
{
	int i=0;
	
		
	
	init_game();
	

	//obj_set_pos(game.hunter.object, game.hunter.x, game.hunter.y);

	while(1)
	{
		VBlankIntrWait();
		frame++;
		key_poll();

		// move left/right
		game.hunter.x += 2*key_tri_horz();
		if(frame%2) {
			for(i=0; i<4; i++) {
				game.ducks[i].x++;
			}
		}
		
		for(i=0; i<BULLETS_SIZE; i++) {
			if(game.bullets[i].x>-10) {
				game.bullets[i].x+=game.bullets[i].vx;
				game.bullets[i].y+=game.bullets[i].vy;
			}
			if(game.bullets[i].x>240 || game.bullets[i].y<0 || game.bullets[i].x<-8) {
				game.bullets[i].x=-10;
				game.bullets[i].y=-10;
			}
		}

		// move up/down
		//game.hunter.y += 2*key_tri_vert();

		// flip
		if(key_hit(KEY_R)) {
			game.hunter.object->attr1 &= ~ATTR1_HFLIP;
			game.hunter.flip=1;
		}
		if(key_hit(KEY_L)) {
			game.hunter.object->attr1 |= ATTR1_HFLIP;
			game.hunter.flip=-1;
		}
		if(key_hit(KEY_A)) {
			if(game.bullets[0].x<0) {
				REG_SND1FREQ = SFREQ_RESET | SND_RATE(NOTE_C, -2);
				game.bullets[0].y=game.hunter.y-5;
                game.bullets[0].vx=game.hunter.flip;
                game.bullets[0].vy=-1;
				if(game.hunter.flip==1) {
					game.bullets[0].x=game.hunter.x+25;
				}
				else {
					game.bullets[0].x=game.hunter.x;
				}
			}
		}
		if(key_hit(KEY_B)) {
			if(game.bullets[1].x<0) {
				REG_SND1FREQ = SFREQ_RESET | SND_RATE(NOTE_C, -2);
				game.bullets[1].y=game.hunter.y-5;
                game.bullets[1].vx=game.hunter.flip;
				game.bullets[1].vy=-1;
                if(game.hunter.flip==1) {
					game.bullets[1].x=game.hunter.x+25;
				}
				else {
					game.bullets[1].x=game.hunter.x;
				}
			}
		}
		
		// toggle mapping mode
		if(key_hit(KEY_START)) {
			            
        }

		render_frame();
		
		
		
	}
}

void init_sound() {
    // turn sound on
	REG_SNDSTAT= SSTAT_ENABLE;
	// snd1 on left/right ; both full volume
	REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1, 7);
	// DMG ratio to 100%
	REG_SNDDSCNT= SDS_DMG100;
	// no sweep
	REG_SND1SWEEP= SSW_OFF;
	// envelope: vol=12, decay, max step time (7) ; 50% duty
	REG_SND1CNT= SSQR_ENV_BUILD(12, 0, 1) | SSQR_DUTY1_2;
	REG_SND1FREQ= 0;
}

void load_background() {
    // Load palette
	memcpy(pal_bg_mem, backgroundPal, backgroundPalLen);
	// Load tiles into CBB 0
	memcpy(&tile_mem[0][0], backgroundTiles, backgroundTilesLen);
	// Load map into SBB 30
	memcpy(&se_mem[30][0], backgroundMap, backgroundMapLen);
	
}

void load_sprites() {
    // Load ducks sprites
	memcpy(pal_obj_mem, duckPal, duckPalLen);
	memcpy(&tile_mem[4][0], duckTiles, duckTilesLen);
	oam_init(obj_buffer, 128);
	
}

int main()
{
	// Init interrupts, and enable VBlank irq
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	
	init_sound();
	
	load_background();
	
	load_sprites();
	
	
	// set up BG0 for a 4bpp 64x32t map, using
	//   using charblock 0 and screenblock 31
	REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32;
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
	// Backround H scroll
	REG_BG0HOFS= 0;
    // Background V scroll
	REG_BG0VOFS= 0;
	
	obj_test();

	

	return 0;
}
