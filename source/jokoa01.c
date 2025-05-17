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

void menu()
{
	erakutsiMenua(); // fondoa erakutsi
	iprintf("\x1b[22;5HOngi etorri gure jokora");
	EGOERA=MENU;
	geldituMusika();
}

void info()
{
	erakutsiInfo();
	iprintf("\x1b[22;5HHonela jokatzen da: ");
	EGOERA=INFO;
	geldituMusika();
}

void gameOver()
{
	iprintf("\x1b[22;5HGame Over");
	erakutsiGameOver();
	EGOERA=GAMEOVER;
	geldituMusika();
	ezabatuSpritea(JOKALARI_SPRITE_INDIZEA);
	ezabatuSpritea(SU_BOLA_SPRITE_INDIZEA);
	while (etsai_lista_len > 0)
	{
		ezabatu_etsaia(etsai_lista_len - 1);
	}
	hasiMusika(MOD_GAMEOVER);
}

void inGame()
{
	erakutsiInGame();
	erakutsiSpritea(gfxmago, JOKALARI_SPRITE_INDIZEA, PANT_ERDI_X-8, PANT_ERDI_Y-8, false);
	jokalari_pos.x = 250;
	jokalari_pos.y = 250;
	HP = 10;
	consoleDemoInit();
	iprintf("\x1b[20;0HHP: %d", HP);
	strcpy(bizitza_barra,"[##########]");
	iprintf("\x1b[19;0HHP: %s", bizitza_barra);
	indice_bizitza_barra = 10;
	BOSSA_DAGO = false;
	PUNTUAK = 0;
	EGOERA=INGAME;
	hasiMusika(MOD_INGAME);
	//consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
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
	konfiguratuTenporizadorea(56798, (1<<6)+(1<<7)+1);
	etenZerbErrutEzarri();
	TekEtenBaimendu();
	DenbEtenBaimendu();
	IME = 1;
	
	menu();
	
	while (1)  // libnds 2.0: while(1) --> while(pmMainLoop())
	{ 
		/*
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
		*/
		// Hemen hau jarri beharko genukeen:
		// swiWaitForVBlank();
		// CPUa %100era ez erabiltzeko, baina erasoak apurtzen ditu
		// Agian hemen egingo bagenitu tick(), marraztu() etab. funtzionatuko luke
	}
	// Bukaeran etenak galarazi.
	IME = 0;
}

void inGameInkesta()
{
	if (TeklaDetektatu())
	{
		//iprintf("\x1b[3;0HTEKLAK_DAT: %d", TEKLAK_DAT);
		//maparen limiteak
		if (~TEKLAK_DAT & BIT(6) && jokalari_pos.y > SCREEN_HEIGHT/2)  // gora
		{
			jokalari_pos.y--;
		}
		if (~TEKLAK_DAT & BIT(7) && jokalari_pos.y < 512 - SCREEN_HEIGHT/2)  // behera
		{
			jokalari_pos.y++;
		}
		if (~TEKLAK_DAT & BIT(4) && jokalari_pos.x < 512 - SCREEN_WIDTH/2)  // eskubi
		{
			jokalari_pos.x++;
			erakutsiSpritea(gfxmago, JOKALARI_SPRITE_INDIZEA, PANT_ERDI_X-8, PANT_ERDI_Y-8, true);
			eskumara_begira = true;
		}
		if (~TEKLAK_DAT & BIT(5) && jokalari_pos.x > SCREEN_WIDTH/2)  // ezkerra
		{
			jokalari_pos.x--;
			erakutsiSpritea(gfxmago, JOKALARI_SPRITE_INDIZEA, PANT_ERDI_X-8, PANT_ERDI_Y-8, false);
			eskumara_begira = false;
		}
	}
}
