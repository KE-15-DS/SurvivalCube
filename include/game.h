#ifndef GAME_H
#define GAME_H

#include <math.h>

/*



*/

// maparen goiko ezkerreko iskinatik kontatuta
typedef struct  {
    int x;
    int y;
} koord_t;

typedef struct {
    koord_t pos;
    int hp;
    // bere buruan zentratuta
    koord_t norantza;
    // zenbat frame mugitu baino lehen
    int abiadura;
} etsaia_t;

etsaia_t etsaia_hasieratu();
//double modulua(koord_t k);
int distantzia(koord_t a, koord_t b);
void tick();
void spawnEnemy();
koord_t rel2abs(koord_t rel);
int random(int min, int max);

// Aldagai globalak
extern int EGOERA;
extern int LVL;
extern int HP;
extern etsaia_t etsai_lista[100];
extern int etsai_lista_len;
extern koord_t jokalari_pos;

#endif