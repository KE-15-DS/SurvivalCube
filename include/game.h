#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdint.h>

#include "mate.h"
extern char bizitza_barra[12];
extern int indice_bizitza_barra;
typedef struct {
    // ABSOLUTUAK
    koord_t pos;
    //uint8_t hp;
    // zenbat frame mugitu baino lehen
    //uint8_t abiadura;
} etsaia_t;

etsaia_t etsaia_hasieratu();
void tick();
void marraztu();
void spawnEnemy();
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

// Konstanteak
#define ERASO_LEN_X 64
#define ERASO_LEN_Y 8
#define ERASO_FRAMES 20

//ENTRA EKAIN

#endif