#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdint.h>

#include "mate.h"


typedef struct {
    // ABSOLUTUAK
    koord_t pos;
    uint8_t hp;
    // zenbat frame mugitu baino lehen
    uint8_t abiadura;
} etsaia_t;

etsaia_t etsaia_hasieratu();
void tick();
void marraztu();
void spawnEnemy();
bool pantailan_dago(koord_t rel);

// Aldagai globalak
extern int EGOERA;
extern int LVL;
extern int HP;
extern etsaia_t etsai_lista[100];
extern int etsai_lista_len;
extern koord_t jokalari_pos;  //abs

#endif