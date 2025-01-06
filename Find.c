#include "Find.h"

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

void checkWord_score(char *input, zodis *naud, int kiek1, zodis *mas, int kiek, char enteredWords[][100], int *enteredCount, char *eile,
                     int *foundWords, int *multiplierMain, float *multiplierCustom, int *userScore)
{
    bool wordFound = false;

    if (strlen(input) >= 4 && strlen(input) <= 6)
    {
        for (int i = 0; i < kiek1; i++)
        {
            if (strcmp(naud[i].zodis, input) == 0)
            {
                strcpy(enteredWords[(*enteredCount)++], input);
                replaceCharacters(eile, input);
                (*foundWords)++;
                wordFound = true;
                (*multiplierMain) += 1.0;  // Update multiplierMain
                (*userScore) += 100 * (*multiplierMain);  // Use the updated multiplier
                break;
            }
        }

        if (!wordFound && canMakeWordFromLetters(input, eile))
        {
            for (int i = 0; i < kiek; i++)
            {
                if (strcmp(mas[i].zodis, input) == 0)
                {
                    strcpy(enteredWords[(*enteredCount)++], input);
                    (*multiplierCustom) += 0.05;  // Update multiplierCustom
                    (*userScore) += 10 * (*multiplierMain);  // Use the updated multiplier
                    wordFound = true;
                    break;
                }
            }
        }
    }

    if (!wordFound)
    {
        printf("Invalid word.\n");
        (*multiplierCustom) = 0.0;
         (*multiplierMain) = 1.0;
    }
}

void highscore(int *currentScore, int *max_score)
{
    if (*currentScore > *max_score)
    {
        *max_score = *currentScore;
        printf("\nNEW HIGH SCORE: %d\n", *max_score);
        saveHighScoreToFile(max_score);
    }
}
void saveHighScoreToFile(int *max_score)
{
    FILE *file = fopen("highscore.txt", "w"); // Open the file in write mode
    if (file == NULL) {
        printf("Error: Could not open file to save high score.\n");
        return;
    }
    fprintf(file, "%d", *max_score); // Write the high score into the file
    fclose(file);                   // Close the file
}
