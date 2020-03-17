
//{{BLOCK(duck)

//======================================================================
//
//	duck, 128x32@4, 
//	+ palette 256 entries, not compressed
//	+ 64 tiles 4x4 metatiles not compressed
//	Total size: 512 + 2048 = 2560
//
//	Time-stamp: 2020-03-17, 17:28:14
//	Exported by Cearn's Usenti v1.7.7
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

const unsigned short duckPal[256]=
{
	0x3400,0x56B5,0x7C1B,0x01E0,0x0000,0x7FFF,0x00E0,0x017F,
	0x0010,0x0200,0x0210,0x4000,0x4010,0x4200,0x6318,0x4210,
	0x001F,0x03E0,0x03FF,0x7C00,0x7C1F,0x7FE0,0x7FFF,0x0004,
	0x0007,0x000B,0x000F,0x0013,0x0017,0x001B,0x001F,0x0160,
	0x0260,0x02E0,0x0360,0x03E0,0x0084,0x00E7,0x016B,0x01EF,
	0x0273,0x02F7,0x037B,0x03FF,0x1000,0x1C00,0x2C00,0x3C00,
	0x4C00,0x5C00,0x6C00,0x7C00,0x1004,0x1C07,0x2C0B,0x3C0F,
	0x4C13,0x5C17,0x6C1B,0x7C1F,0x1080,0x1CE0,0x2D60,0x3DE0,

	0x4E60,0x5EE0,0x6F60,0x7FE0,0x0842,0x0C63,0x14A5,0x1CE7,
	0x2529,0x2D6B,0x35AD,0x3DEF,0x4631,0x4E73,0x5EF7,0x6739,
	0x6F7B,0x77BD,0x001F,0x007F,0x00FF,0x01FF,0x027F,0x02FF,
	0x037F,0x03FF,0x03FC,0x03F8,0x03F4,0x03F0,0x03EC,0x03E8,
	0x03E4,0x03E0,0x0FE0,0x1FE0,0x2FE0,0x3FE0,0x4FE0,0x5FE0,
	0x6FE0,0x7FE0,0x7F80,0x7F00,0x7E80,0x7E00,0x7D80,0x7D00,
	0x7C80,0x7C00,0x7C03,0x7C07,0x7C0B,0x7C0F,0x7C13,0x7C17,
	0x7C1F,0x701F,0x601F,0x501F,0x401F,0x301F,0x201F,0x101F,

	0x001F,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0421,0x0842,0x0C63,0x1084,0x14A5,0x18C6,0x1CE7,
	0x2108,0x2529,0x294A,0x2D6B,0x318C,0x35AD,0x39CE,0x3DEF,
	0x4210,0x4631,0x4A52,0x4E73,0x5294,0x56B5,0x5AD6,0x5EF7,
	0x6318,0x6739,0x6B5A,0x6F7B,0x739C,0x77BD,0x7BDE,0x7FFF,
};

