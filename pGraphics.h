#include <stdio.h>
#include <math.h>

int calculategrid(char **arr, int size)
{
    double sizeGrid = ceil(sqrt(size));

    return (int)sizeGrid;
}

void creategrid(int size, char **letters)
{
    int temp = 0;

    for (int i = 0; i < (size); i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("\t%c", *letters[temp++]);
        }
        printf("\n");
        
    }
}
