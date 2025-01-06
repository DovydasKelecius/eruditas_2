#include "Shuffle.c"
#include "Graphics.c"
#include "Find.c"
#include <ctype.h>

int main()
{
    int zaidimas = 1;

    while (zaidimas)
    {
        if (!mainMenu())
            return 1;

        int difficulty = selectDifficulty();
        int kiek = 0, kiek1 = 0; // kiek - zodziu kiekis faile; kiek1 - naudojamu zodziu kiekis

        FILE *file = fopen("zodziai.txt", "r"); // pointeris i zodziu faila
        if (file == NULL)
        {
            printf("Nepavyksta atidaryti failo.\n");
            exit(1);
        }

        kiek_zodziu(file, &kiek);

        zodis *mas = (zodis *)malloc(kiek * sizeof(zodis)); // priskiriama atmintis strukturai "zodis"
        if (mas == NULL)
        {
            printf("Atmintis tempojant malloc nepriskirta.\n");
            fclose(file);
            exit(1);
        }

        zodziu_nuskaitymas(file, &kiek, mas);
        fclose(file);

        zodis *naud = NULL;

        random_zodziai(&kiek, mas, &kiek1, &naud, difficulty);

        /* laikina
        printf("Pasirinkti zodziai:\n");
        for (int i = 0; i < kiek1; i++)
        {
            printf("%s %d\n", naud[i].zodis, naud[i].ilg);
        }
        */

        char *eile = (char *)malloc((difficulty * difficulty + 1) * sizeof(char));
        if (eile == NULL)
        {
            printf("Nepavyko priskirti atminties simboliu masyvui \"eile\".\n");
            free(mas);
            free(naud);
            exit(1);
        }

        apjungti(&kiek1, naud, eile);
        sumaiso(eile);

        // ########## GRAPHICS ############ //

        int sizeGrid = calculategrid(strlen(eile));
        int multiplierMain = 1;
        float multiplierCustom = 0.0;
        int gameover = 0, foundWords = 0, enteredCount = 0, userScore = 0;
        // Gameover is gameState, foundWords is the number of found words, enteredCount is the number of words entered
        char input[10]; // user input
        char enteredWords[10][100]; // enteredWords is list to make sure user doesn't repeat the same words and win

        system("cls");
        while (!gameover)
        {
            float multiplier = multiplierMain + multiplierCustom;

            printf("\nEntered Words:\n");
            for (int i = 0; i < enteredCount; i++)
            {
                printf("%s ", enteredWords[i]);
            }

            printf("\nScore [%d]\t Multiplier [x%0.2f]\n", userScore, multiplier);

            creategrid(sizeGrid, eile);
            printf("\n[%d/%d] Enter found word: ", foundWords, kiek1);

            scanf("%s", input);

            for (int i = 0; input[i] != '\0'; i++) ///visos raides paverciamos mazosiois
                input[i] = tolower(input[i]);

            if (isWordEntered(enteredWords, enteredCount, input))
            {
                system("cls");
                printf("Word already entered. Try a different word.\n");
                continue;
            }

            checkWord_score(input, naud, kiek1, mas, kiek, enteredWords, &enteredCount, eile,
                            &foundWords, &multiplierMain, &multiplierCustom, &userScore);

            if (foundWords == kiek1)
                gameover = 1;

            system("cls");
        }

        if (gameover)
        {
            displayVictory();
            zaidimas = replay();
        }

        // ########## GRAPHICS END ############ //

        // Unallocating memory
        for (int i = 0; i < kiek; i++)
            free(mas[i].zodis);
        free(mas);
        for (int i = 0; i < kiek1; i++)
            free(naud[i].zodis);
        free(naud);
        free(eile);
        fclose(file);
    }
    return 1;
}
