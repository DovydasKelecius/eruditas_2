#include <stdio.h>
#include <math.h>

int calculategrid(char **arr, int size)
{
    double sizeGrid = ceil(sqrt(size));
    printf("double size: %.3lf\n", sizeGrid);

    return (int)sizeGrid;
}

void creategrid(int size, char **letters)
{
    for (int i = 0; i < (size * size); i++)
    {
        printf("%d. Cancer\n", i);
    }
}
