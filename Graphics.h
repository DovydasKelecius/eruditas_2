#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <string.h>

extern int calculategrid(int size);
extern void creategrid(int size, char *letters);
extern void replaceCharacters(char *eile, const char *input);
extern int isWordEntered(char enteredWords[10][100], int count, const char *word);

extern void displayMenu();
extern void displayManual();
extern void displayLeaderboard();
extern int selectDifficulty();
extern int replay();
extern int mainMenu();

#endif // GRAPHICS_H_INCLUDED
