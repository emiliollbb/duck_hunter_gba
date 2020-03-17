//
// toolbox.h: 
// 
// Tools header for obj_demo
// 
// (20060211-20060924, cearn)
//
// === NOTES ===
// * This is a _small_ set of typedefs, #defines and inlines that can 
//   be found in tonclib, and might not represent the 
//   final forms.


#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "types.h"		// (tonc_types.h)
#include "memmap.h"		// (tonc_memmap.h)
#include "memdef.h"		// (tonc_memdef.h)
#include "input.h"		// (tonc_input.h)


typedef u16 SCR_ENTRY, SE;
typedef SCR_ENTRY	SCREENBLOCK[1024];
#define se_mem			((SCREENBLOCK*)MEM_VRAM)
#define REG_BG0CNT			*(vu16*)(REG_BASE+0x0008)	// bg 0-3 control
#define REG_BG1CNT			*(vu16*)(REG_BASE+0x000A)
#define REG_BG2CNT			*(vu16*)(REG_BASE+0x000C)
#define REG_BG3CNT			*(vu16*)(REG_BASE+0x000E)

#define REG_BG0HOFS			*(vu16*)(REG_BASE+0x0010)		// bg 0-3 origins
#define REG_BG0VOFS			*(vu16*)(REG_BASE+0x0012)
#define REG_BG1HOFS			*(vu16*)(REG_BASE+0x0014)
#define REG_BG1VOFS			*(vu16*)(REG_BASE+0x0016)
#define REG_BG2HOFS			*(vu16*)(REG_BASE+0x0018)
#define REG_BG2VOFS			*(vu16*)(REG_BASE+0x001A)
#define REG_BG3HOFS			*(vu16*)(REG_BASE+0x001C)
#define REG_BG3VOFS			*(vu16*)(REG_BASE+0x001E)

#define BG_MOSAIC			0x0040	//!< Enable Mosaic
#define BG_4BPP					 0	//!< 4bpp (16 color) bg (no effect on affine bg)
#define BG_8BPP				0x0080	//!< 8bpp (256 color) bg (no effect on affine bg)
#define BG_WRAP				0x2000	//!< Wrap around edges of affine bgs
#define BG_SIZE0				 0
#define BG_SIZE1			0x4000
#define BG_SIZE2			0x8000
#define BG_SIZE3			0xC000
#define BG_REG_32x32			 0	//!< reg bg, 32x32 (256x256 px)
#define BG_REG_64x32		0x4000	//!< reg bg, 64x32 (512x256 px)
#define BG_REG_32x64		0x8000	//!< reg bg, 32x64 (256x512 px)
#define BG_REG_64x64		0xC000	//!< reg bg, 64x64 (512x512 px)
#define BG_AFF_16x16			 0	//!< affine bg, 16x16 (128x128 px)
#define BG_AFF_32x32		0x4000	//!< affine bg, 32x32 (256x256 px)
#define BG_AFF_64x64		0x8000	//!< affine bg, 64x64 (512x512 px)
#define BG_AFF_128x128		0xC000	//!< affine bg, 128x128 (1024x1024 px)

#define BG_PRIO_MASK	0x0003
#define BG_PRIO_SHIFT		0
#define BG_PRIO(n)		((n)<<BG_PRIO_SHIFT)

#define BG_CBB_MASK		0x000C
#define BG_CBB_SHIFT		 2
#define BG_CBB(n)		((n)<<BG_CBB_SHIFT)

#define BG_SBB_MASK		0x1F00
#define BG_SBB_SHIFT		 8
#define BG_SBB(n)		((n)<<BG_SBB_SHIFT)

#define BG_SIZE_MASK	0xC000
#define BG_SIZE_SHIFT		14
#define BG_SIZE(n)		((n)<<BG_SIZE_SHIFT)


#define BG_BUILD(cbb, sbb, size, bpp, prio, mos, wrap)		\
(															\
	   ((size)<<14)  | (((wrap)&1)<<13) | (((sbb)&31)<<8	\
	| (((bpp)&8)<<4) | (((mos)&1)<<6)   | (((cbb)&3)<<2)	\
	| ((prio)&3)											\
)


// === (tonc_core.h) ==================================================

// tribool: 1 if {plus} on, -1 if {minus} on, 0 if {plus}=={minus}
INLINE int bit_tribool(u32 x, int plus, int minus);


extern COLOR *vid_page;
extern u16 __key_curr, __key_prev;


// === (tonc_video.h) =================================================

// --- sizes ---
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

#define M3_WIDTH	SCREEN_WIDTH
#define M3_HEIGHT	SCREEN_HEIGHT
#define M4_WIDTH	SCREEN_WIDTH
#define M4_HEIGHT	SCREEN_HEIGHT
#define M5_WIDTH	160
#define M5_HEIGHT	128

// --- colors ---

#define CLR_BLACK	0x0000
#define CLR_RED		0x001F
#define CLR_LIME	0x03E0
#define CLR_YELLOW	0x03FF
#define CLR_BLUE	0x7C00
#define CLR_MAG		0x7C1F
#define CLR_CYAN	0x7FE0
#define CLR_WHITE	0x7FFF

INLINE COLOR RGB15(u32 red, u32 green, u32 blue);

INLINE void vid_vsync();
u16 *vid_flip();


// --- Objects  ---

void oam_init(OBJ_ATTR *obj, u32 count);
void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count);

