
#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

extern int calculategrid(int size);
extern void creategrid(int size, char *letters);
extern void replaceCharacters(char *eile, const char *input);
extern int isWordEntered(char enteredWords[10][100], int count, const char *word);

extern void displayMenu();
extern void displayManual();
extern void displayLeaderboard();
extern int selectDifficulty();
extern int mainMenu();

#endif // GRAPHICS_H_INCLUDED