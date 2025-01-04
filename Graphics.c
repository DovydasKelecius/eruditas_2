#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Graphics.h"



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

void replaceCharacters(char *eile, const char *input)
{
    int inputLen = strlen(input);
    for (int i = 0; i < inputLen; i++)
    {
        char *pos = strchr(eile, input[i]);
        if (pos != NULL)
        {
            *pos = ' '; // Replace with dot
        }
    }
}

int isWordEntered(char enteredWords[10][100], int count, const char *word)
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

// ################# Menu ###################

void displayMenu() 
{
    system("cls");
    printf("=== Main Menu ===\n");
    printf("1. Start Game\n");
    printf("2. Leaderboard\n");
    printf("3. Game Manual\n");
    printf("\n0. Quit\n");
    printf("=================\n");
}

void displayManual()
{
    system("cls");
    printf("=== Game Manual ===\n");
    printf("TESTINGGGGGG YES"); // Game Manual here
}

void displayLeaderboard()
{
    system("cls");
    printf("=== Leaderboard ===\n");
    printf("TESTINGGGGGG"); 

    // Reading and outputting from text 
}

void displayVictory()
{
    system("cls");
    printf("\nCongratulations! You've WON!");
}

int selectDifficulty()
{
    int difficulty;
    printf("Select Difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("\n\nEnter your choice: ");
    scanf("%d", &difficulty);

    switch (difficulty) {
        case 1:
            printf("Easy difficulty selected.\n");
            return difficulty = 1;
        case 2:
            printf("Medium difficulty selected.\n");
            return difficulty = 2;
        case 3:
            printf("Hard difficulty selected.\n");
            return difficulty = 3;
        default:
            printf("Invalid choice. Defaulting to Easy.\n");
            return difficulty = 1;
    }

    return 1;
}


int mainMenu() 
{
    int choice;
    do {
        displayMenu();
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch (choice) {
            case 1:
                printf("Starting the game...\n");
                
                return 1;
            case 2:
                printf("Displaying leaderboard...\n");
                displayLeaderboard();

                printf("\n\nPress Any Key to Return\n");  
                getchar(); 
                getchar();
                break;
            case 3:
                printf("Opening game manual...\n");
                displayManual();
                printf("\n\nPress Any Key to Return\n");  
                getchar();
                getchar();
                break;
            case 0:
                printf("Quitting the game. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
