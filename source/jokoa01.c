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

int denb; // denbora neurtzen joateko; baloratu ea beharrezkoa den

void erakutsiMenua()
{
	// TODO: menuaren fondoa jarri
	iprintf("\x1b[22;5HOngi etorri gure jokora");
}

void erakutsiInfo()
{
	// TODO: polito jarri
	iprintf("\x1b[22;5HHonela jokatzen da: ");
}

void jokoa01()
{	
	// Aldagai baten definizioa
	int i=9;
	int tekla=0;;
	EGOERA=MENU;  // uste dut ez dela beharrezkoa
	
	/*
	iprintf("\x1b[22;5HHau idazte proba bat da");	// Hau 22 lerroan eta 5 zutabean hasiko da idazten.
													//Aldagai baten idatzi nahi izanez gero, %d komatxoen barruan eta 
													 //komatxoen kanpoan aldagaiaren balioa.
	iprintf("\x1b[23;5HAldagai proba. Balioa=%d", i);*/

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
	konfiguratuTenporizadorea(39322, 0xC2);
	etenZerbErrutEzarri();
	TekEtenBaimendu();
	DenbEtenBaimendu();
	IME = 1;
	
	erakutsiMenua();
	while (1)
	{	
		switch (EGOERA)
		{
		case MENU:
			
			break;
		case INFO:
		
			// TODO: Info fondoa gehitu
			
		 break; 

		case GAMEOVER: break; // TODO: Game Over fondoa gehitu
		}
	}
	// Bukaeran etenak galarazi.
	IME = 0;
}