INLINE OBJ_ATTR *obj_set_attr(OBJ_ATTR *obj, u16 a0, u16 a1, u16 a2);
INLINE void obj_set_pos(OBJ_ATTR *obj, int x, int y);
INLINE void obj_hide(OBJ_ATTR *oatr);
INLINE void obj_unhide(OBJ_ATTR *obj, u16 mode);
void obj_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count);


// === INLINES ========================================================

// --- (tonc_core.h) --------------------------------------------------

// --- Simple bit macros ---
#define BIT(n)					( 1<<(n) )
#define BIT_SHIFT(a, n)			( (a)<<(n) )
#define BIT_SET(word, flag)		( word |=  (flag) )
#define BIT_CLEAR(word, flag)	( word &= ~(flag) )
#define BIT_FLIP(word, flag)	( word ^=  (flag) )
#define BIT_EQ(word, flag)		( ((word)&(flag)) == (flag) )

// some EVIL bit-field operations, >:)
// _x needs shifting
#define BFN_PREP(x, name)		( ((x)<<name##_SHIFT) & name##_MASK )
#define BFN_GET(y, name)			( ((y) & name##_MASK)>>name##_SHIFT )
#define BFN_SET(y, x, name)		(y = ((y)&~name##_MASK) | BFN_PREP(x,name) )

// x already shifted
#define BFN_PREP2(x, name)		( (x) & name##_MASK )
#define BFN_GET2(y, name)		( (y) & name##_MASK )
#define BFN_SET2(y, x, name)		(y = ((y)&~name##_MASK) | BFN_PREP2(x,name) )

//! Gives a tribool (-1, 0, or +1) depending on the state of some bits.
/*! Looks at the \a plus and \a minus bits of \a flags, and subtracts 
*	  their status to give a +1, -1 or 0 result. Useful for direction flags.
*	\param plus		Bit number for positive result
*	\param minus	Bit number for negative result
*	\return	<b>+1</b> if \a plus bit is set but \a minus bit isn't<br>
*	  <b>-1</b> if \a minus bit is set and \a plus bit isn't</br>
*	  <b>0</b> if neither or both are set.
*/
INLINE int bit_tribool(u32 flags, int plus, int minus)
{	return ((flags>>plus)&1) - ((flags>>minus)&1);	}


// --- (tonc_video.h) -------------------------------------------------

//! Wait for next VBlank
INLINE void vid_vsync()
{
	while(REG_VCOUNT >= 160);	// wait till VDraw
	while(REG_VCOUNT < 160);	// wait till VBlank
}

//! Create a 15bit BGR color.
INLINE COLOR RGB15(u32 red, u32 green, u32 blue)
{	return red | (green<<5) | (blue<<10);	}


// --- Objects ---


//! Set the attributes of an object.
INLINE OBJ_ATTR *obj_set_attr(OBJ_ATTR *obj, u16 a0, u16 a1, u16 a2)
{
	obj->attr0= a0; obj->attr1= a1; obj->attr2= a2;
	return obj;
}

//! Set the position of \a obj
INLINE void obj_set_pos(OBJ_ATTR *obj, int x, int y)
{
	BFN_SET(obj->attr0, y, ATTR0_Y);
	BFN_SET(obj->attr1, x, ATTR1_X);
}

//! Hide an object.
INLINE void obj_hide(OBJ_ATTR *obj)
{	BFN_SET2(obj->attr0, ATTR0_HIDE, ATTR0_MODE);		}

//! Unhide an object.
/*! \param obj	Object to unhide.
*	\param mode	Object mode to unhide to. Necessary because this affects
*	  the affine-ness of the object.
*/
INLINE void obj_unhide(OBJ_ATTR *obj, u16 mode)
{	BFN_SET2(obj->attr0, mode, ATTR0_MODE);			}


#endif // TOOLBOX_H