const unsigned short duckTiles[1024]=
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4000,0x4444,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0033,
	0x3000,0x3333,0x3000,0x3553,0x3300,0x3545,0x3354,0x3555,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0077,0x0000,0x7777,0x0000,

	0x0000,0x0000,0x0000,0x4400,0x4404,0x4444,0x4440,0x4444,
	0x4450,0x4444,0x4500,0x4444,0x4500,0x4444,0x5500,0x4444,
	0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,
	0x4444,0x4444,0x4444,0x0444,0x4444,0x4444,0x4444,0x4444,
	0x3354,0x3333,0x3554,0x3333,0x3544,0x0333,0x3544,0x0333,
	0x0004,0x0000,0x0000,0x0000,0x0004,0x0000,0x0004,0x0000,
	0x7777,0x0000,0x7777,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x4445,0x0000,0x5555,0x0000,0x5500,0x0000,0x7700,
	0x0000,0x0777,0x0000,0x0777,0x0000,0x0077,0x0000,0x0000,
	0x4554,0x4444,0x5555,0x4444,0x5005,0x4444,0x0000,0x4445,
	0x0000,0x4450,0x0000,0x4450,0x0000,0x4550,0x0000,0x5500,
	0x0004,0x0000,0x0004,0x0000,0x0044,0x0000,0x0044,0x0000,
	0x0044,0x0000,0x0444,0x0000,0x0444,0x0000,0x0444,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4000,0x4444,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0033,
	0x3000,0x3333,0x3000,0x3553,0x3300,0x3545,0x3354,0x3555,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x7700,0x0000,0x7777,0x0000,0x0077,0x0000,

	0x0000,0x0000,0x0000,0x4400,0x4404,0x4444,0x4440,0x4444,
	0x4400,0x4444,0x4000,0x4444,0x4000,0x4444,0x0000,0x4444,
	0x4444,0x4444,0x4444,0x4444,0x4444,0x4455,0x5554,0x4455,
	0x5554,0x4555,0x5555,0x4555,0x5555,0x4455,0x4555,0x0004,
	0x3354,0x3333,0x3554,0x3333,0x3544,0x0333,0x3544,0x0333,
	0x0004,0x0000,0x0004,0x0000,0x0004,0x0000,0x0000,0x0000,
	0x0077,0x0000,0x0077,0x0000,0x0770,0x0000,0x7700,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x4440,0x0000,0x7700,0x0000,0x0777,0x0000,0x0777,
	0x0000,0x0077,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0444,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x4400,0x0044,0x5440,0x0045,0x5540,0x0045,0x5544,0x0045,
	0x5555,0x0045,0x5555,0x0055,0x5555,0x0055,0x5555,0x5555,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0033,
	0x3000,0x3333,0x3000,0x3553,0x3300,0x3545,0x3355,0x3555,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0077,0x0000,0x7777,0x0000,

	0x0000,0x0000,0x0000,0x4400,0x4404,0x4444,0x4440,0x4444,
	0x4450,0x5444,0x4550,0x5544,0x5500,0x5555,0x5500,0x5555,
	0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,0x5555,
	0x5555,0x5555,0x5555,0x0555,0x5555,0x0055,0x0555,0x0000,
	0x3355,0x3333,0x3555,0x3333,0x3555,0x0333,0x3555,0x0333,
	0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x7777,0x0000,0x7777,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x5000,0x5555,0x0000,0x7750,0x0000,0x0777,0x0000,0x0777,
	0x0000,0x0077,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0005,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x2200,
	0x0000,0x2220,0x0000,0x2220,0x0000,0x2200,0x0000,0x7700,
	0x0000,0x0000,0x0000,0x0000,0x0002,0x0000,0x0222,0x0000,
	0x0242,0x0000,0x0222,0x1600,0x0222,0x6660,0x6777,0x8886,
	0x0000,0x0000,0x0000,0x1100,0x0000,0x0110,0x0000,0x0011,
	0x1110,0x0001,0x6611,0x0000,0x6668,0x0000,0x0668,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x7770,0x0000,0x7777,0x0000,0x7777,0x0000,0x7777,
	0x0000,0x7777,0x7000,0x7777,0x7000,0x7777,0x7000,0x7777,
	0x7777,0x6688,0x7777,0x6667,0x7777,0x0666,0x6777,0x0066,
	0x6677,0x0076,0x7777,0x0077,0x7777,0x0077,0x7777,0x0077,
	0x0066,0x0000,0x0006,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x7000,0x7777,0x7000,0x7777,0x7000,0x7777,0x7000,0x7777,
	0x6000,0x7777,0x6000,0x7776,0x6000,0x0066,0x6000,0x0066,
	0x7777,0x0077,0x7777,0x0077,0x7777,0x0077,0x7777,0x0077,
	0x7777,0x0067,0x7777,0x0066,0x6000,0x0066,0x6000,0x0066,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x6000,0x0066,0x6000,0x0066,0x6000,0x0066,0x6000,0x0066,
	0x6000,0x0066,0x6000,0x0066,0x8000,0x8888,0x8000,0x8888,
	0x6000,0x0066,0x6000,0x0066,0x6000,0x0066,0x6000,0x0066,
	0x6000,0x0066,0x6000,0x0066,0x8000,0x8888,0x8000,0x8888,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

//}}BLOCK(duck)
