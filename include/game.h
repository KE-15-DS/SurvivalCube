#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdint.h>

#include "mate.h"

typedef enum {
    NORMALA,
    SENDOA,
    AZKARRA,
    BOSS
} etsai_mota_t;

typedef struct {
    koord_t pos;  // ABSOLUTUAK
    uint8_t hp;  // zenbat aldiz jo behar duten hiltzeko
    uint8_t iframes;
    uint8_t abiadura; // zenbat frame itxaron mugitu baino lehen, 0 -> jokalariaren abiadura
    uint16_t puntuak; // hiltzean emango dituen puntu kopurua
    bool eskumarantz;  // norantz begiratzen duen
    bool isBoss;  // hilezina izatea
    u16* gfx;  // spriteari erakuslea
} etsaia_t;

etsaia_t etsaia_hasieratu(koord_t abs, etsai_mota_t mota);
void tick();
void marraztu();
void spawnEnemy(etsai_mota_t mota);
bool pantailan_dago(koord_t rel);
bool talka(koord_t rel);
void ezabatu_etsaia(int indizea);
bool erasoak_jota(koord_t rel);
void marraztu_etsaia(int indizea, etsaia_t *e);

// Aldagai globalak
extern int EGOERA;
extern int LVL;
extern int HP;
extern int IFRAMES;
extern etsaia_t etsai_lista[100];
extern int etsai_lista_len;
extern koord_t jokalari_pos;  //abs
extern bool erasoa_ezkerrean;
extern bool erasoa_eskuman;
extern int eraso_cooldown;  // 0rantz doa, ERASO_FRAMES eta 2*ERASO_FRAMES artean dagoenean dago aktibo erasoa, bestela oraindik ezin da berriz erabili
extern bool eskumara_begira;
extern unsigned int PUNTUAK;
extern bool BOSSA_DAGO;
extern char bizitza_barra[13];
extern int indice_bizitza_barra;

// Konstanteak
#define ERASO_LEN_X 64
#define ERASO_LEN_Y 8
#define ERASO_FRAMES 20

#endif