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
}

/* 16x16 pixeleko Sprite baten definizioa erronbo bat marrazteko */
/* Memoriako bankuek duten lan egiteko modua dela eta, lehenengo lau lerroak goiko
   ezkerreko koadrantean erakusten dira, hurrengo lauak goiko eskuineko kuadrantean,
   hurrengo lauak beheko ezkerreko koadrantean eta azkeneko lauak beheko eskuineko koadrantean. 
   Alboko irudian ikusten den bezala. */

u8 mago[256] = 
{
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

};

u8 erronboHandia[1024] = 
{
	0,0,0,0,0,0,2,2,0,0,0,0,0,2,2,2,0,0,0,0,2,2,2,2,0,0,0,2,2,2,2,2,0,0,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	
 
	2,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

	0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,0,0,0,2,2,2,0,0,0,0,0,0,2,2,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,2,2,2,2,0,0,0,0,2,2,2,0,0,0,0,0,2,2,0,0,0,0,0,0,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,	
};

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
		gfxerronboHandia[i] = erronboHandia[i*2] | (erronboHandia[(i*2)+1]<<8);				
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

void ErakutsiErronboHandia(int indizea, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxerronboHandia,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void EzabatuErronboHandia(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxerronboHandia,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}

/***********************2024-2025*******************************/

