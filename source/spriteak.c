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
u16* gfxerronboHandia;


/* Pantailan erakutsi nahi den sprite bakoitzeko memoria erreserbatu.*/
void memoriaErreserbatu()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxmago= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxerronboHandia=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
}

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu PANTAILA NAGUSIAN. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. SPRITEARI KOLOREAK ESLEITZEKO ALDATU*/
void PaletaNagusiaEzarri() {
	/*
	SPRITE_PALETTE[1] = RGB15(31,0,0);
	SPRITE_PALETTE[2] = RGB15(31,31,31);
	SPRITE_PALETTE[3] = RGB15(31,31,31);
	SPRITE_PALETTE[4] = RGB15(0,31,0);
	SPRITE_PALETTE[5] = RGB15(0,0,31);
	SPRITE_PALETTE[6] = RGB15(0,0,0);
	SPRITE_PALETTE[7] = RGB15(0,31,31);
	SPRITE_PALETTE[8] = RGB15(31,0,31);
	SPRITE_PALETTE[9] = RGB15(16,16,16);
	SPRITE_PALETTE[10] = RGB15(25,25,25);
	SPRITE_PALETTE[11] = RGB15(8,8,8);
	SPRITE_PALETTE[12] = RGB15(31,19,0);
	SPRITE_PALETTE[13] = RGB15(19,0,4);
	SPRITE_PALETTE[14] = RGB15(25,0,0);
	SPRITE_PALETTE[15] = RGB15(16,0,16);
	SPRITE_PALETTE[16] = RGB15(25,19,31);
	SPRITE_PALETTE[17] = RGB15(31,19,25);
	SPRITE_PALETTE[18] = RGB15(23,21,21);
	SPRITE_PALETTE[19] = RGB15(0,0,16);
	SPRITE_PALETTE[20] = RGB15(0,16,16);
	SPRITE_PALETTE[21] = RGB15(0,12,0);
	SPRITE_PALETTE[22] = RGB15(16,16,0);
	SPRITE_PALETTE[23] = RGB15(19,31,19);
	SPRITE_PALETTE[24] = RGB15(31,31,19);
	*/
	SPRITE_PALETTE[1] = RGB15(31,31,31);
	SPRITE_PALETTE[2] = RGB15(4,4,8);
	SPRITE_PALETTE[3] = RGB15(28,8,8);
	SPRITE_PALETTE[4] = RGB15(28,28,16);
	SPRITE_PALETTE[5] = RGB15(24,24,8);
	SPRITE_PALETTE[6] = RGB15(28,4,0);
	SPRITE_PALETTE[7] = RGB15(12,20,8);
	SPRITE_PALETTE[8] = RGB15(8,8,8);
	SPRITE_PALETTE[9] = RGB15(12,16,8);
	SPRITE_PALETTE[10] = RGB15(24,16,8);
	SPRITE_PALETTE[11] = RGB15(12,4,0);
	SPRITE_PALETTE[12] = RGB15(20,4,8);
	SPRITE_PALETTE[13] = RGB15(20,12,8);
	SPRITE_PALETTE[14] = RGB15(12,8,8);
	SPRITE_PALETTE[15] = RGB15(8,4,8);
	SPRITE_PALETTE[16] = RGB15(12,8,16);
	SPRITE_PALETTE[17] = RGB15(16,4,8);
	SPRITE_PALETTE[18] = RGB15(4,4,5);
	SPRITE_PALETTE[19] = RGB15(24,30,13);
	SPRITE_PALETTE[20] = RGB15(31,31,27);
	SPRITE_PALETTE[21] = RGB15(30,29,21);
	SPRITE_PALETTE[22] = RGB15(13,25,4);
	SPRITE_PALETTE[23] = RGB15(29,26,27);
	SPRITE_PALETTE[24] = RGB15(27,23,16);
	SPRITE_PALETTE[25] = RGB15(22,15,10);
	SPRITE_PALETTE[26] = RGB15(1,18,10);
	SPRITE_PALETTE[27] = RGB15(30,24,22);
	SPRITE_PALETTE[28] = RGB15(4,10,10);
	SPRITE_PALETTE[29] = RGB15(0,13,13);
	SPRITE_PALETTE[30] = RGB15(21,26,27);
	SPRITE_PALETTE[31] = RGB15(18,12,7);
	SPRITE_PALETTE[32] = RGB15(21,26,31);
	SPRITE_PALETTE[33] = RGB15(24,18,21);
	SPRITE_PALETTE[34] = RGB15(10,5,4);
	SPRITE_PALETTE[35] = RGB15(15,20,29);
	SPRITE_PALETTE[36] = RGB15(11,14,26);
	SPRITE_PALETTE[37] = RGB15(10,9,21);
	SPRITE_PALETTE[38] = RGB15(20,11,7);
	SPRITE_PALETTE[39] = RGB15(25,16,9);
	SPRITE_PALETTE[40] = RGB15(30,20,14);
	SPRITE_PALETTE[41] = RGB15(13,13,14);
	SPRITE_PALETTE[42] = RGB15(18,17,17);
	SPRITE_PALETTE[43] = RGB15(22,20,19);
	SPRITE_PALETTE[44] = RGB15(27,25,24);
}

