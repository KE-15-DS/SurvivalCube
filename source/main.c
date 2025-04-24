// 2024-2025 ikasturtea

/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia
#include <time.h>

// Guk garatutako fitxategiak

#include "grafikoak.h"		
#include "definizioak.h"
#include "spriteak.h"
#include "jokoa01.h"
#include "game.h"
#include "musika.h"

// aldagai globalen hasieraketak
int EGOERA = MENU;
int LVL = 0;
int HP = 100;
etsaia_t etsai_lista[100];  // uste dut horrela hasieratzen dela
int etsai_lista_len = 0;
koord_t jokalari_pos;
int IFRAMES = 0;

int main(void) 
{
	jokalari_pos.x = 250;  // maparen erdia
	jokalari_pos.y = 250;  // TODO maparen limiteak
	srand(time(NULL));
	HasieratuGrafikoakSpriteak();
	hasieratuMusika();

	// Zuen jokoari dei egingo zaio hemendik
	jokoa01();

	return(0); // AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

}

/***********************2024-2025*******************************/

