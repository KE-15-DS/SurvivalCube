// 2024-2025 ikasturtea

/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

#include "spriteak.h"
#include "definizioak.h"

u16* gfxmago;
u16* gfxzombi;
u16* gfxgolem;
u16* gfxmurcielago;
u16* gfxbolaFuego;

/* Pantailan erakutsi nahi den sprite bakoitzeko memoria erreserbatu.*/
void memoriaErreserbatu()
{
	//oamClear(&oamMain, 0, 0);
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxmago= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxzombi= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxmurcielago= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxgolem= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxbolaFuego= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu PANTAILA NAGUSIAN. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. SPRITEARI KOLOREAK ESLEITZEKO ALDATU*/
void PaletaNagusiaEzarri() 
{
 	// mago
 	SPRITE_PALETTE[0] = RGB15(0,0,0);
 	SPRITE_PALETTE[1] = RGB15(5,5,5);
 	SPRITE_PALETTE[2] = RGB15(0,0,1);
 	SPRITE_PALETTE[3] = RGB15(3,3,4);
 	SPRITE_PALETTE[4] = RGB15(7,7,7);
 	SPRITE_PALETTE[5] = RGB15(1,2,3);
 	SPRITE_PALETTE[6] = RGB15(29,28,20);
 	SPRITE_PALETTE[7] = RGB15(6,10,3);
 	SPRITE_PALETTE[8] = RGB15(0,0,0);
 	SPRITE_PALETTE[9] = RGB15(6,6,4);
 	SPRITE_PALETTE[10] = RGB15(1,1,2);
 	SPRITE_PALETTE[11] = RGB15(28,25,26);
 	SPRITE_PALETTE[12] = RGB15(21,14,9);
 	SPRITE_PALETTE[13] = RGB15(26,22,15);
 	SPRITE_PALETTE[14] = RGB15(6,11,4);
 	SPRITE_PALETTE[15] = RGB15(0,1,1);
 	SPRITE_PALETTE[16] = RGB15(12,24,3);
 	SPRITE_PALETTE[17] = RGB15(3,9,9);
 	SPRITE_PALETTE[18] = RGB15(23,29,12);
 	SPRITE_PALETTE[19] = RGB15(20,25,26);
 	SPRITE_PALETTE[20] = RGB15(0,2,1);
 	SPRITE_PALETTE[21] = RGB15(0,17,9);
 	SPRITE_PALETTE[22] = RGB15(2,3,4);
 	SPRITE_PALETTE[23] = RGB15(29,23,21);
 	SPRITE_PALETTE[24] = RGB15(0,0,0);
 	SPRITE_PALETTE[25] = RGB15(3,9,6);
 	SPRITE_PALETTE[26] = RGB15(23,17,20);
 	SPRITE_PALETTE[27] = RGB15(0,10,10);
 	SPRITE_PALETTE[28] = RGB15(1,1,2);
 	SPRITE_PALETTE[29] = RGB15(14,19,28);
 	SPRITE_PALETTE[30] = RGB15(20,25,30);
 	SPRITE_PALETTE[31] = RGB15(0,0,0);
 	SPRITE_PALETTE[32] = RGB15(2,2,2);
 	SPRITE_PALETTE[33] = RGB15(5,5,5);
 	SPRITE_PALETTE[34] = RGB15(1,1,2);
 	SPRITE_PALETTE[35] = RGB15(4,4,4);
 	SPRITE_PALETTE[36] = RGB15(30,30,26);
 	SPRITE_PALETTE[37] = RGB15(2,2,3);
 	SPRITE_PALETTE[38] = RGB15(8,8,8);
 	SPRITE_PALETTE[39] = RGB15(1,1,2);
 	SPRITE_PALETTE[40] = RGB15(1,2,1);
 	SPRITE_PALETTE[41] = RGB15(2,2,3);
 	SPRITE_PALETTE[42] = RGB15(1,1,2);
 	SPRITE_PALETTE[43] = RGB15(1,3,1);
 	SPRITE_PALETTE[44] = RGB15(3,3,4);
 	SPRITE_PALETTE[45] = RGB15(0,1,2);
 	SPRITE_PALETTE[46] = RGB15(0,17,9);
 	SPRITE_PALETTE[47] = RGB15(0,2,0);
 	SPRITE_PALETTE[48] = RGB15(3,3,4);
 	SPRITE_PALETTE[49] = RGB15(0,0,1);
 	SPRITE_PALETTE[50] = RGB15(0,12,12);
 	SPRITE_PALETTE[51] = RGB15(0,1,1);
 	SPRITE_PALETTE[52] = RGB15(3,4,4);
 	SPRITE_PALETTE[53] = RGB15(0,0,1);
 	SPRITE_PALETTE[54] = RGB15(17,11,6);
 	SPRITE_PALETTE[55] = RGB15(0,0,0);
 	SPRITE_PALETTE[56] = RGB15(5,5,5);
 	SPRITE_PALETTE[57] = RGB15(0,0,1);
 	SPRITE_PALETTE[58] = RGB15(1,0,0);
 	SPRITE_PALETTE[59] = RGB15(4,4,4);
 	SPRITE_PALETTE[60] = RGB15(9,4,3);
 	SPRITE_PALETTE[61] = RGB15(2,0,0);
 	SPRITE_PALETTE[62] = RGB15(9,9,12);
 	SPRITE_PALETTE[63] = RGB15(1,2,3);
 	SPRITE_PALETTE[64] = RGB15(10,13,25);
 	SPRITE_PALETTE[65] = RGB15(1,1,2);
 	SPRITE_PALETTE[66] = RGB15(9,8,20);
 	SPRITE_PALETTE[67] = RGB15(3,3,4);
 	SPRITE_PALETTE[68] = RGB15(1,1,3);
 	SPRITE_PALETTE[69] = RGB15(24,15,8);
 	SPRITE_PALETTE[70] = RGB15(29,19,13);
 	SPRITE_PALETTE[71] = RGB15(2,2,4);
 	SPRITE_PALETTE[72] = RGB15(17,16,16);
 	SPRITE_PALETTE[73] = RGB15(21,19,18);
 	SPRITE_PALETTE[74] = RGB15(0,0,1);
 	SPRITE_PALETTE[75] = RGB15(12,12,13);
 	SPRITE_PALETTE[76] = RGB15(0,1,4);
 	SPRITE_PALETTE[77] = RGB15(3,3,4);
 	SPRITE_PALETTE[78] = RGB15(3,3,4);
 	SPRITE_PALETTE[79] = RGB15(10,10,10);
 	SPRITE_PALETTE[80] = RGB15(1,0,0);
 	SPRITE_PALETTE[81] = RGB15(1,0,0);
 	SPRITE_PALETTE[82] = RGB15(1,0,0);
 	SPRITE_PALETTE[83] = RGB15(19,10,6);
 	SPRITE_PALETTE[84] = RGB15(9,4,3);
 	SPRITE_PALETTE[85] = RGB15(1,0,0);
 	SPRITE_PALETTE[86] = RGB15(1,0,0);
 	SPRITE_PALETTE[87] = RGB15(1,0,0);
 	SPRITE_PALETTE[88] = RGB15(2,3,4);
 	SPRITE_PALETTE[89] = RGB15(1,0,0);
 	SPRITE_PALETTE[90] = RGB15(26,24,23);
 	SPRITE_PALETTE[91] = RGB15(8,8,13);
 	SPRITE_PALETTE[92] = RGB15(1,1,2);
 	SPRITE_PALETTE[93] = RGB15(2,1,1);

	//zombi
	SPRITE_PALETTE[94] = RGB15(3,3,3);
	SPRITE_PALETTE[95] = RGB15(1,1,1);
	SPRITE_PALETTE[96] = RGB15(21,22,11);
	SPRITE_PALETTE[97] = RGB15(28,27,16);
	SPRITE_PALETTE[98] = RGB15(12,17,10);
	SPRITE_PALETTE[99] = RGB15(2,2,2);
	SPRITE_PALETTE[100] = RGB15(7,6,10);
	SPRITE_PALETTE[101] = RGB15(1,1,1);
	SPRITE_PALETTE[102] = RGB15(1,0,0);
	SPRITE_PALETTE[103] = RGB15(25,2,2);
	SPRITE_PALETTE[104] = RGB15(8,8,8);
	SPRITE_PALETTE[105] = RGB15(0,0,0);
	SPRITE_PALETTE[106] = RGB15(19,10,6);
	SPRITE_PALETTE[107] = RGB15(20,2,5);
	SPRITE_PALETTE[108] = RGB15(12,5,3);
	SPRITE_PALETTE[109] = RGB15(2,2,2);
	SPRITE_PALETTE[110] = RGB15(13,9,5);
	SPRITE_PALETTE[111] = RGB15(2,2,2);
	SPRITE_PALETTE[112] = RGB15(28,8,8);
	SPRITE_PALETTE[113] = RGB15(2,0,0);
	SPRITE_PALETTE[114] = RGB15(25,2,2);
	SPRITE_PALETTE[115] = RGB15(3,2,2);
	SPRITE_PALETTE[116] = RGB15(2,2,1);
	SPRITE_PALETTE[117] = RGB15(12,14,8);
	SPRITE_PALETTE[118] = RGB15(0,0,0);
	SPRITE_PALETTE[119] = RGB15(2,2,1);
	SPRITE_PALETTE[120] = RGB15(21,14,11);
	SPRITE_PALETTE[121] = RGB15(1,1,0);
	SPRITE_PALETTE[122] = RGB15(1,0,0);
	SPRITE_PALETTE[123] = RGB15(1,0,0);
	SPRITE_PALETTE[124] = RGB15(0,0,0);
	SPRITE_PALETTE[125] = RGB15(3,2,0);
	SPRITE_PALETTE[126] = RGB15(8,5,4);
	SPRITE_PALETTE[127] = RGB15(1,1,0);
	SPRITE_PALETTE[128] = RGB15(1,0,0);
	SPRITE_PALETTE[129] = RGB15(0,0,0);
	SPRITE_PALETTE[130] = RGB15(1,1,0);
	SPRITE_PALETTE[131] = RGB15(16,2,8);
	SPRITE_PALETTE[132] = RGB15(0,0,0);
	SPRITE_PALETTE[133] = RGB15(3,2,2);
	SPRITE_PALETTE[134] = RGB15(1,1,1);
	SPRITE_PALETTE[135] = RGB15(9,8,12);
	SPRITE_PALETTE[136] = RGB15(2,2,1);
	SPRITE_PALETTE[137] = RGB15(2,1,1);
	SPRITE_PALETTE[138] = RGB15(2,0,0);
	SPRITE_PALETTE[139] = RGB15(1,0,0);
	SPRITE_PALETTE[140] = RGB15(1,1,1);
	SPRITE_PALETTE[141] = RGB15(1,0,1);
	SPRITE_PALETTE[142] = RGB15(1,1,1);
	SPRITE_PALETTE[143] = RGB15(1,1,1);

	// golem
	SPRITE_PALETTE[144] = RGB15(9,9,9);
	SPRITE_PALETTE[145] = RGB15(3,3,3);
	SPRITE_PALETTE[146] = RGB15(7,7,7);
	SPRITE_PALETTE[147] = RGB15(3,3,3);
	SPRITE_PALETTE[148] = RGB15(8,7,7);
	SPRITE_PALETTE[149] = RGB15(9,9,9);
	SPRITE_PALETTE[150] = RGB15(9,9,9);
	SPRITE_PALETTE[151] = RGB15(20,20,20);
	SPRITE_PALETTE[152] = RGB15(2,2,2);
	SPRITE_PALETTE[153] = RGB15(13,13,13);
	SPRITE_PALETTE[154] = RGB15(30,21,27);
	SPRITE_PALETTE[155] = RGB15(28,25,26);
	SPRITE_PALETTE[156] = RGB15(28,15,15);
	SPRITE_PALETTE[157] = RGB15(9,7,7);
	SPRITE_PALETTE[156] = RGB15(30,21,27);
	SPRITE_PALETTE[157] = RGB15(26,2,1);
	SPRITE_PALETTE[158] = RGB15(15,1,2);
	SPRITE_PALETTE[159] = RGB15(15,1,2);
	SPRITE_PALETTE[160] = RGB15(3,2,3);
	SPRITE_PALETTE[161] = RGB15(24,8,10);
	SPRITE_PALETTE[162] = RGB15(20,3,8);
	SPRITE_PALETTE[163] = RGB15(12,3,5);
	SPRITE_PALETTE[164] = RGB15(16,3,6);
	SPRITE_PALETTE[165] = RGB15(3,3,3);
	SPRITE_PALETTE[166] = RGB15(8,8,8);
	SPRITE_PALETTE[167] = RGB15(9,8,9);
	SPRITE_PALETTE[168] = RGB15(3,3,3);
	SPRITE_PALETTE[169] = RGB15(8,8,8);
	SPRITE_PALETTE[170] = RGB15(9,8,8);
	SPRITE_PALETTE[171] = RGB15(9,8,8);
	SPRITE_PALETTE[172] = RGB15(3,3,3);
	SPRITE_PALETTE[173] = RGB15(26,2,1);
	SPRITE_PALETTE[174] = RGB15(24,8,12);
	SPRITE_PALETTE[175] = RGB15(3,3,3);
	SPRITE_PALETTE[176] = RGB15(3,3,3);
	SPRITE_PALETTE[177] = RGB15(3,3,2);
	SPRITE_PALETTE[178] = RGB15(4,4,4);
	SPRITE_PALETTE[179] = RGB15(3,3,3);
	SPRITE_PALETTE[180] = RGB15(2,1,1);
	SPRITE_PALETTE[181] = RGB15(11,6,6);
	SPRITE_PALETTE[182] = RGB15(6,4,4);
	SPRITE_PALETTE[183] = RGB15(6,4,4);
	SPRITE_PALETTE[184] = RGB15(31,31,31);
	SPRITE_PALETTE[185] = RGB15(28,28,28);
	SPRITE_PALETTE[186] = RGB15(2,2,2);
	SPRITE_PALETTE[187] = RGB15(5,4,4);
	SPRITE_PALETTE[188] = RGB15(9,9,9);
	SPRITE_PALETTE[189] = RGB15(6,4,6);
	SPRITE_PALETTE[190] = RGB15(8,5,7);
	SPRITE_PALETTE[191] = RGB15(6,6,6);
	SPRITE_PALETTE[192] = RGB15(3,2,3);

	// murcielago
	SPRITE_PALETTE[193] = RGB15(3,3,3);
	SPRITE_PALETTE[194] = RGB15(1,1,0);
	SPRITE_PALETTE[195] = RGB15(1,1,1);
	SPRITE_PALETTE[196] = RGB15(17,16,16);
	SPRITE_PALETTE[197] = RGB15(2,2,2);
	SPRITE_PALETTE[198] = RGB15(5,4,6);
	SPRITE_PALETTE[199] = RGB15(12,12,13);
	SPRITE_PALETTE[200] = RGB15(9,8,12);
	SPRITE_PALETTE[201] = RGB15(1,1,1);
	SPRITE_PALETTE[202] = RGB15(6,6,8);
	SPRITE_PALETTE[203] = RGB15(1,1,1);
	SPRITE_PALETTE[204] = RGB15(25,2,2);
	SPRITE_PALETTE[205] = RGB15(1,1,1);
	SPRITE_PALETTE[206] = RGB15(0,0,0);
	SPRITE_PALETTE[207] = RGB15(2,2,2);
	SPRITE_PALETTE[208] = RGB15(0,0,0);
	SPRITE_PALETTE[209] = RGB15(7,6,10);
	SPRITE_PALETTE[210] = RGB15(0,0,0);
	SPRITE_PALETTE[211] = RGB15(0,0,0);
	SPRITE_PALETTE[212] = RGB15(0,0,0);
	SPRITE_PALETTE[213] = RGB15(0,0,0);
	SPRITE_PALETTE[214] = RGB15(0,0,0);
	SPRITE_PALETTE[215] = RGB15(1,1,1);
	SPRITE_PALETTE[216] = RGB15(0,0,0);
	SPRITE_PALETTE[217] = RGB15(0,0,0);
	SPRITE_PALETTE[218] = RGB15(0,0,0);
	SPRITE_PALETTE[219] = RGB15(1,1,1);
	SPRITE_PALETTE[220] = RGB15(0,0,0);

	// bola de fuego
	SPRITE_PALETTE[221] = RGB15(31,31,4);
	SPRITE_PALETTE[222] = RGB15(29,22,6);
	SPRITE_PALETTE[223] = RGB15(26,4,3);
	SPRITE_PALETTE[224] = RGB15(27,14,11);
	SPRITE_PALETTE[225] = RGB15(30,18,6);
	SPRITE_PALETTE[226] = RGB15(30,12,0);
	SPRITE_PALETTE[227] = RGB15(30,20,3);
	SPRITE_PALETTE[228] = RGB15(30,29,2);
	SPRITE_PALETTE[229] = RGB15(26,2,3);
	SPRITE_PALETTE[230] = RGB15(30,14,0);
	SPRITE_PALETTE[231] = RGB15(30,22,4);
	SPRITE_PALETTE[232] = RGB15(31,26,8);
	SPRITE_PALETTE[233] = RGB15(31,25,7);
	SPRITE_PALETTE[234] = RGB15(29,22,2);
	SPRITE_PALETTE[235] = RGB15(29,22,2);
	SPRITE_PALETTE[236] = RGB15(28,7,0);
	SPRITE_PALETTE[237] = RGB15(31,14,0);
	SPRITE_PALETTE[238] = RGB15(27,4,0);
	SPRITE_PALETTE[239] = RGB15(28,11,1);
	SPRITE_PALETTE[240] = RGB15(30,19,3);
	SPRITE_PALETTE[241] = RGB15(30,21,3);
	SPRITE_PALETTE[242] = RGB15(30,10,0);
	SPRITE_PALETTE[243] = RGB15(30,12,2);
	SPRITE_PALETTE[244] = RGB15(31,26,8);
	SPRITE_PALETTE[245] = RGB15(30,18,0);
	SPRITE_PALETTE[246] = RGB15(30,17,1);
	SPRITE_PALETTE[247] = RGB15(28,17,12);
	SPRITE_PALETTE[248] = RGB15(31,18,2);
	SPRITE_PALETTE[249] = RGB15(31,14,0);
	SPRITE_PALETTE[250] = RGB15(27,4,0);
	SPRITE_PALETTE[251] = RGB15(28,11,1);

}

/* 16x16 pixeleko Sprite baten definizioa erronbo bat marrazteko */
/* Memoriako bankuek duten lan egiteko modua dela eta, lehenengo lau lerroak goiko
   ezkerreko koadrantean erakusten dira, hurrengo lauak goiko eskuineko kuadrantean,
   hurrengo lauak beheko ezkerreko koadrantean eta azkeneko lauak beheko eskuineko koadrantean. 
   Alboko irudian ikusten den bezala. */

u8 mago[256] = 
{
	0,0,0,0,0,1,2,3,0,0,0,0,4,5,6,6,
	0,7,8,9,10,11,12,13,14,15,16,3,17,12,11,12,
	3,16,18,16,17,19,11,19,0,20,21,22,17,13,11,23,
	0,0,24,25,3,13,26,26,0,0,27,28,13,29,30,30,31,
	32,0,0,33,34,35,0,36,37,38,0,39,18,40,0,6,11,
	41,0,42,16,43,0,12,23,44,0,45,46,47,0,23,36,48,
	0,49,50,51,0,23,36,52,0,53,54,55,0,30,36,56,0,
	57,54,58,0,29,13,36,59,60,54,61,0,0,62,63,30,23,
	64,29,29,0,65,23,23,64,66,64,64,0,0,67,29,64,66,
	64,64,0,0,68,29,64,66,69,70,0,0,71,29,64,66,72,
	73,0,0,74,29,64,66,72,75,0,0,0,76,64,66,72,77,
	0,0,0,0,3,73,78,79,64,29,13,30,60,54,80,0,64,
	66,11,29,60,54,81,0,64,66,64,11,11,54,82,0,69,83,
	64,29,84,54,85,0,72,75,64,29,60,54,86,0,72,75,64,
	29,60,54,87,0,72,75,64,88,60,54,89,0,3,90,78,91,92,54,93,0,
};

u8 zombi[256] = {
	0,0,0,0,0,0,94,94,0,0,0,0,0,95,96,97,
	0,0,0,0,0,94,98,96,0,0,0,0,0,99,100,96,
	0,0,0,0,0,101,98,98,0,0,0,0,102,103,104,100,
	0,0,0,105,106,107,108,104,0,0,0,109,106,108,107,110,
	94,111,0,0,0,0,0,0,97,112,113,0,0,0,0,0,
	96,114,115,0,0,0,0,0,100,98,116,0,0,0,0,0,
	98,117,118,0,0,0,0,0,100,119,0,0,0,0,0,0,
	104,120,121,0,0,0,0,0,110,108,120,122,0,0,0,0,
	0,0,123,106,108,108,110,110,0,0,124,96,125,126,110,110,
	0,0,0,127,0,128,108,108,0,0,0,0,0,129,126,126,
	0,0,0,0,0,130,131,100,0,0,0,0,0,132,107,100,
	0,0,0,0,0,0,133,100,0,0,0,0,0,0,134,135,
	110,108,120,136,0,0,0,0,110,108,107,137,0,0,0,0,
	108,126,103,138,0,0,0,0,126,126,139,0,0,0,0,0,
	135,140,0,0,0,0,0,0,135,141,0,0,0,0,0,0,
	135,142,0,0,0,0,0,0,100,142,0,0,0,0,0,0,
};

u8 golem[256] = 
{
	0,0,0,0,0,0,0,0,0,0,144,145,146,147,148,149,
	0,150,147,151,147,151,147,147,0,152,151,153,154,153,155,155,
	0,147,153,154,156,154,154,154,157,147,156,156,157,158,154,159,
	160,154,156,161,162,156,156,156,147,156,161,162,163,164,163,164,
	0,0,0,0,0,0,0,0,165,166,167,168,169,0,0,0,
	151,147,147,151,147,170,0,0,153,154,155,153,151,147,171,0,
	154,156,154,155,153,151,172,0,173,174,156,154,155,153,175,176,
	162,161,174,156,154,155,177,178,163,162,161,174,156,154,179,0,
	147,156,161,163,164,163,164,163,147,156,161,164,156,156,156,156,
	147,156,161,162,164,174,174,174,180,156,161,161,162,164,162,162,
	181,147,156,174,162,164,163,163,0,147,156,174,162,163,182,183,
	0,147,156,156,174,147,184,185,186,156,162,174,156,187,184,188,
	164,163,162,161,156,154,147,0,156,156,164,162,156,154,147,189,
	174,162,164,162,156,154,147,0,162,164,162,161,156,154,147,0,
	164,164,162,156,156,154,190,0,163,162,164,156,154,147,0,0,
	147,162,164,156,154,147,191,0,162,163,156,174,156,154,192,0,
};

u8 murcielago[256] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,193,0,0,
	0,194,193,0,195,196,193,197,0,193,196,193,198,199,200,200,
	0,201,202,199,198,200,200,200,0,0,203,202,198,204,200,204,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,193,0,0,0,0,0,0,0,
	196,205,0,206,193,193,207,0,199,198,193,196,196,196,193,0,
	200,198,199,200,200,200,208,0,200,198,200,209,209,210,0,0,
	0,0,0,211,198,200,209,200,0,0,0,0,212,198,209,209,
	0,0,0,0,0,213,198,198,0,0,0,0,0,0,214,215,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	200,198,209,202,216,0,0,0,198,202,202,217,0,0,0,0,
	202,202,218,0,0,0,0,0,219,220,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

u8 bolaFuego[256] = 
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,221,222,223,0,0,0,0,0,0,0,224,
	0,0,0,0,0,225,226,227,0,0,228,229,230,231,232,233,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	223,234,235,0,0,0,0,0,236,237,238,239,0,0,0,0,
	240,240,241,242,243,0,0,0,233,233,233,244,245,0,0,0,
	0,0,0,0,0,246,226,227,0,0,0,0,0,0,0,247,
	0,0,0,0,0,221,222,223,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	240,240,241,242,248,0,0,0,236,249,250,251,0,0,0,0,
	223,234,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
/* Irudikatutako Spriteak memorian kargatzen ditu. SPRITE bat baino gehiago erakusteko
for bana egin behar da.*/

void SpriteakMemorianGorde(){ 
	
int i;
	//16*16ko spriteentzako
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxzombi[i] = zombi[i*2] | (zombi[(i*2)+1]<<8);		
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxmago[i] = mago[i*2] | (mago[(i*2)+1]<<8);
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxgolem[i] = golem[i*2] | (golem[(i*2)+1]<<8);	
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxmurcielago[i] = murcielago[i*2] | (murcielago[(i*2)+1]<<8);	
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxbolaFuego[i] = bolaFuego[i*2] | (bolaFuego[(i*2)+1]<<8);	
	}
};

void erakutsiSpritea(u16* gfx, int indizea, int x, int y, bool eskumarantz)
{
	oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfx,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		eskumarantz, false, // vflip, hflip
		false	// apply mosaic
		); 
		  
	//oamUpdate(&oamMain);  
}

void ezabatuSpritea(int indizea)
{
	oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		0, 0,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		NULL,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	//oamUpdate(&oamMain); 
}

/***********************2024-2025*******************************/

