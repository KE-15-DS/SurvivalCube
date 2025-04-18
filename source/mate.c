#include <nds.h>

#include "mate.h"
#include "game.h"

float distantzia(koord_t a, koord_t b)
{
    koord_t k = {b.x-a.x, b.y-a.y};
    return modulua(k);
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

float modulua(koord_t k)
{
    return fast_sqrt(k.x*k.x + k.y*k.y);
}

// rel(0,0)-rantz joateko norabide "optimoa"
int_norabide_t lortu_norabidea(koord_t rel)
{
    float mod = modulua(rel);
    float x = rel.x/mod;
    float y = rel.y/mod;
    int_norabide_t n = {0,0};
    if (x > 0.5)  // = distantzia
        n.x = -1;  // orduan hurbildu
    else if (x < -0.5)
        n.x = 1;
    if (y > 0.5)
        n.y = -1;
    else if (y < -0.5)
        n.y = 1;
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