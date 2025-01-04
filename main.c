#include "Shuffle.c"
#include "Graphics.c"
#include <ctype.h>
#include <stdbool.h>

// Checks if a word can be constructed from the given letters
bool canMakeWordFromLetters(const char *word, const char *letters)
{
    int letterCounts[256] = {0}; // Frequency count for letters in `letters`

    // Count the occurrences of each character in `letters`
    for (int i = 0; letters[i] != '\0'; i++)
    {
        letterCounts[(unsigned char)letters[i]]++;
    }

    // Check if the word can be constructed
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (--letterCounts[(unsigned char)word[i]] < 0)
        {
            return false; // Not enough letters to form the word
        }
    }

    return true;
}


int main()
{
    if(!mainMenu()) return 1;
    int difficulty = selectDifficulty();

    printf("Diff = %d\n\n\n", difficulty);

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
    for (int i = 0; i < kiek1; i++)
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
    printf("---------\n%s\n-------\n", eile);

    // ########## GRAPHICS ############ //
    // ########## GRAPHICS ############ //
    // ########## GRAPHICS ############ //

    // Graphics only work with x^2 arrays, example: 3x3, 5x5, not 3x4
    int sizeGrid = calculategrid(strlen(eile));
    int multiplierMain = 1;
    float multiplierCustom = 0.0;
    int gameover = 0, foundWords = 0,  enteredCount = 0, userScore = 0;
    // Gameover is  gameState, foundWords is the number of found words, entered count is the number of words entered
    char input[10];
    char enteredWords[10][100];
    // input is user input string, enteredWords is list to make sure user doesn't repeat the same words and win



    // system("cls");
    while (!gameover)
    {
        // printf("Difficulty = %d\n\n", difficulty);
        float multiplier = multiplierMain + multiplierCustom;
        ///laikina
        printf("\nEntered Words:\n");
        for (int i = 0; i < enteredCount; i++)
        {
            printf("%s ", enteredWords[i]);
        }

        printf("\nScore [%d]\t Multiplier [x%0.2f]\n", userScore, multiplier);
        
        
        
        creategrid(sizeGrid, eile);
        printf("\n[%d/%d] Enter found word: ", foundWords, kiek1);

        // Input
        scanf("%s", input);

        for (int i = 0; input[i] != '\0'; i++) // Convert all letters to lowercase
            input[i] = tolower(input[i]);

        if (isWordEntered(enteredWords, enteredCount, input))
        {
            printf("Word already entered. Try a different word.\n");
            continue;
        }

        bool wordFound = false;


        // Check if the word exists in `naud.zodis`
        for (int i = 0; i < kiek1; i++)
        {
            if (strcmp(naud[i].zodis, input) == 0)
            {
                strcpy(enteredWords[enteredCount++], input); // Add the word to `enteredWords`
                replaceCharacters(eile, input);             // Replace the used characters in `eile`
                foundWords++;
                wordFound = true;

                multiplierMain += 1;
                userScore += 100 * multiplier;
                break;
            }
        }

        // If the word was not in `naud.zodis`, check if it can be made from `eile`
        if(strlen(input)>=4 && strlen(input)<=6)
        {
            if (!wordFound && canMakeWordFromLetters(input, eile))
            {
                printf("Custom word accepted: %s\n", input);
                strcpy(enteredWords[enteredCount++], input); // Add the word to `enteredWords`

                multiplierCustom += 0.05;
                userScore += 10 * multiplier;
            }
            else if (!wordFound)
            {
                printf("Invalid word. Try again.\n");
                multiplierCustom = 0.0;
            }
        }
        else
            printf("Entered word doesnt follow the rules.\n");



        if (foundWords == kiek1) gameover++;
        system("cls");
    }

    if(gameover) displayVictory();
    getchar(); 
    getchar();

    // ########## GRAPHICS END ############ //

    // Unallocating memory

    for (int i = 0; i < kiek; i++) free(mas[i].zodis);
    free(mas);
    for (int i = 0; i < kiek1; i++)
    {
        free(naud[i].zodis);
    }

    free(naud);
    free(eile);
    fclose(file);
    return 1;
}