/* 16x16 pixeleko Sprite baten definizioa erronbo bat marrazteko */
/* Memoriako bankuek duten lan egiteko modua dela eta, lehenengo lau lerroak goiko
   ezkerreko koadrantean erakusten dira, hurrengo lauak goiko eskuineko kuadrantean,
   hurrengo lauak beheko ezkerreko koadrantean eta azkeneko lauak beheko eskuineko koadrantean. 
   Alboko irudian ikusten den bezala. */

u8 mago[256] = 
{
	/*
	0	,	0	,	0	,	0	,	0	,	0	,	0	,	5	,	0	,	0	,	19	,	0	,	0	,	0	,	5	,	20	,	 // 	0	0	0	0	0	0	0	5	5	5	0	0	0	0	0	0
	0	,	0	,	0	,	0	,	0	,	5	,	20	,	20	,	0	,	0	,	7	,	0	,	0	,	5	,	12	,	12	,	 // 	0	0	19	0	0	0	5	20	20	20	5	0	0	0	0	0
	0	,	0	,	7	,	7	,	0	,	12	,	9	,	12	,	0	,	0	,	14	,	14	,	0	,	12	,	6	,	12	,	 // 	0	0	0	0	0	5	20	20	20	5	20	5	0	0	0	0
	0	,	0	,	0	,	14	,	0	,	12	,	12	,	12	,	0	,	0	,	14	,	14	,	0	,	9	,	3	,	3	,	 // 	0	0	7	0	0	5	12	12	12	12	5	19	5	0	0	0
	5	,	5	,	0	,	0	,	0	,	0	,	0	,	0	,	20	,	20	,	5	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	7	7	0	12	9	12	9	9	12	5	19	0	0	0
	20	,	5	,	20	,	5	,	0	,	0	,	0	,	0	,	12	,	12	,	5	,	19	,	5	,	0	,	0	,	0	,	 // 	0	0	14	14	0	12	6	12	6	12	9	19	19	0	0	0
	9	,	9	,	12	,	5	,	19	,	0	,	0	,	0	,	6	,	12	,	9	,	19	,	19	,	0	,	0	,	0	,	 // 	0	0	0	14	0	12	12	12	12	3	9	19	19	0	0	0
	12	,	3	,	9	,	19	,	19	,	0	,	0	,	0	,	3	,	9	,	19	,	19	,	0	,	0	,	0	,	0	,	 // 	0	0	14	14	0	9	3	3	3	9	19	19	0	0	0	0
	0	,	0	,	12	,	12	,	5	,	9	,	3	,	3	,	0	,	0	,	12	,	12	,	20	,	19	,	9	,	3	,	 // 	0	0	12	12	5	9	3	3	9	5	19	0	0	0	0	0
	0	,	0	,	14	,	20	,	20	,	5	,	9	,	3	,	0	,	0	,	14	,	20	,	5	,	0	,	5	,	9	,	 // 	0	0	12	12	20	19	9	3	9	20	5	0	0	0	0	0
	0	,	14	,	14	,	5	,	0	,	0	,	5	,	5	,	0	,	14	,	14	,	0	,	0	,	5	,	20	,	20	,	 // 	0	0	14	20	20	5	9	3	9	20	20	5	0	0	0	0
	0	,	14	,	14	,	0	,	0	,	5	,	20	,	20	,	0	,	14	,	14	,	0	,	0	,	5	,	20	,	20	,	 // 	0	0	14	20	5	0	5	9	5	19	20	20	0	0	0	0
	9	,	5	,	19	,	0	,	0	,	0	,	0	,	0	,	9	,	20	,	5	,	0	,	0	,	0	,	0	,	0	,	 // 	0	14	14	5	0	0	5	5	20	5	12	12	0	0	0	0
	9	,	20	,	20	,	5	,	0	,	0	,	0	,	0	,	5	,	19	,	20	,	20	,	0	,	0	,	0	,	0	,	 // 	0	14	14	0	0	5	20	20	20	20	5	0	0	0	0	0
	20	,	5	,	12	,	12	,	0	,	0	,	0	,	0	,	20	,	20	,	5	,	0	,	0	,	0	,	0	,	0	,	 // 	0	14	14	0	0	5	20	20	20	20	5	0	0	0	0	0
	20	,	20	,	5	,	0	,	0	,	0	,	0	,	0	,	20	,	20	,	5	,	0	,	0	,	0	,	0	,	0	,	 // 	0	14	14	0	0	5	20	20	20	20	5	0	0	0	0	0
	*/

	1, 1, 18, 1, 1, 1, 1, 18, 1, 18, 19, 18, 1, 1, 18, 20, 
	1, 18, 22, 18, 1, 18, 23, 21, 1, 18, 26, 18, 1, 18, 27, 25, 
	1, 18, 29, 18, 1, 18, 20, 27, 1, 18, 31, 18, 1, 18, 20, 27, 
	1, 18, 31, 18, 1, 18, 20, 32, 1, 18, 31, 34, 18, 20, 24, 35, 
	18, 18, 1, 1, 1, 1, 1, 1, 21, 21, 18, 1, 1, 1, 1, 1, 
	24, 25, 23, 18, 1, 18, 1, 1, 25, 23, 25, 28, 18, 22, 18, 1, 
	30, 23, 30, 28, 22, 19, 22, 18, 27, 23, 24, 28, 18, 26, 18, 1, 
	33, 33, 24, 18, 1, 18, 1, 1, 32, 32, 35, 24, 18, 1, 1, 1, 
	1, 18, 31, 34, 32, 24, 35, 36, 1, 18, 31, 34, 35, 23, 37, 36, 
	1, 18, 31, 23, 23, 36, 37, 36, 1, 18, 31, 34, 35, 36, 38, 39, 
	1, 18, 31, 34, 35, 36, 41, 42, 1, 18, 31, 34, 35, 36, 41, 42, 
	1, 18, 31, 34, 18, 36, 41, 42, 1, 18, 31, 18, 1, 18, 44, 18, 
	35, 35, 36, 27, 32, 18, 1, 1, 36, 36, 37, 36, 27, 27, 18, 1, 
	36, 36, 37, 36, 35, 18, 1, 1, 40, 39, 37, 36, 35, 18, 1, 1, 
	43, 42, 37, 36, 35, 18, 1, 1, 41, 42, 37, 36, 35, 18, 1, 1, 
	18, 42, 37, 36, 18, 1, 1, 1, 1, 18, 43, 18, 1, 1, 1, 1, 

};

