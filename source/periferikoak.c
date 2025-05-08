// 2024-2025 ikasturtea

/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "jokoa01.h"


int tekla; // Sakatutako tekla gordetzeko aldagaia; baloratu ea behar den



int TeklaDetektatu() 
{
	// TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
	if ((~TEKLAK_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int SakatutakoTekla() 
{

	// Sakatutako teklaren balioa itzultzen du: A=0;B=1;SELECT=2;START=3;ESKUBI=4;EZKER=5;
	// GORA=6;BEHERA=7;R=8;L=9;
	if (~TEKLAK_DAT & 1) return A;
	else if (~TEKLAK_DAT & 2) return B;
	else if (~TEKLAK_DAT & 4) return SELECT;
	else if (~TEKLAK_DAT & 8) return START;
	else if (~TEKLAK_DAT & 16) return ESKUBI;
	else if (~TEKLAK_DAT & 32) return EZKER;
	else if (~TEKLAK_DAT & 64) return GORA;
	else if (~TEKLAK_DAT & 128) return BEHERA;
	else if (~TEKLAK_DAT & 256) return R;
	else if (~TEKLAK_DAT & 512) return L;
}

// TODO? konfiguratu A, B, etab. pasatzen
void konfiguratuTeklatua(int TEK_konf)
{
	// Teklatuaren konfigurazioa bere S/I erregistroak aldatuz
	// Parametro bezala jasotako balioan 1 egoeran dauden bitak aldatu kontrol-erregistroan
	TEKLAK_KNT = TEK_konf;
}

void konfiguratuTenporizadorea(int Latch, int TENP_konf)
{
	// Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz
	// Parametro bezala jasotako balioan 1 egoeran dauden bitak aldatu kontrol-erregistroan
	DENB0_KNT = TENP_konf;
	DENB0_DAT = Latch;
}

void TekEtenBaimendu()
{
	// Teklatuaren etenak baimendu
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE |= 4096; // 2^12
	IME=1;
}

void TekEtenGalarazi()
{

	// Teklatuaren etenak galarazi
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE &= ~(4096);  // 2^12
	IME=1;
}  

void DenbEtenBaimendu()
{

// Tenporizadore baten etenak baimendu (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE |= 8;
	IME=1;
}

void DenbEtenGalarazi()
{

// Tenporizadore baten etenak galarazi (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE &= ~8;
	IME=1;

}

void ErlojuaMartxanJarri()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT |= 128;
}

void ErlojuaGelditu()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT &= ~128;
}

void ukimenPantailaInkesta(int scene) //scene-k nondik deitu den jakiten laguntzen digu
{
	touchRead(&PANT_DAT);

	// if (PANT_DAT.px != 0 && PANT_DAT.py != 0){ // ez det uste jada hau berko deunik
	// 	iprintf("\x1b[22;0Hstylus ikutzen X: %3d Y: %3d", PANT_DAT.px, PANT_DAT.py);
	// }
			
	if (scene == 0) //main menu TODO: aldatu koordenadak zuen gustora
	{
		if (PANT_DAT.px < 116 && PANT_DAT.px > 51 && 
			PANT_DAT.py < 170 && PANT_DAT.py > 151 )
		{
			inGame();
		}
				
		if (PANT_DAT.px < 216 && PANT_DAT.px > 139 && 
			PANT_DAT.py < 170 && PANT_DAT.py > 151 )
		{
			info();
		}
	}

	if (scene == 1) //game over
	{
		if (PANT_DAT.px < 116 && PANT_DAT.px > 51 && 
			PANT_DAT.py < 120 && PANT_DAT.py > 101 )
		{
			inGame();
		}
				
		if (PANT_DAT.px < 216 && PANT_DAT.px > 139 && 
			PANT_DAT.py < 120 && PANT_DAT.py > 101 )
		{
			menu();
		}
	}
		
}

/***********************2024-2025*******************************/
//2025 fj summer

