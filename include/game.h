#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdint.h>

/*



*/

// maparen goiko ezkerreko iskinatik kontatuta
typedef struct  {
    int x;
    int y;
} koord_t;

typedef struct {
    // erlatiboak
    koord_t pos;
    uint8_t hp;
    // zenbat frame mugitu baino lehen
    uint8_t abiadura;
} etsaia_t;

// Norabide bektore normalizatua borobilduta. Balio posibleak: -1, 0, 1
typedef struct {
    char x;
    char y;
} int_norabide_t;

etsaia_t etsaia_hasieratu();
//double modulua(koord_t k);
int distantzia(koord_t a, koord_t b);
void tick();
void marraztu();
void spawnEnemy();
koord_t rel2abs(koord_t rel);
int random_int(int min, int max);
koord_t rel2pant(koord_t rel);
koord_t abs2pant(koord_t abs);
koord_t abs2rel(koord_t abs);
bool pantailan_dago(koord_t rel);
int_norabide_t lortu_norabidea(koord_t rel);

// Aldagai globalak
extern int EGOERA;
extern int LVL;
extern int HP;
extern etsaia_t etsai_lista[100];
extern int etsai_lista_len;
extern koord_t jokalari_pos;

#endif