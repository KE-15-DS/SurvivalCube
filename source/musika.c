#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "musika.h"

void hasieratuMusika() 
{
    mmInitDefaultMem((mm_addr)soundbank_bin);
    mmLoad(MOD_PD_CVK);
}

void hasiMusika()
{
    mmStart(MOD_PD_CVK, MM_PLAY_LOOP);
}

void geldituMusika()
{
    mmStop();
}