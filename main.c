#include "pGraphics.h"
#include "pFunctions.c"

int main()
{
    int kiek=0, kiek1=0; /// kiek - zodziu kiekis faile; kiek1 - naudojamu zodziu kiekis

    FILE *file=fopen("zodziai.txt", "r"); ///pointeris i zodziu faila
    if (file==NULL)
    {
        printf("Nepavyksta atidaryti failo.\n");
        exit(1);
    }

    kiek_zodziu(file, &kiek);

    zodis *mas=(zodis*)malloc(kiek*sizeof(zodis)); ///priskiriama atmintis strukturai "zodis"
    if(mas==NULL)
    {
        printf("Atmintis tempojant malloc nepriskirta.\n");
        exit(1);
    }

    zodziu_nuskaitymas(file, &kiek, mas);

    zodis *naud=NULL;

    random_zodziai(&kiek, mas, &kiek1, &naud);

    ///laikina
    printf("Pasirinkti zodziai:\n");
    int i;
    for (i = 0; i < kiek1; i++)
    {
        printf("%s %d\n", naud[i].zodis, naud[i].ilg);
    }

    char *eile=(char*)malloc(17*sizeof(char)); ///17=16(nes 4x4 lentele)+1(pabaigos simbolis)
    if(eile==NULL)
    {
        printf("Nepavyko priskirti atminties simboliu masyvui \"eile\".\n");
        exit(1);
    }

    apjungti(&kiek1, naud, eile);

    sumaiso(eile);
    ///laikina
    printf("************\n");
    printf("Sumaisyta eile: %s\n", eile);
    printf("************\n");

    // ########## GRAPHICS ############ //

    // Graphics only work with x^2 arrays, example: 3x3, 5x5, not 3x4
    int size = strlen(eile);
    int sizeGrid = calculategrid(size);
    creategrid(sizeGrid, eile);

    // ########## GRAPHICS END ############ //

    // Unallocating memory

    //int i;
    for (i=0; i<kiek; i++)
        free(mas[i].zodis);
    free(mas);
    for (i=0; i<kiek1; i++)
    {
        free(naud[i].zodis);
        free(naud[i].ilg);
    }
    free(naud);
    free(eile);
    fclose(file);
    return 1;
}




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

    int i, sk;
    ///atsitiktinai pasirenkami zodziai, kuriu bendras simboliu sk yra 16 (4x4 lentele)
    while(max_ilg!=16)
    {
        sk=0;
        max_ilg=0;
        (*kiek1)=0;
        for (i=0; i<(*kiek); i++) ///nepanaudoti zodziai - 0; panaudoti - 1
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
    for (i=0; i<(*kiek); i++)///naudojami zodziai perkeliami i naud masyva "naud"
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
    int i;
    strcpy(eile, ""); ///tuscia eile
    for (i = 0; i < *kiek1; i++)
    {
        strcat(eile, naud[i].zodis);
    }
}
void sumaiso(char *eile) ///Fisher-Yates shuffle algorithm
{
    int n=strlen(eile);
    int i;
    for(i=0; i<n; i++)
    {
        int j=rand()%(i + 1);
        char temp=eile[i];
        eile[i]=eile[j];
        eile[j]=temp;
    }
}