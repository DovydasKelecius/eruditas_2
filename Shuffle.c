#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Shuffle.h"

void kiek_zodziu(FILE *file, int *kiek)///suranda kiek faile yra zodziu
{
    char t; ///temporary

    ///iesko pabaigos simbolio, aka. skaiciuoja zodzius
    while ((t=fgetc(file))!=EOF)
        if (t=='\n')
            (*kiek)++;

    ///jei paskutinis zodis nesibaigia "\n" ji vistiek prideda
    fseek(file, -1, SEEK_END); ///rodykle perkelia 1 pozicija pries failo pabaiga; SEEK_END - perkelia rodykle i failo pabaiga
    if (fgetc(file)!='\n')
        (*kiek)++;

    rewind(file); ///failo rodykle perkeliama i failo pradzia
}
void zodziu_nuskaitymas(FILE *file, int *kiek, zodis *mas)
{
    char temp[256]; ///laikinai laiko zodi
    int sk=0;    ///laikinas zodziu skaicius
    while(fgets(temp, sizeof(temp), file)!=NULL && sk<kiek) ///nuskaito zodi kas eilute
    {
        int ilg=strlen(temp); ///suskaiciuoja zodzio ilgi
        if (temp[ilg-1]=='\n') ///panaikina pabaigos simboli
            temp[ilg-1]='\0';

        mas[sk].zodis=(char*)malloc((ilg+1)*sizeof(char)); ///zodziui priskiria atminti
        if (mas[sk].zodis==NULL)
        {
            printf("Nepavyksta priskirti atminties zodziui.\n");
            exit(1);
        }
        strcpy(mas[sk].zodis, temp); ///nukopijuoja zodi i stuktura
        mas[sk].ilg=strlen(temp); ///issaugo zodzio ilgi
        sk++;
    }
}
void random_zodziai(int *kiek, zodis *mas, int *kiek1, zodis **naud)
{
    srand(time(0));
    int max_ilg=0;
    int *temp=(int *)malloc((*kiek)*sizeof(int)); /// Array to track selected words
    if (temp==NULL)
    {
        printf("Nepavyksta priskirti atminties pasirinktiems zodziams.\n");
        exit(1);
    }

    int sk;
    ///atsitiktinai pasirenkami zodziai, kuriu bendras simboliu sk yra 16 (4x4 lentele)
    while(max_ilg!=16)
    {
        sk=0;
        max_ilg=0;
        (*kiek1)=0;
        for (int i=0; i<(*kiek); i++) ///nepanaudoti zodziai - 0; panaudoti - 1
            temp[i]=0;

        while (sk<(*kiek))
        {
            int ind=rand()%(*kiek);
            if(temp[ind]==0)
            {
                temp[ind]=1;
                max_ilg+=mas[ind].ilg;
                (*kiek1)++;
            }

            if(max_ilg>=16)
                break;

            sk++;
        }
    }

    zodis *temp_naud=(zodis*)malloc((*kiek1)*sizeof(zodis));
    if(temp_naud==NULL)
    {
        printf("Nepavyksta priskirti atminties masyvui \"naud\" naudojant realloc.\n");
        free(temp);
        exit(1);
    }
    *naud=temp_naud;

    sk=0;
    for (int i=0; i<(*kiek); i++)///naudojami zodziai perkeliami i naud masyva "naud"
    {
        if(temp[i]==1)
        {
            (*naud)[sk].zodis=(char*)malloc((mas[i].ilg+1)*sizeof(char));
            if((*naud)[sk].zodis==NULL)
            {
                printf("Nepavyksta priskirti atminties zodziui.\n");
                free(temp);
                exit(1);
            }
            strcpy((*naud)[sk].zodis, mas[i].zodis);
            (*naud)[sk].ilg=mas[i].ilg;
            sk++;
        }
    }

    free(temp);
}
void apjungti(int *kiek1, zodis *naud, char *eile) ///apjungia zodzius i viena eilute
{
    strcpy(eile, ""); ///tuscia eile
    for (int i = 0; i < *kiek1; i++)
    {
        strcat(eile, naud[i].zodis);
    }
}
void sumaiso(char *eile) ///Fisher-Yates shuffle algorithm
{
    int n=strlen(eile);
    for(int i=0; i<n; i++)
    {
        int j=rand()%(i + 1);
        char temp=eile[i];
        eile[i]=eile[j];
        eile[j]=temp;
    }
}
