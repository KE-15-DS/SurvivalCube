#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "musika.h"

void hasieratuMusika() 
{
    mmInitDefaultMem((mm_addr)soundbank_bin);
    mmLoad(MOD_INGAME);
    mmLoad(MOD_GAMEOVER);
    mmLoadEffect(SFX_HURT);
    mmLoadEffect(SFX_HIT);
}

void hasiMusika(int abestia)
{
    mmStart(abestia, MM_PLAY_LOOP);
}

void geldituMusika()
{
    mmStop();
}

void hurtSfx()
{
    static const mm_sound_effect hurt_sfx = {
        { SFX_HURT } ,			// id
        (int)(1.0f * (1<<10)),	// rate
        0,		// handle
        255,	// volume
        127,		// panning
    };
    
    mmEffectEx(&hurt_sfx);
}

void hitSfx()
{
    static const mm_sound_effect hit_sfx = {
        { SFX_HIT } ,			// id
        (int)(1.0f * (1<<10)),	// rate
        0,		// handle
        255,	// volume
        127,		// panning
    };
    
    mmEffectEx(&hit_sfx);
}