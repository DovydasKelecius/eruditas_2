#include <stdlib.h>
#include <stdio.h>

#include "pGraphics.h"

int main()
{
    char *placeholder_arr[] = {"a", "b", "c", "d", "p", "d", "k", "a", "p", "a"};
    int size = sizeof(placeholder_arr) / sizeof(placeholder_arr[0]);

    int sizeGrid = calculategrid(placeholder_arr, size);
    printf("size: %d\n", sizeGrid);
    creategrid(sizeGrid, placeholder_arr);

    return 1;
}
