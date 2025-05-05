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
    if (mugituDelay == 2*3)  // Horrela, abiadura posibleak = 0,1,2
        mugituDelay = 0;

    int i = 0;
    for (;i < etsai_lista_len; i++)
    {
        //koord_t* k = &etsai_lista[i].pos;  // gutxiago idazteko / arraya indexatzea aurrezteko?
        etsaia_t* e = &etsai_lista[i];
        
        if (e->iframes > 0)
            e->iframes--;

        // mugitu etsaiak
        // TODO kontrolatu denbora
        if (mugituDelay % (e->abiadura + 1) == 0)
        {
            int_norabide_t n = lortu_norabidea(abs2rel(e->pos));
            // Mugitu
            e->pos.x += n.x;
            e->pos.y += n.y;
            // Norantza eguneratu
            if (n.x == 1)
                e->eskumarantz = true;
            else if (n.x == -1)
                e->eskumarantz = false;
        }

        if (/*!e->isBoss &&*/ erasoak_jota(abs2rel(e->pos)) && e->iframes == 0)
        {
            e->hp--;
            if (e->hp == 0)
            {
                PUNTUAK += etsai_lista[i].puntuak;
                ezabatu_etsaia(i);
            }
            else 
            {
                e->iframes = eraso_cooldown;  // mototruco
            }
        }
        else if (IFRAMES ==  0 && talka(abs2rel(e->pos)))
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

    iprintf("\x1b[17;0HPuntuazioa: %d                 ", PUNTUAK);

    // TODO: menos random
    if (!BOSSA_DAGO)
    {
        int chance = PUNTUAK / 200 + 20; // TODO tunear
        int enemigos_unlocked = PUNTUAK / 300;
        if (random_int(chance, 100) == 100)
        {
            spawnEnemy(random_int(0,enemigos_unlocked));  // funtzionatzen du ze enum ak intak dira
        }

        if (PUNTUAK > 1000)
        {
            if (random_int(0,20)==0)
            {
                spawnEnemy(BOSS);
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
        //erakutsiMagoa(indizea, pant.x, pant.y);
        erakutsiSpritea(e->gfx, indizea, pant.x, pant.y, e->eskumarantz);
    }
    else
    {
        //ezabatuMagoa(indizea, pant.x, pant.y);
        ezabatuSpritea(e->gfx, indizea);
    }
}

void spawnEnemy(etsai_mota_t mota)
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

        etsaia_t e = etsaia_hasieratu(abs_pos, mota);
        etsai_lista[etsai_lista_len] = e;  // kopia
        etsai_lista_len++;
    }
}

// Etsaiaren atributu guztiak posizioa izan ezik erabakitzen ditu.
etsaia_t etsaia_hasieratu(koord_t abs, etsai_mota_t mota)
{
    //etsaia_t e = {abs, 10, false, false, gfxmago};
    etsaia_t e;
    e.pos = abs;
    e.isBoss = false;
    e.iframes = 0;
    e.eskumarantz = false;
    switch (mota)
    {
    case MAGO:
        e.gfx = gfxmago;
        e.abiadura = 2;
        e.puntuak = 10;
        e.hp = 1;
        break;
    case BOSS:
        e.isBoss = true;
        e.abiadura = 1;
        e.puntuak = -1;  // autocasting -> max int jejejejeje
        e.hp = -1;  // 255 aldiz jotzea lortzen baduzu bakarrik geldituko zara, zuk zeuk sortutako mundu desolatuan harrapatuta
        e.gfx = gfxmago;  // momentuz
        break;
    case SENDOA:
        e.abiadura = 2;
        e.puntuak = 30;
        e.hp = 2;
        e.gfx = gfxmago;  // momentuz
        break;
    case AZKARRA:
        e.abiadura = 0;
        e.puntuak = 50;
        e.hp = 1;
        e.gfx = gfxmago;  // momentuz
        break;
    }
    
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
    // if (etsai_lista[indizea].isBoss) ...
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
