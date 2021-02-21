//
// background_demo.c
// Essential tilemap loading: the start of backgroundstar from ducksoid 1
//
// (20060221 - 20070216, cearn)

#include <string.h>
#include <tonc.h>
#include <stdio.h>

#include "version.h"
#include "background.h"
#include "background2.h"
#include "duck.h"

#define DUCKS_SIZE 4
#define BULLETS_SIZE 2


struct duck_s {
    int e,x,y,vx,vy;
    u32 shoot_time;
    OBJ_ATTR *object;
};

struct bullet_s {
    int e,x,y,vx,vy;
    OBJ_ATTR *object;
};

struct hunter_s {
    int x,y, flip, score;
    OBJ_ATTR *object;
};

struct game_s {
    struct duck_s ducks[DUCKS_SIZE];
    struct bullet_s bullets[2];
    struct hunter_s hunter;
    int cloud_pos;
    int objects;
    u32 frame;
};

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer= (OBJ_AFFINE*)obj_buffer;

struct game_s game;

void init_game() {
    int i=0;
    game.objects=0;
    game.cloud_pos=10;
    
    for(i=0; i<DUCKS_SIZE; i++) {
		game.ducks[i].x=i*50-200;
		game.ducks[i].y=32;
        game.ducks[i].vx=1;
        game.ducks[i].vy=0;
        game.ducks[i].e=1;
        game.ducks[i].object=&obj_buffer[game.objects++];
        obj_set_attr(game.ducks[i].object, 
			ATTR0_SQUARE,
			ATTR1_SIZE_32,
			ATTR2_PALBANK(0) | ATTR2_PRIO(1) | 0);
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
        game.bullets[i].e=0;
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
        // Duck flying
        if(game.ducks[i].vx>0) {
            game.ducks[i].object->attr2= ATTR2_BUILD(game.frame/16%3*16, i%2, 1);
        }
        else if(game.ducks[i].vx==0) {
            game.ducks[i].object->attr2= ATTR2_BUILD(5*16, i%2, 1);
        }
        
        obj_set_pos(game.ducks[i].object, game.ducks[i].x, game.ducks[i].y);
    }
    for(i=0; i<BULLETS_SIZE; i++) {
        obj_set_pos(game.bullets[i].object, game.bullets[i].x, game.bullets[i].y);
    }
    
    if(game.hunter.flip==1) {
        game.hunter.object->attr1 &= ~ATTR1_HFLIP;
    }
    else if(game.hunter.flip==-1) {
        game.hunter.object->attr1 |= ATTR1_HFLIP;
    }
    obj_set_pos(game.hunter.object, game.hunter.x, game.hunter.y);
    
    // Clouds scroll
    REG_BG1HOFS=game.cloud_pos;

    oam_copy(oam_mem, obj_buffer, game.objects);
}

