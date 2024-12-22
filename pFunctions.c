#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pStruct.h"

extern void kiek_zodziu(FILE *file, int *kiek);
extern void zodziu_nuskaitymas(FILE *file, int *kiek, zodis *mas);
extern void random_zodziai(int *kiek, zodis *mas, int *kiek1, zodis **naud);
extern void apjungti(int *kiek1, zodis *naud, char *eile);
extern void sumaiso(char *eile);

extern int calculategrid(int size);
extern void creategrid(int size, char *letters);