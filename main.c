#include "pFunctions.c"
#include "pGraphics.h"

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

    int gameover = 0, foundWords = 0,  enteredCount = 0; 
    // Gameover is  gameState, foundWords is the number of found words, entered count is the number of words entered
    char input[10];
    char enteredWords[10][20]; 
    // input is user input string, enteredWords is list to make sure user doesn't repeat the same words and win
    
    // system("cls");
    while(!gameover)
    {
        printf("// ########## GRAPHICS ############ //\n\n");
        printf("Score []\n");
        creategrid(sizeGrid, eile);
        printf("\n[%d/%d] Enter found word: ", foundWords, kiek1);
        
        // Input
        scanf("%s", input);
        if (isWordEntered(enteredWords, enteredCount, input))
        {
            printf("Word already entered. Try a different word.\n");
            continue;
        }
        // Scan the array
        for (int i = 0; i < kiek1; i++)
        {
            if (strcmp(naud[i].zodis, input) == 0)
            {
                strcpy(enteredWords[enteredCount++], input); // Add the word to enteredWords
                replaceCharacters(eile, input);
                foundWords++;
            }
        }



        if(foundWords == kiek1) gameover++;
        system("cls");
    }
    


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



