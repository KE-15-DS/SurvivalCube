#ifndef MATE_H
#define MATE_H

/* ****** mate.h ********
Hemen orotariko funtzio eta datu mota matematikoak definitzen dira; hala nola, 
koordenatuak eta erreferentzi sistemen artean pasatzeko funtzioak.

abs: koordenatu absolutuak: maparen koordenatuak. Zentrua 0,0-n dago eta limiteak {...}-n definituta daude.
rel: jokalarian zentratuta: pantailaren zentrua -- hau da, pantailan jokalariaren posizioa, hau beti erdian egongo baita -- da 0,0 puntua.
pant: pantailaren koordenatuak: pantailaren lehenengo pixela, goiko ezkerreko iskinakoa, da 0,0 puntua, eta ez da onartzen balio negatiborik.

Denak koord_t dira, beraz, kontuz parametroen izenekin, horiek esango baitute zein motatakoak izan behar diren koordenatuak. Batetik bestera 
pasatzeko [a]2[b] motako funtzioak daude erabilgarri.
*/

typedef struct  {
    int x;
    int y;
} koord_t;

// Norabide bektore normalizatua borobilduta. Balio posibleak: -1, 0, 1
// Berez dena 6 bitetan konprimatu ahalko litzateke
typedef struct {
    short x;
    short y;
} int_norabide_t;

float distantzia(koord_t a, koord_t b);
koord_t rel2abs(koord_t rel);
int random_int(int min, int max);
koord_t rel2pant(koord_t rel);
koord_t abs2pant(koord_t abs);
koord_t abs2rel(koord_t abs);
int_norabide_t lortu_norabidea(koord_t rel);
float fast_sqrt(float x);
// Bektorearen modulua.
float modulua(koord_t k);

#endif
