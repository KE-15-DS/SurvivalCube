// 2024-2025 ikasturtea

/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"
#include "jokoa01.h"
#include "game.h"

// int EGOERA; // Arazo bat badago bota errua Ekaini
int seg3;   // Hiru segundo pasatzen ote diren ikusten joateko

void tekEten ()
{
	// switch-case?
	if (EGOERA == MENU)
	{
		switch (SakatutakoTekla())  // ezin dira 2 aldi berean sakatu
		{
		case START:
			inGame();
			break;
		case SELECT:
			info();
			break;
		}
		
	}
	else if (EGOERA == INFO)
	{
		if (SakatutakoTekla() == B)
		{
			menu();
		}
	}
	else if (EGOERA == INGAME)
	{
		if (SakatutakoTekla() == A)
		{
			if (eraso_cooldown == 0)
			{
				if (eskumara_begira)
				{
					erasoa_eskuman = true;
					erasoa_ezkerrean = false;  // ez dakit false hauek beharrezkoak diren
				}
				else
				{
					erasoa_ezkerrean = true;
					erasoa_eskuman = false;
				}
				eraso_cooldown = 2*ERASO_FRAMES;
			}
		}
	}
	else if (EGOERA == GAMEOVER)
	{
		if (SakatutakoTekla() == START)
		{
			inGame();
		}
		if (SakatutakoTekla() == SELECT)
		{
			menu();
		}
	}
}

void tenpEten()
{
	if (EGOERA == MENU){
		//TODO: beitu honek nola iteun
		ukimenPantailaInkesta();
	}
	static int tik=0;
	if (EGOERA == INGAME)
	{
		// marraztu behar dena marraztu
		// fondoa
		// etsaiak
		// player
		inGameInkesta();
		tick();
		marraztu();
		// debug
		iprintf("\x1b[0;0Hjokalari_pos: (%d,%d)", jokalari_pos.x, jokalari_pos.y);
		iprintf("\x1b[1;0Hetsai_lista_len: %d", etsai_lista_len);
		iprintf("\x1b[2;0HIFRAMES: %d", IFRAMES);
		iprintf("\x1b[3;0Heraso: %d, esk:%d,ezk:%d", eraso_cooldown, erasoa_eskuman, erasoa_ezkerrean);
		iprintf("\x1b[4;0HBOSS: %d", BOSSA_DAGO);
	}
	/*
	if (EGOERA!=ZAI)
	{
		tik++; 
		if (tik==5)
		{
			seg++;
			iprintf("\x1b[13;5HPasa diren segunduak=%d", seg);
			tik=0;
			if (EGOERA == IREKITA)
			{
				seg3++;
				if (seg3==3)
				{
					erakutsiAtea();
					seg3=0;
					EGOERA=ITXITA;
					EzabatuErronboa(1, 5, 5);
					EzabatuErronboHandia(2, 100, 100);
				}
			}
		}
	}*/
}

void VBlankEten()
{
	if (EGOERA==INGAME)
	{
		int virtual_scroll_x = jokalari_pos.x - (SCREEN_WIDTH/2);
		int virtual_scroll_y = jokalari_pos.y - (SCREEN_HEIGHT/2);
		int actual_scroll_x = virtual_scroll_x / 2; // Scale down due to 0.5x scaling
		int actual_scroll_y = virtual_scroll_y / 2;
		// Use full 32-bit calculations
		REG_BG2X = (actual_scroll_x << 8);  // Equivalent to *128 (0.5x scaled 256px background)
		REG_BG2Y = (actual_scroll_y << 8);
	}
	oamUpdate(&oamMain);
}

void etenZerbErrutEzarri()
{
	irqSet(IRQ_KEYS, tekEten);
	irqSet(IRQ_TIMER0, tenpEten);
	irqSet(IRQ_VBLANK, VBlankEten);
}

/***********************2024-2025*******************************/

