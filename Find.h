#ifndef FIND_H_INCLUDED
#define FIND_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Shuffle.h"

bool canMakeWordFromLetters(const char *word, const char *letters);
extern void checkWord_score(char *input, zodis *naud, int kiek1, zodis *mas, int kiek, char enteredWords[][100], int *enteredCount, char *eile,
                            int *foundWords, int *multiplierMain, float *multiplierCustom, int *userScore);
                            void highscore(int *currentScore, int *max_score);
                            void saveHighScoreToFile(int *max_score);

#endif // FIND_H_INCLUDED
