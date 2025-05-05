// 2024-2025 ikasturtea

/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

/* Fondo desberdinak erakutsi nahi izango baditugu, hemen fondo bakoitzaren burukoa (.h fitxategia) gehitu behar da. Buruko horiek
automatikoki sortzen dira, konpilatzerako garaian, baina horretarako gogoratu behar da */

#include "fondoak.h"
#include "grafikoak.h"
#include "game.h"
#include "Menua.h"
#include "Info.h"
#include "Ingame.h"
#include "Gameover.h"

/* Irudiak memorian kopiatzeko DMA kanala aukeratu (3.a) */
static const int DMA_CHANNEL = 3;

void resetFondoak()
{
    // Reset BG2 to default (disable or set to original state)
    REG_BG2CNT = BG_BMP16_128x128 | BG_BMP_BASE(8) | BG_PRIORITY(2);
    REG_BG2PA = 1 << 8; // Reset affine matrix to no scaling
    REG_BG2PD = 1 << 8;
    REG_BG2X = -(SCREEN_WIDTH / 2 - 32) << 8; // Original offset from template
    REG_BG2Y = -32 << 8;

    // Clear VRAM
    dmaFillHalfWords(0, (uint16*)BG_BMP_RAM(8), 128*128*2);
}

/* Pantailaratu nahi den grafiko bakoitzerako horrelako prozedura bat idatzi behar da */

void erakutsiMenua() {
    resetFondoak();
	dmaCopyHalfWords(DMA_CHANNEL,
                     MenuaBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     MenuaBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsiInfo() {
    resetFondoak();
	dmaCopyHalfWords(DMA_CHANNEL,
                     InfoBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     InfoBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsiInGame() {
    int bg2 = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0,0);
    dmaCopyHalfWords(DMA_CHANNEL,
        IngameBitmap,
        bgGetGfxPtr(bg2),
        IngameBitmapLen);

    // Configure BG2 as a 256x256 affine layer with scaling
    //REG_BG2CNT = BG_BMP16_256x256 | BG_BMP_BASE(8) | BG_PRIORITY(2);
    // Scale down by 0.5x to simulate a 512x512 background (0x0080 is 0.5 in 8.8 fixed-point)
    REG_BG2PA = 0x0080;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 0x0080;
    // Initialize scroll position to center the player
    int virtual_scroll_x = jokalari_pos.x - (SCREEN_WIDTH / 2);
    int virtual_scroll_y = jokalari_pos.y - (SCREEN_HEIGHT / 2);
    REG_BG2X = (virtual_scroll_x / 2) << 8;
    REG_BG2Y = (virtual_scroll_y / 2) << 8;
}

void erakutsiGameOver() {
    resetFondoak();
	dmaCopyHalfWords(DMA_CHANNEL,
                     GameoverBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     GameoverBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}
/***********************2024-2025*******************************/

