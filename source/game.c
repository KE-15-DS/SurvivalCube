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

void marraztu()
{
    // MEGA TODO
    int i;
    for (i=0; i < etsai_lista_len; i++)
    {
        if (pantailan_dago(etsai_lista[i].pos))
        {
            // marraztu etsaia
        }
    }
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

bool pantailan_dago(koord_t rel)
{
    return rel.x < 128 && rel.y < 96 && rel.x > -128 && rel.y > -96;
}

// Jokalarian zentratuta -> absolutuak
koord_t rel2abs(koord_t rel)
{
    koord_t abs;
    abs.x = jokalari_pos.x + rel.x;
    abs.y = jokalari_pos.y + rel.y;
    return abs;
}

koord_t rel2pant(koord_t rel)
{
    static const int erdix = 128;
    static const int erdiy = 96;
    koord_t p;
    p.x = rel.x + erdix;
    p.y = rel.y + erdiy;
    return p;
}

koord_t abs2rel(koord_t abs)
{
    // TODO
    koord_t r;
    return r;
}

koord_t abs2pant(koord_t abs)
{
    return rel2pant(abs2rel(abs));
}

// TODO testear
int random(int min, int max)
{
    return (rand() % (max-min+1)) + min;
}