void update_game() {
    int i,j;
    char buffer[10];
    // move left/right
		game.hunter.x += 2*key_tri_horz();
		if(game.frame%2) {
			for(i=0; i<DUCKS_SIZE; i++) {
                if(game.ducks[i].x<240 && game.ducks[i].y<160) {
                    game.ducks[i].x+=game.ducks[i].vx;
                    game.ducks[i].y+=game.ducks[i].vy;
                }
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
        
        // Check collisions
      for(i=0; i<BULLETS_SIZE; i++)
      {
        for(j=0; j<DUCKS_SIZE; j++)
        {
          if(
          game.bullets[i].e && game.ducks[j].e &&
        (game.bullets[i].x-game.ducks[j].x+16) * (game.bullets[i].x-game.ducks[j].x+16) < 25*25
        && (game.bullets[i].y-game.ducks[j].y+4) * (game.bullets[i].y-game.ducks[j].y+4) < 25*25)
          {
              REG_SND1FREQ = SFREQ_RESET | SND_RATE(NOTE_C, -2);
              game.ducks[j].shoot_time=game.frame;
              game.ducks[j].vx=0;
              game.ducks[j].vy=3;
              game.hunter.score++;
              // Update score in screen
              tte_write("#{P:16,152}");
			  tte_write("#{cx:0x1000}");
			  sprintf(buffer, "%02u", game.hunter.score);
			  tte_write(buffer);
              
              game.bullets[i].e=0;
          }
        }
      }

		// move up/down
		//game.hunter.y += 2*key_tri_vert();

		// flip
		if(key_hit(KEY_R)) {
			game.hunter.flip=1;
		}
		if(key_hit(KEY_L)) {
			game.hunter.flip=-1;
		}
		if(key_hit(KEY_A)) {
			if(game.bullets[0].x<0) {
				REG_SND4FREQ = SFREQ_RESET | SND_RATE(NOTE_C, -3);
				game.bullets[0].y=game.hunter.y-5;
                game.bullets[0].vx=game.hunter.flip;
                game.bullets[0].vy=-1;
                game.bullets[0].e=1;
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
				REG_SND4FREQ = SFREQ_RESET | SND_RATE(NOTE_C, -3);
				game.bullets[1].y=game.hunter.y-5;
                game.bullets[1].vx=game.hunter.flip;
				game.bullets[1].vy=-1;
                game.bullets[1].e=1;
                if(game.hunter.flip==1) {
					game.bullets[1].x=game.hunter.x+25;
				}
				else {
					game.bullets[1].x=game.hunter.x;
				}
			}
		}
		
		if(key_hit(KEY_START)) {
            for(i=0; i<DUCKS_SIZE; i++) {
                game.ducks[i].x=i*50-200;
                game.ducks[i].y=32;
                game.ducks[i].vx=1;
                game.ducks[i].vy=0;
            }
        }
        
        // Move clouds
        if(game.frame%3==0)
        {
			game.cloud_pos+=1;
		}
}


void init_sound() {
    // turn sound on
	REG_SNDSTAT= SSTAT_ENABLE;
	// snd1 on left/right ; both full volume
	REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1 | SDMG_NOISE, 7);
	// DMG ratio to 100%
	REG_SNDDSCNT= SDS_DMG100;
	// no sweep
	REG_SND1SWEEP= SSW_OFF;
	// envelope: vol=12, decay, max step time (7) ; 50% duty
	REG_SND1CNT= SSQR_ENV_BUILD(12, 0, 1) | SSQR_DUTY1_2;
	REG_SND1FREQ= 0;
    REG_SND4CNT= SSQR_ENV_BUILD(12, 0, 1) | SSQR_DUTY1_2;
	REG_SND4FREQ= 0;
}

void load_background() {
    // Load palette
	memcpy(pal_bg_mem, backgroundPal, backgroundPalLen);
	// Load tiles into CBB 0
	memcpy(&tile_mem[0][0], backgroundTiles, backgroundTilesLen);
	// Load map into SBB 3
	memcpy(&se_mem[3][0], backgroundMap, backgroundMapLen);
	
    // set up BG0 for a 4bpp 64x32t map, using
	//   using charblock 0 and screenblock 3
	REG_BG0CNT= BG_CBB(0) | BG_SBB(3) | BG_4BPP | BG_REG_64x32 | BG_PRIO(1);
	
	// Backround H scroll
	REG_BG0HOFS= 0;
    // Background V scroll
	REG_BG0VOFS= 0;
	
	
	// Load tiles background1 into CBB 1
	memcpy(&tile_mem[1][0], background2Tiles, background2TilesLen);
	// Load map background1 into SBB 11
	memcpy(&se_mem[11][0], background2Map, background2MapLen);
	// Config background1
	REG_BG1CNT= BG_CBB(1) | BG_SBB(11) | BG_4BPP | BG_REG_64x32 | BG_PRIO(0);
	// Backround1 H scroll
	REG_BG1HOFS=10;
    // Background1 V scroll
	REG_BG1VOFS=-15;
	
	tte_write("#{P:16,152}");
	tte_write("#{cx:0x1000}");
	tte_write("00");
}

void load_sprites() {
    // Load ducks sprites
	memcpy(pal_obj_mem, duckPal, duckPalLen);
	memcpy(&tile_mem[4][0], duckTiles, duckTilesLen);
	oam_init(obj_buffer, 128);
	
}

void run_version() {
	int timeout=200;
	pal_bg_bank[1][15]= CLR_WHITE;    
	tte_write("#{cx:0x1000}");
	
	tte_write("#{P:50,16}www.emiliollbb.net");
	tte_write("#{P:90,64}PRESENTS");
	tte_write("#{P:75,100}DUCK HUNTER");
	tte_write("#{P:0,152}");
	tte_write(VERSION);
	
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG3;
	
	while(timeout>0)
	{
		VBlankIntrWait();
		timeout--;
	}
	tte_write("#{es}");
}

int main()
{
	// Init interrupts, and enable VBlank irq
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);
	
	init_sound();
	tte_init_se(
        3,                      // Background number (BG 0)
        BG_CBB(3)|BG_SBB(30),   // BG control (for REG_BGxCNT)
        0,                      // Tile offset (special cattr)
        CLR_YELLOW,             // Ink color
        14,                     // BitUnpack offset (on-pixel = 15)
        NULL,                   // Default font (sys8) 
        NULL);                  // Default renderer (se_drawg_s)
	
	run_version();
	
	load_background();
	
	load_sprites();
		
    // Init Display
    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG3 | DCNT_OBJ | DCNT_OBJ_1D;
    
    
	init_game();
	
	while(1)
	{
		VBlankIntrWait();
		game.frame++;
		key_poll();

		update_game();
		render_frame();
	}

	return 0;
}
