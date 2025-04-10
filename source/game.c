#include <stdlib.h>
#include <nds/math.h>

#include "game.h"

/* FIXME: sqrt no va
double modulua(koord_t k)
{
    return sqrt(k.x*k.x + k.y*k.y);
}*/

int distantzia(koord_t a, koord_t b)
{
    // TODO: b - a 
    return 0;
}

void tick()
{

}

void spawnEnemy()
{
    static const int min_dist = 40;
    static const int max_dist = 140;

    int x = random(min_dist, max_dist);
    int y = random(min_dist, max_dist);
    etsaia_t e = etsaia_hasieratu();
    e.pos.x = x;
    e.pos.y = y;

    etsai_lista[etsai_lista_len] = e;  // kopia
    etsai_lista_len++;
}

etsaia_t etsaia_hasieratu()
{
    etsaia_t e;
    e.hp = 2;
    e.norantza.x = 0;
    e.norantza.y = 0;
    e.abiadura = 5;
    return e;
}

// Jokalarian zentratuta -> absolutuak
koord_t rel2abs(koord_t rel)
{
    koord_t abs;
    abs.x = jokalari_pos.x + rel.x;
    abs.y = jokalari_pos.y + rel.y;
    return abs;
}

// TODO testear
int random(int min, int max)
{
    return (rand() % (max-min+1)) + min;
}