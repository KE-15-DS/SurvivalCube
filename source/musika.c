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
}

void hasiMusika(int abestia)
{
    mmStart(abestia, MM_PLAY_LOOP);
}

void geldituMusika()
{
    mmStop();
}