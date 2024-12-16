#include <stdlib.h>
#include <stdio.h>

#include "pGraphics.h"

int main()
{
    // Graphics only work with x^2 arrays, example: 3x3, 5x5, not 3x4 (for now, will see)
    char *placeholder_arr[] = {"a", "b", "c", "d", "p", "d", "k", "a", "p"};
    int size = sizeof(placeholder_arr) / sizeof(placeholder_arr[0]);

    int sizeGrid = calculategrid(placeholder_arr, size);
    creategrid(sizeGrid, placeholder_arr);

    return 1;
}