u8 zombi[256] = 
{
	1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 3, 
	1, 1, 1, 1, 1, 1, 2, 6, 1, 1, 1, 1, 1, 1, 2, 7, 
	1, 1, 1, 1, 1, 1, 2, 9, 1, 1, 1, 1, 1, 1, 1, 2, 
	1, 1, 1, 1, 1, 1, 2, 10, 1, 1, 1, 1, 1, 2, 10, 11, 
	2, 2, 2, 1, 1, 1, 1, 1, 4, 4, 5, 2, 1, 1, 1, 1, 
	5, 5, 7, 2, 1, 1, 1, 1, 8, 5, 8, 2, 1, 1, 1, 1, 
	7, 7, 7, 2, 1, 1, 1, 1, 8, 8, 8, 6, 2, 1, 1, 1, 
	8, 8, 11, 12, 13, 2, 1, 1, 14, 14, 12, 11, 13, 2, 1, 1, 
	1, 1, 1, 1, 1, 2, 10, 11, 1, 1, 1, 1, 1, 2, 12, 11, 
	1, 1, 1, 1, 1, 2, 6, 15, 1, 1, 1, 1, 1, 1, 2, 15, 
	1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 
	1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 
	14, 14, 14, 11, 11, 13, 2, 1, 14, 14, 14, 15, 2, 5, 2, 1, 
	11, 11, 11, 2, 1, 2, 1, 1, 15, 15, 15, 2, 1, 1, 1, 1, 
	1, 8, 17, 2, 1, 1, 1, 1, 1, 8, 12, 2, 1, 1, 1, 1, 
	1, 8, 2, 1, 1, 1, 1, 1, 8, 1, 2, 1, 1, 1, 1, 1, 
}

/* Irudikatutako Spriteak memorian kargatzen ditu. SPRITE bat baino gehiago erakusteko
for bana egin behar da.*/

void SpriteakMemorianGorde(){ 
	
int i;
	//16*16ko spriteentzako
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxmago[i] = mago[i*2] | (mago[(i*2)+1]<<8);				
	}
	//32*32ko spriteentzako
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxzombi[i] = zombi[i*2] | (zombi[(i*2)+1]<<8);				
	}
}

/* Funtzio honek erronbo bat irudikatzen du pantailako x,y posizioan. Pantailan ateratzea nahi den erronbo 
   bakoitzari indize desberdin bat esleitu behar zaio, 0 eta 126 balioen arteko indizea izan daiteke */

void erakutsiMagoa(int indizea, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmago,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

void erakutsiMagoaNorantza(int indizea, int x, int y, bool eskumarantz)
{
	oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmago,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		eskumarantz, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Funtzio honek erronbo baten indizea pasata pantailatik ezabatzen du */
void ezabatuMagoa(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmago,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}

void erakutsiZombi(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmago,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain);

}

void ezabatuZombi(int indizea, int x, int y)
{
	oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmago,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
	oamUpdate(&oamMain);  
}

/***********************2024-2025*******************************/

