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
#include "Atea.h" // hau ezabatu
#include "AteaIrekita.h" // hau ezabatu
#include "Menua.h"
#include "Info.h"

/* Irudiak memorian kopiatzeko DMA kanala aukeratu (3.a) */
static const int DMA_CHANNEL = 3;

/* Pantailaratu nahi den grafiko bakoitzerako horrelako prozedura bat idatzi behar da */

// vvvvvvvvvvvvvv hau dana ezabatu vvvvvvvvvvvvvvvv
/* ok
void erakutsiAtea() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     AteaBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     AteaBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsiAteaIrekita() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     AteaIrekitaBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     AteaIrekitaBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}
// ^^^^^^^^^^^^^^ hau dana ezabatu ^^^^^^^^^^^^^^^
*/

// top 5 pruebas mas experimentales que ni tri-line se podria esperar
void erakutsiMenua() {

	dmaCopyHalfWords(DMA_CHANNEL,
                     MenuaBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     MenuaBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}

void erakutsiInfo() {

	dmaCopyHalfWords(DMA_CHANNEL,
                     InfoBitmap, // Automatikoki sortzen den aldagaia
                     (uint16 *)BG_BMP_RAM(0), // Fondo nagusiaren helbidea
                     InfoBitmapLen); // Luzera (bytetan); automatikoki sortzen den aldagaia
}
/***********************2024-2025*******************************/

