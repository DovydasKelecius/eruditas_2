#ifndef SHUFFLE_H_INCLUDED
#define SHUFFLE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct zodis
{
    char *zodis;
    int ilg; ///simboliu kiekis zodyje
} zodis;

extern void kiek_zodziu(FILE *file, int *kiek);
extern void zodziu_nuskaitymas(FILE *file, int *kiek, zodis *mas);
extern void random_zodziai(int *kiek, zodis *mas, int *kiek1, zodis **naud);
extern void apjungti(int *kiek1, zodis *naud, char *eile);
extern void sumaiso(char *eile);

#endif // SHUFFLE_H_INCLUDED
