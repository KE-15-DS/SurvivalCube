// 2024-2025 ikasturtea

/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia
// Guk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"
#include "game.h"
#include "spriteak.h"
#include "musika.h"


int denb; // denbora neurtzen joateko; baloratu ea beharrezkoa den

void menu() // !!!!!!! erakutsiMenua deitze zan, baina erakutsiLoremIpsum() izenak fondotarako erreserba ditzagun.
{
	// TODO: benetako menu bat in
	erakutsiMenua(); // fondoa erakutsi
	iprintf("\x1b[22;5HOngi etorri gure jokora");
	EGOERA=MENU;
	geldituMusika();
}

void info() // !!!!!!! erakutsiInfo deitze zan, baina erakutsiLoremIpsum() izenak fondotarako erreserba ditzagun.
{
	// TODO: honentzat fondo guapardo bat in
	erakutsiInfo();
	iprintf("\x1b[22;5HHonela jokatzen da: ");
	EGOERA=INFO;
	geldituMusika();
}

void gameOver()
{
	// TODO: game over en general programau
	iprintf("\x1b[22;5HGame Over");
	EGOERA=GAMEOVER;
	geldituMusika();
}

void inGame()
{
	erakutsiInGame();
	erakutsiMagoa(JOKALARI_SPRITE_INDIZEA, PANT_ERDI_X-8, PANT_ERDI_Y-8);
	HP = 10;
	bizitza_barra[12]="[##########]";
	indice_bizitza_barra = 10;
	iprintf("\x1b[20;0HHP: %d", HP);
	iprintf("\x1b[19;0HHP: %s", bizitza_barra);
	EGOERA=INGAME;
	hasiMusika();
}

void jokoa01()
{	
	int tekla=0;
	EGOERA=MENU;  // uste dut ez dela beharrezkoa

	//******************************2.JARDUERAN************************************************//
	// ORDEN HONETAN ZEREGIN HAUEK EGITEA GOMENDATZEN DA:
	// Teklatua konfiguratu behar da.	
	// Tenporizadorea konfiguratu behar da.
	// Etenen zerbitzu errutinak ezarri behar dira.
	// Teklatuaren etenak baimendu behar dira.
	// Tenporizadorearen etenak baimendu behar dira.
	// Etenak baimendu behar dira.
	//***************************************************************************************//
	//konfiguratuTeklatua(1 + 16384);  // 2^0+2^14
	//konfiguratuTeklatua(KEY_IRQ_ENABLE | KEY_IRQ_OR | KEY_A | KEY_START | KEY_SELECT);
	konfiguratuTeklatua(1 + 2 + (1<<2) + (1<<3) + (1<<14));  // A, START, SELECT
	// TODO: konfiguratu tenporizadorea / VBLANK etenak erabili
	konfiguratuTenporizadorea(56798, (1<<6)+(1<<7)+1);
	etenZerbErrutEzarri();
	TekEtenBaimendu();
	DenbEtenBaimendu();
	IME = 1;
	
	menu();
	
	while (1)  // libnds 2.0: while(1) --> while(pmMainLoop())
	{
		switch (EGOERA)
		{
		case MENU:
			break;
		case INFO:
			break; 
		case GAMEOVER: 
			break; 
		case INGAME:
			// teklatuaren inkesta (geziak)
			
			

			break;
		}
		//iprintf("\x1b[4;0H me cago en su mare");
	}
	// Bukaeran etenak galarazi.
	IME = 0;
}

void inGameInkesta()
{
	if (TeklaDetektatu())  // and denbora bat pasa da, 60px/s abiadura gehiegi da
	{
		//iprintf("\x1b[3;0HTEKLAK_DAT: %d", TEKLAK_DAT);
		// mapari 0-500eko limiteak jarri dizkiot
		// FIXME: etsaiak ere barruan geratzea falta da.
		// TODO: sortu "barrera bisual" bat maparen inguruan, jokalariak mugak ikusteko
		if (~TEKLAK_DAT & BIT(6) && jokalari_pos.y > 0)  // gora
		{
			jokalari_pos.y--;
		}
		if (~TEKLAK_DAT & BIT(7) && jokalari_pos.y < 500)  // behera
		{
			jokalari_pos.y++;
		}
		if (~TEKLAK_DAT & BIT(4) && jokalari_pos.x < 500)  // eskubi
		{
			jokalari_pos.x++;
			erakutsiMagoaNorantza(JOKALARI_SPRITE_INDIZEA, PANT_ERDI_X-8, PANT_ERDI_Y-8, true);
			eskumara_begira = true;
		}
		if (~TEKLAK_DAT & BIT(5) && jokalari_pos.x > 0)  // ezkerra
		{
			jokalari_pos.x--;
			erakutsiMagoaNorantza(JOKALARI_SPRITE_INDIZEA, PANT_ERDI_X-8, PANT_ERDI_Y-8, false);
			eskumara_begira = false;
		}
	}


}

