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
            printf("+---");
        printf("+\n");
        for (int j = 0; j < size; j++)
            printf(" | %c", letters[temp++]);
        printf(" |\n");
    }

    printf(" ");
    for (int j = 0; j < size; j++)
        printf("+---");
    printf("+\n");

}

void replaceCharacters(char *eile, const char *input)
{
    int inputLen = strlen(input);
    for (int i = 0; i < inputLen; i++)
    {
        char *pos = strchr(eile, input[i]);
        if (pos != NULL)
            *pos = ' '; // Replace with dot
    }
}

int isWordEntered(char enteredWords[10][100], int count, const char *word)
{
    for (int i = 0; i < count; i++)
        if (strcmp(enteredWords[i], word) == 0)
            return 1; // Word has already been entered

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
    printf("---Welcome to Eruditas 2!---\n\n");
    printf("Wondering how to play?\n");
    printf("You will see a board in front of you.\n");
    printf("The size of the board depends on the difficulty you choose.\n");
    printf("The board has a bunch of scrambled letters on it.\n");
    printf("You have to guess all the different words made out of those letters!\n");
    printf("The words should be 4 to 6 letters long.\n");
    printf("There is a pre-selected list of words you have to guess, \nall the extra words guessed will give you additional points.\n\n\n");
    printf("---\"Multiplier\"---:\n");
    printf("Each correctly found word increases the multiplier by 1,\n");
    printf("extra words by 0.05.\n");
    printf("And each incorrect guess resets the multiplier to 1.\n\n\n");
    printf("---\"Wrong answers\"---\n");
    printf("If you enter three wrong words in a row you will lose the game,\n");
    printf("so try your best to guess only the correct words!\n");
    printf("Good luck!\n");
}
void displayLeaderboard(int *max_score)
{
    system("cls");
    printf("=== Leaderboard ===\n");

    FILE *file = fopen("highscore.txt", "r");
    if (file != NULL)
    {
        fscanf(file, "%d", max_score);
        fclose(file);
    }
    else
        *max_score = 0;

    printf("High score: %d\n", *max_score);
}
void displayVictory()
{
    system("cls");
    printf("\nCongratulations! You've WON!\n");
}

void displayDefeat()
{
    system("cls");
    printf("\nYou've Lost... Want to try again?!\n");
}

int replay()
{
    int pasirinkimas;
    printf("1. Return to menu\n");
    printf("0. Quit.\n");
    scanf("%d", &pasirinkimas);
    if (pasirinkimas == 0)
    {
        printf("Thanks for playing! Goodbye!\n");
        return 0;
    }
    else
        return 1;

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

    switch (difficulty)
    {
    case 1:
        printf("Easy difficulty selected.\n");
        return difficulty = 4;
    case 2:
        printf("Medium difficulty selected.\n");
        return difficulty = 5;
    case 3:
        printf("Hard difficulty selected.\n");
        return difficulty = 6;
    default:
        printf("Invalid choice. Defaulting to Easy.\n");
        return difficulty = 4;
    }

    return 1;
}


int mainMenu(int *max_score)
{
    int choice;
    do
    {
        displayMenu();
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch (choice)
        {
        case 1:
            printf("Starting the game...\n");

            return 1;
        case 2:
            printf("Displaying leaderboard...\n");
            displayLeaderboard(&max_score);

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
    }
    while (choice != 0);

    return 0;
}

