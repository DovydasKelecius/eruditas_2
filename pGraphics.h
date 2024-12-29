#include <stdio.h>
#include <math.h>
#include <string.h>

int calculategrid(int size)
{
    double sizeGrid = ceil(sqrt(size));

    return (int)sizeGrid;
}

void creategrid(int size, char *letters)
{
    int temp = 0;

    for (int i = 0; i < size; i++)
    {
        printf(" ");
        for (int j = 0; j < size; j++)
        {
            printf("+---");
        }
        printf("+\n");
        for (int j = 0; j < size; j++)
        {
            printf(" | %c", letters[temp++]);
        }
        printf(" |\n");
    }

    printf(" ");
    for (int j = 0; j < size; j++)
    {
        printf("+---");
    }
    printf("+\n");
    
}

void replaceCharacters(char *eile, const char *input) {
    int inputLen = strlen(input);
    for (int i = 0; i < inputLen; i++) {
        char *pos = strchr(eile, input[i]);
        if (pos != NULL) {
            *pos = ' '; // Replace with dot
        }
    }
}

int isWordEntered(char enteredWords[][10], int count, const char *word)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(enteredWords[i], word) == 0)
        {
            return 1; // Word has already been entered
        }
    }
    return 0; // Word has not been entered
} 

    