#include <stdlib.h>
#include <nds.h>

#include "game.h"
#include "spriteak.h"

int distantzia(koord_t a, koord_t b)
{
    // TODO: b - a 
    return 0;
}

void tick()
{
    int i = 0;
    for (;i < etsai_lista_len; i++)
    {
        // mugitu etsaiak
        // TODO kontrolatu denbora
        int_norabide_t n = lortu_norabidea(abs2rel(etsai_lista[i].pos));
        etsai_lista[i].pos.x += n.x;
        etsai_lista[i].pos.y += n.y;
    }
    // TODO: menos random
    if (random_int(0,24) == 0)
    {
        spawnEnemy();
    }
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
            // temporal hasta que haya sprite
            koord_t pant = abs2pant(etsai_lista[i].pos);
            pant.x-=8;
            pant.y+=8;
            erakutsiMagoa(i, pant.x, pant.y);
        }
    }
}

void spawnEnemy()
{
    static const int min_dist = 40;
    static const int max_dist = 140;

    if (etsai_lista_len < 100)
    {
        int x = random_int(min_dist, max_dist);
        int y = random_int(min_dist, max_dist);
        etsaia_t e = etsaia_hasieratu();
        e.pos.x = x;
        e.pos.y = y;

        etsai_lista[etsai_lista_len] = e;  // kopia
        etsai_lista_len++;
    }
}

etsaia_t etsaia_hasieratu()
{
    etsaia_t e;
    e.hp = 2;
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

float fast_sqrt(float x)
{
    // Convert float to fixed-point
    s32 fixed_num = floattof32(x);
    // Calculate square root (result is also fixed-point)
    s32 fixed_result = sqrtf32(fixed_num);
    // Convert result back to float
    return f32tofloat(fixed_result);
}

double modulua(koord_t k)
{
    return fast_sqrt(k.x*k.x + k.y*k.y);
}

// rel(0,0)-rantz joateko norabide "optimoa"
int_norabide_t lortu_norabidea(koord_t rel)
{
    int mod = modulua(rel);
    double x = ((double)rel.x)/mod;
    double y = ((double)rel.y)/mod;
    int_norabide_t n; // espero 0,0 rekin hasieratzea.
    if (x > 0.5)
        n.x = 1;
    else if (x < -0.5)
        n.x = -1;
    if (y > 0.5)
        n.y = 1;
    else if (y < -0.5)
        n.y = -1;
    return n;
}

 // TODO: testear que soy demasiado tondo to para esto
koord_t abs2rel(koord_t abs)
{
    koord_t rel;
    rel.x = abs.x - jokalari_pos.x;
    rel.y = abs.y - jokalari_pos.y;
    return rel;
}

koord_t abs2pant(koord_t abs)
{
    return rel2pant(abs2rel(abs));
}

// TODO: testear
int random_int(int min, int max)
{
    return (rand() % (max-min+1)) + min;
}