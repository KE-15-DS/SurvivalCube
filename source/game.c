#include <stdlib.h>
#include <nds.h>
// debug
#include <stdio.h>

#include "game.h"
#include "spriteak.h"


void tick()
{
    int i = 0;
    for (;i < etsai_lista_len; i++)
    {
        // mugitu etsaiak
        // TODO: kontrolatu denbora
        int_norabide_t n = lortu_norabidea(abs2rel(etsai_lista[i].pos));
        bool pd = pantailan_dago(abs2pant(etsai_lista[i].pos));
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
        koord_t pant = abs2pant(etsai_lista[i].pos);
        if (pantailan_dago(pant))
        {
            // marraztu etsaia
            // temporal hasta que haya sprite
            pant.x-=8;  // spritea zentratzeko
            pant.y-=8;
            erakutsiMagoa(i, pant.x, pant.y);
        }
        else
        {
            ezabatuMagoa(i, pant.x, pant.y);
        }
    }
}

void spawnEnemy()
{
    // orain limiteekin! uau!
    static const int min_dist = 40;
    static const int max_dist = 140;
    static const int min_bound = 0;
    static const int max_bound = 500;

    if (etsai_lista_len < 100)
    {
        int x, y;
        koord_t k, abs_pos;
        etsaia_t e = etsaia_hasieratu();

        do {
            x = random_int(min_dist, max_dist);
            y = random_int(min_dist, max_dist);
            if (random_int(0,1))
                x = -x;
            if (random_int(0,1))
                y = -y;
            k.x = x;
            k.y = y;
            abs_pos  = rel2abs(k);
        } while (abs_pos.x < min_bound || abs_pos.y < min_bound || abs_pos.x > max_bound || abs_pos.y > max_bound); // TODO: TESTEATU ONDO (nei ondo itezila esango nuke)

        e.pos = rel2abs(k);
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

bool pantailan_dago(koord_t pant)
{
    // 8ko margina "pop"ik ez egoteko
    return pant.x >= -8 && pant.y >= -8 && pant.x <= 256+8 && pant.y <= 192+8;
}
