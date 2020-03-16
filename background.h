
//{{BLOCK(background)

//======================================================================
//
//	background, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 6 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 192 + 2048 = 2752
//
//	Time-stamp: 2020-03-16, 18:06:45
//	Exported by Cearn's Usenti v1.7.7
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

#ifndef __BACKGROUND__
#define __BACKGROUND__

#define backgroundPalLen 512
extern const unsigned short backgroundPal[256];

#define backgroundTilesLen 192
extern const unsigned short backgroundTiles[96];

#define backgroundMapLen 2048
extern const unsigned short backgroundMap[1024];

#endif // __BACKGROUND__

//}}BLOCK(background)
