#include <stdlib.h>
#include <nds.h>
#include <stdio.h>

#include "game.h"
#include "spriteak.h"
#include "jokoa01.h"
#include "periferikoak.h"


void tick()
{
    if (IFRAMES > 0)
        IFRAMES--;

    if (eraso_cooldown > 0)
    {
        eraso_cooldown--;
        
        if (eraso_cooldown < ERASO_FRAMES)
        {
            erasoa_eskuman = false;
            erasoa_ezkerrean = false;
        }
    }

    static int mugituDelay = 0;
    if (mugituDelay == 2)
        mugituDelay = 0;

    int i = 0;
    for (;i < etsai_lista_len; i++)
    {
        koord_t* k = &etsai_lista[i].pos;  // gutxiago idazteko / arraya indexatzea aurrezteko?
        // mugitu etsaiak
        // TODO kontrolatu denbora
        if (mugituDelay == 0)
        {
            int_norabide_t n = lortu_norabidea(abs2rel(*k));
            k->x += n.x;
            k->y += n.y;
        }

        if (!etsai_list[i].isBoss && erasoak_jota(abs2rel(*k)))
        {
            PUNTUAK += etsai_lista[i].puntuak;
            ezabatu_etsaia(i);
        }
        else
        {
            if (IFRAMES ==  0 && talka(abs2rel(*k)))
            {
                HP--;
                bizitza_barra[indice_bizitza_barra] = ' ';
                indice_bizitza_barra --;
                iprintf("\x1b[20;0HHP: %d        ", HP);
                iprintf("\x1b[19;0HHP: %s        ", bizitza_barra);

                if (HP <= 0)
                {
                    gameOver();
                }

                IFRAMES = 20;  // adibidez
            }
        }
    }

    iprintf("\x1b[17;0HPuntuazioa: %d                 ", PUNTUAK);

    // TODO: menos random
    if (!BOSSA_DAGO)
    {
        if (random_int(0,100 - PUNTUAK/30) == 0)
        {
            spawnEnemy();
        }

        if (PUNTUAK > 200)
        {
            if (random_int(0,20)==0)
            {
                spawnEnemy();
                etsai_lista[etsai_lista_len-1].isBoss = true;
                BOSSA_DAGO = true;
            }
        }
    }

    mugituDelay++;
}

void marraztu()
{
    // MEGA TODO
    int i;
    for (i=0; i < etsai_lista_len; i++)
    {
        marraztu_etsaia(i, &etsai_lista[i]);
    }
}

// Marraztu edo pantailatik ezabatzen du behar den heinean
void marraztu_etsaia(int indizea, etsaia_t *e)
{
    koord_t pant = abs2pant(e->pos);
    if (pantailan_dago(pant))
    {
        // marraztu etsaia
        // temporal hasta que haya sprite
        pant.x-=8;  // spritea zentratzeko
        pant.y-=8;
        erakutsiMagoa(indizea, pant.x, pant.y);
    }
    else
    {
        ezabatuMagoa(indizea, pant.x, pant.y);
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

        etsaia_t e = etsaia_hasieratu(abs_pos);
        etsai_lista[etsai_lista_len] = e;  // kopia
        etsai_lista_len++;
    }
}

// Etsaiaren atributu guztiak posizioa izan ezik erabakitzen ditu.
etsaia_t etsaia_hasieratu(koord_t abs)
{
    etsaia_t e = {abs, 10, false, false};
    return e;
}

bool pantailan_dago(koord_t pant)
{
    // 8ko margina "pop"ik ez egoteko
    return pant.x >= -8 && pant.y >= -8 && pant.x <= 256+8 && pant.y <= 192+8;
}

// rel-en dagoen etsaiak jokalariarekin talka egin al duen itzultzen du
// TODO agian hobetu
bool talka(koord_t rel)
{
    return (rel.x <= 5 && rel.x >= -5) && (rel.y <= 5 && rel.y >= -5);
}
void ezabatu_etsaia(int indizea)
{
    etsai_lista_len--;
    etsai_lista[indizea] = etsai_lista[etsai_lista_len];
    marraztu_etsaia(indizea, &etsai_lista[indizea]);
    koord_t pant = abs2pant(etsai_lista[etsai_lista_len].pos);
    ezabatuMagoa(etsai_lista_len, pant.x-8, pant.y-8);
}

bool erasoak_jota(koord_t rel)
{
    if ((erasoa_eskuman || erasoa_ezkerrean) && rel.y >= -ERASO_LEN_Y && rel.y <= ERASO_LEN_Y)
    {
        if (erasoa_eskuman)
        {
            return rel.x > 0 && rel.x <= ERASO_LEN_X;
        }
        else //if (erasoa_ezkerrean)
        {
            return rel.x < 0 && rel.x >= -ERASO_LEN_X;
        }
    }
    return false;
}
