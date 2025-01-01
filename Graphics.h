
#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

extern int calculategrid(int size);
extern void creategrid(int size, char *letters);
extern void replaceCharacters(char *eile, const char *input);
extern int isWordEntered(char enteredWords[10][20], int count, const char *word);

#endif // GRAPHICS_H_INCLUDED