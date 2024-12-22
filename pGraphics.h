#include <stdio.h>
#include <math.h>

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
