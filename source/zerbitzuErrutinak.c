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
			EGOERA = INGAME;
			// TODO: gauzak egin: hasieraketak, bla bla
			erakutsiMagoa(101, 128-8, 96-8);
			break;
		case SELECT:
			EGOERA = INFO;
			// TODO: jolasteko gida pantailaratu
			info();
			break;
		}
	}
	else if (EGOERA == INFO)
	{
		if (SakatutakoTekla() == B)
		{
			EGOERA = MENU;
			menu();
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

