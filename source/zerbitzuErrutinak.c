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
			// TODO: jolasteko gida pantailaratu
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
}

void tenpEten()
{
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

void etenZerbErrutEzarri()
{
	irqSet(IRQ_KEYS, tekEten);
	irqSet(IRQ_TIMER0, tenpEten);
}

/***********************2024-2025*******************************/

