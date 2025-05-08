// 2024-2025 ikasturtea
#ifndef SPRITEAK_H
#define SPRITEAK_H

#include <stdint.h>
#include <stdbool.h>

extern uint16_t* gfx;
extern uint16_t* gfx2;
extern uint16_t* gfx3;
extern uint16_t* gfxSub;

extern void memoriaErreserbatu();

extern void PaletaNagusiaEzarri();
/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu pantaila nagusian. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. */

extern void BigarrenPaletaEzarri();
/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu bigarren pantailan. 0 balioa 
   gardena da eta definitu gabeko balioak beltzak. */

extern void SpriteakMemorianGorde();
/* Irudikatutako Spriteak memorian kargatzen ditu.*/

#define PANT_ERDI_X 128
#define PANT_ERDI_Y 96
#define JOKALARI_SPRITE_INDIZEA 101

extern u16* gfxmago;
extern u16* gfxzombi;
void erakutsiSpritea(u16* gfx, int indizea, int x, int y, bool eskumarantz);
void ezabatuSpritea(int indizea);

#endif