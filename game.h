#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ANSI color escape codes
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

// prototypes
void playerCards();
void randomCard();
void processCards();
void player1Turn();
void player2Turn();

// main deck
char cards[60][5] = {
    "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "G0", "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9",
    "Y0", "Y1", "Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9", "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9",
    "R+2", "RR", "RS", "W", "D4", "G+2", "GR", "GS", "W", "D4", "Y+2", "YR", "YS", "W", "D4", "B+2", "BR", "BS", "W", "D4"};

// all variables
int size1 = 7, size2 = 7;
char player1Cards[7][5], player2Cards[7][5];
char currentCard[5];
char throwCard[5];
char color[0];
int skip = 0;
int unoCalledPlayer1 = 0, unoCalledPlayer2 = 0;

int main()
{
    printf("\n ---------------------------- CAPSLOCK SHOULD BE ENABLE ------------------\nRules:\n1. Each player will be distributed 7 cards\n\n2. Player 1 will get the first turn.\n\n3. Each player has to throw the card according to either the color or the number of the last card. If you don't have the specific card, you have to type (SKIP)\n\n4. After you enter SKIP, a new card will be drawn and automatically added to your deck\n\n5. When only 1 card will be left for either of the players, you will have to enter UNO just before playing the last card\n\n6. If you don't enter UNO before entering your last card, it won't be allowed to play, and a new card will be added to your deck as a punishment\n\n\n\n---------------- Have Fun ----------------\n\n\n\n");
    srand(time(NULL));
    randomCard();
    playerCards();

    printf("First card from the deck:\n");
    printf("----------------\t%s\t-----------------------\n", currentCard);
    for (int i = 0; i < size1; i++)
    {
        printf("\nCard %d Of Player 1 : %s%s%s", i + 1, ANSI_COLOR_YELLOW, player1Cards[i], ANSI_COLOR_RESET);
    }

    printf("\n-------------------------------------");
    for (int i = 0; i < size2; i++)
    {
        printf("\nCard %d Of Player 2: %s%s%s", i + 1, ANSI_COLOR_RED, player2Cards[i], ANSI_COLOR_RESET);
    }

    processCards();
    return 0;
}

void playerCards()
{
    // cards to player1
    for (int i = 0; i < size1; i++)
    {
        int random;
        do
        {
            random = rand() % 60;
        } while (strcmp(cards[random], " ") == 0);
        strcpy(player1Cards[i], cards[random]);
        strcpy(cards[random], " ");
    }
    // cards to player2
    for (int i = 0; i < size2; i++)
    {
        int random;
        do
        {
            random = rand() % 60;
        } while (strcmp(cards[random], " ") == 0);

        strcpy(player2Cards[i], cards[random]);
        strcpy(cards[random], " ");
    }
}
void randomCard()
{
    int random;
    do
    {
        random = rand() % 40;
    } while (strcmp(cards[random], " ") == 0);
    strcpy(currentCard, cards[random]);
    strcpy(cards[random], " ");
}

void player1Turn()
{
    int found = 0;
    int validthrow = 0;
   
     // Check if UNO needs to be called
    if (size1 == 1 && unoCalledPlayer1 == 0) {
       
        char unoInput[4];
        scanf("%3s", unoInput);
        if (strcmp(unoInput, "UNO") == 0) {
            unoCalledPlayer1 = 1;
        } else {
            printf("You must say UNO before playing your last card. Penalty: Player 2 wins!\n");
            printf("Player 1 failed to say UNO and loses the game.\n");
            // End the game, Player 2 wins
            exit(0);
        }
    }

    if (skip == 1)
    {
        skip = 0;
        return;
    }

    while (validthrow == 0)
    {
        printf("\nPlayer 1: ");
        scanf("%4s", throwCard);
//skip check
        if (strcmp(throwCard, "SKIP") == 0)
        {
            skip = 1;
            printf("\n----------------------------\n");
            printf("Player 1 has skipped his turn.\n");
            printf("\n----------------------------\n");
            printf("\n1 Card is added to player 1's deck\n");
            for (int i = 0; i < 1; i++)
            {
                int random;
                do
                {
                    random = rand() % 60;
                } while (strcmp(cards[random], " ") == 0);

                strcpy(player1Cards[size1], cards[random]);
                
                strcpy(cards[random], " ");
            }
            size1++;
            for (int i = 0; i < size1; i++)
            {
                printf("Card %d of player 1 : %s%s%s\n", i + 1, ANSI_COLOR_YELLOW, player1Cards[i], ANSI_COLOR_RESET);
            }
            return player2Turn();
        }
        
        else
        {
            for (int i = 0; i < size1; i++)
            {
                // Checking that card is in the deck or not----------
                if (strcmp(player1Cards[i], throwCard) == 0)
                {
                    found = 1;
                    // Shift the remaining cards to the left starting from the index i
                    for (int j = i; j < size1 - 1; j++)
                    {
                        strcpy(player1Cards[j], player1Cards[j + 1]);
                    }
                    if (throwCard[0] == currentCard[0] || throwCard[1] == currentCard[1] || throwCard[1] == '+' || strcmp(throwCard, "D4") == 0 || strcmp(throwCard, "W") == 0 || throwCard[1] == 'R' || throwCard[1] == 'S' )
                    {
                        size1--; 
                        // Decrement size to reflect the removal of the card
                    }
                    break;
                }
            }
 // main terminal--------------------
            if (found == 1 && (throwCard[0] == currentCard[0] || throwCard[1] == currentCard[1] || throwCard[1] == '+' || strcmp(throwCard, "D4") == 0 || throwCard[1] == 'R' || throwCard[1] == 'S' || strcmp(throwCard, "W") == 0))
            {
 // REVERSE CHECK-----------------------------------
                if (throwCard[0] == currentCard[0] && (throwCard[1] == 'R' || throwCard[1] == 'S'))
                {  
                printf("Valid card! Player 1 can throw this card.\n");
                printf("Player 1's deck after throwing card:\n");
                for (int i = 0; i < size1; i++)
                {
                    printf("Card %d of player 1 : %s%s%s\n", i + 1, ANSI_COLOR_YELLOW, player1Cards[i], ANSI_COLOR_RESET);
                }
                    printf("\nPlayer one either reversed or skipped the turn.");
                    return player1Turn();
                }
// invalid reverse----------------------------------------------
                if (throwCard[0] != currentCard[0] && (throwCard[1] == 'R' || throwCard[1] == 'S'))
                {
                    printf("Invalid card! Player 1 cannot throw this card. The card should match the color or number.\n Or it should be a special card.\n");
                    printf("Try Again \n");
                    return player1Turn();
                }

  // checking for Draw2------------------------------------------
                if (throwCard[0] == currentCard[0] && throwCard[1] == '+')
                {
                    printf("\n----------------------------\n");
                    printf("Player 2 will draw 2 cards");
                    printf("\n----------------------------\n");
                    for (int i = 0; i < 2; i++)
                    {
                        int random;
                        do
                        {
                            random = rand() % 60;
                        } while (strcmp(cards[random], " ") == 0);

                        strcpy(player2Cards[size2], cards[random]);
                        size2++;
                        strcpy(cards[random], " ");
                    }
// showing player 2's deck with additiona; cards------------------------------
                    printf("\n----------------------------\n");
                    printf("Player 2's deck after drawing 2 cards:\n");
                    printf("\n----------------------------\n");

                    for (int i = 0; i < size2; i++)
                    {
                        printf("Card %d of player 2 : %s%s%s\n", i + 1, ANSI_COLOR_RED, player2Cards[i], ANSI_COLOR_RESET);
                    }
                    currentCard[0] = throwCard[0];

                    printf("-----------------\t %s \t---------------\n", throwCard);
                
                } 
//invalid draw 2-------------------------------------------------
                else if(throwCard[0] != currentCard[0] && throwCard[1] == '+')
                {
                    printf("Invalid card! Player 1 cannot throw this card. The card should match the color or number.\n Or it should be a special card.\n");
                    printf("Try Again \n");
                    return player1Turn();
                }
 // CHECKING FOR D4---------------------------------------------------------------------
                if (strcmp(throwCard, "D4") == 0)
                {
                    printf("\n----------------------------\n");
                    printf("Player 2 will draw 4 cards");
                    printf("\n----------------------------\n");
                    for (int i = 0; i < 4; i++)
                    {
                        int random;
                        do
                        {
                            random = rand() % 60;
                        } while (strcmp(cards[random], " ") == 0);

                        strcpy(player2Cards[size2], cards[random]);
                        size2++;
                        strcpy(cards[random], " ");
                    }

                    printf("\n----------------------------\n");
                    printf("Player 2's deck after drawing 4 cards:\n");
                    printf("\n----------------------------\n");

                    for (int i = 0; i < size2; i++)
                    {
                        printf("Card %d of player 2 : %s%s%s\n", i + 1, ANSI_COLOR_RED, player2Cards[i], ANSI_COLOR_RESET);
                    }
// ask for color input
                    printf("Choose a color (R, G, B, Y): ");
                    while (1)
                    {
                        fflush(stdin);
                        scanf(" %c", &color[0]);
                        if (color[0] == 'R' || color[0] == 'G' || color[0] == 'B' || color[0] == 'Y')
                        {
                            printf("Chosen color:%c", color[0]);
                            currentCard[0] = color[0];
                            break;
                        }
                        else
                        {
                            printf("Invalid color choice. Please choose R, G, B, or Y: ");
                        }
                    }

                    printf("\n-----------------\t %c \t---------------\n", color[0]);

                }
// check for wild card--------------------------------------
                else if (strcmp(throwCard, "W") == 0) {
                printf("Choose a color (R, G, B, Y): ");
                while (1) {
                    fflush(stdin);
                    scanf(" %c", &color[0]);
                    if (color[0] == 'R' || color[0] == 'G' || color[0] == 'B' || color[0] == 'Y') {
                        printf("\nChosen Color : %c", color[0]);
                        currentCard[0] = color[0];
                        break;
                    } else 
                    {
                        printf("Invalid color choice. Please choose R, G, B, or Y: ");
                    }
                }
                }
                else
                {
                    // Update the current card on the table
                    strcpy(currentCard, throwCard);
                    printf("\n-----------------\t %s \t---------------\n", currentCard);
                }

                printf("\nValid card! Player 1 can throw this card.\n");
                printf("Player 1's deck after throwing card:\n");
                for (int i = 0; i < size1; i++)
                {
                    printf("Card %d of player 1 : %s%s%s\n", i + 1, ANSI_COLOR_YELLOW, player1Cards[i], ANSI_COLOR_RESET);
                }

                validthrow = 1;
            }
            else
            {
                printf("Invalid card! Player 1 cannot throw this card. The card should match the color or number.\n Or it should be a special card.\n");
                printf("Try Again \n");
            }
        }
    }
}


void player2Turn()
{
    int found = 0;
    int validthrow1 = 0;
     // Check if UNO needs to be called
    if (size2 == 1 && unoCalledPlayer2 == 0) {
        
        fflush(stdin);
        char unoInput[4];
        scanf("%3s", unoInput);
        if (strcmp(unoInput, "UNO") == 0) {
            unoCalledPlayer2 = 1;
        } else {
            printf("You must say UNO before playing your last card. \nPenalty: Player 1 wins!\n");
            printf("Player 2 failed to say UNO and loses the game.\n");
            // End the game, Player 1 wins
            exit(0);
        }
    }
    if (skip == 1)
    {
        skip = 0;
        return;
    }

    while (validthrow1 == 0)
    {
        printf("\nPlayer 2: ");
        scanf("%4s", throwCard);
//skip check-----------------------
        if (strcmp(throwCard, "SKIP") == 0)
        {
            skip = 1;
            printf("\n----------------------------\n");
            printf("Player 2 has skipped his turn.\n");
            printf("\n----------------------------\n");
            printf("\n1 Card is added to player 2's deck\n");
            for (int i = 0; i < 1; i++)
            {
                int random;
                do
                {
                    random = rand() % 60;
                } while (strcmp(cards[random], " ") == 0);

                strcpy(player2Cards[size2], cards[random]);
                size2++;
                strcpy(cards[random], " ");
            }
            for (int i = 0; i < size2; i++)
            {
                printf("Card %d of player 2 : %s%s%s\n", i + 1, ANSI_COLOR_RED, player2Cards[i], ANSI_COLOR_RESET);
            }
            return player1Turn();

        }
        else
        {
        for (int i = 0; i < size2; i++)
        {
            if (strcmp(player2Cards[i], throwCard) == 0)
            {
                found = 1;
                // Shift the remaining cards to the left starting from the index i
                for (int j = i; j < size2 - 1; j++)
                {
                    strcpy(player2Cards[j], player2Cards[j + 1]);
                }
                if (throwCard[0] == currentCard[0] || throwCard[1] == currentCard[1] || throwCard[1] == '+' || strcmp(throwCard, "D4") == 0||strcmp(throwCard, "W") == 0 || throwCard[1] == 'R' || throwCard[1] == 'S' )
                {
                    size2--; // Decrement size to reflect the removal of the card
                }
                break;
            }
        }
// main terminal--------------------
        if (found == 1 && (throwCard[0] == currentCard[0] || throwCard[1] == currentCard[1] || throwCard[1] == '+' || strcmp(throwCard, "D4") == 0 || throwCard[1] == 'R' || throwCard[1] == 'S' || strcmp(throwCard, "W") == 0))
        {
// REVERSE CHECK-----------------------------------
            if (throwCard[0] == currentCard[0] && (throwCard[1] == 'R' || throwCard[1] == 'S'))
            {
                 printf("Valid card! Player 1 can throw this card.\n");
                 printf("Player 1's deck after throwing card:\n");
                for (int i = 0; i < size2; i++)
                {
                    printf("Card %d of player 2 : %s%s%s\n", i + 1, ANSI_COLOR_RED, player2Cards[i], ANSI_COLOR_RESET);
                }
                     printf("\nPlayer two either reversed or skipped the turn.");
                     return player2Turn();
            }
// invalid reverse----------------------------------------------
            if (throwCard[0] != currentCard[0] && (throwCard[1] == 'R' || throwCard[1] == 'S'))
            {
                printf("Invalid card! Player 2 cannot throw this card. The card should match the color or number.\n Or it should be a special card.\n");
                printf("Try Again \n");
                return player2Turn();
            }

// checking for Draw2-----------------------------------
            if (throwCard[0] == currentCard[0] && throwCard[1] == '+')
            {

                printf("\n----------------------------\n");
                printf("Player1 will draw 2 cards");
                printf("\n----------------------------\n");
                for (int i = 0; i < 2; i++)
                {
                    int random;
                    do
                    {
                        random = rand() % 60;
                    } while (strcmp(cards[random], " ") == 0);

                    strcpy(player1Cards[size1], cards[random]);
                    size1++;
                    strcpy(cards[random], " ");
                }
// showing player 2's deck with additiona; cards------------------------------
                printf("\n----------------------------\n");
                printf("Player 1's deck after drawing 2 cards:\n");
                printf("\n----------------------------\n");

                for (int i = 0; i < size1; i++)
                {
                    printf("Card %d of player 1 : %s%s%s\n", i + 1, ANSI_COLOR_YELLOW, player1Cards[i], ANSI_COLOR_RESET);
                }
                currentCard[0] = throwCard[0];

                printf("-----------------\t %s \t---------------\n", throwCard);
            }
 //invalid draw 2-------------------------------------------------           
             else if(throwCard[0] != currentCard[0] && throwCard[1] == '+')
            {
                printf("Invalid card! Player 2 cannot throw this card. The card should match the color or number.\n Or it should be a special card.\n");
                    printf("Try Again \n");
                    return player2Turn();
            }
// CHECKING FOR D4------------------------------
            if (strcmp(throwCard, "D4") == 0)
            {
                printf("\n----------------------------\n");
                printf("Player1 will draw 4 cards");
                printf("\n----------------------------\n");
                for (int i = 0; i < 4; i++)
                {
                    int random;
                    do
                    {
                        random = rand() % 60;
                    } while (strcmp(cards[random], " ") == 0);

                    strcpy(player1Cards[size1], cards[random]);
                    size1++;
                    strcpy(cards[random], " ");
                }

                printf("--------------------------------\n");
                printf("Player 1's deck after drawing 4 cards:\n");
                printf("--------------------------------\n");

                for (int i = 0; i < size1; i++)
                {
                    printf("Card %d of player 1 : %s%s%s\n", i + 1, ANSI_COLOR_YELLOW, player1Cards[i], ANSI_COLOR_RESET);
                }
//ask for input COLOR------------------------
                printf("Choose a color (R, G, B, Y): ");
                while (1)
                {
                    fflush(stdin);
                    scanf(" %c", &color[0]);
                    if (color[0] == 'R' || color[0] == 'G' || color[0] == 'B' || color[0] == 'Y')
                    {
                        printf("Chosen color: %c", color[0]);
                        currentCard[0] = color[0];
                        break;
                    }
                    else
                    {
                        printf("Invalid color choice. Please choose R, G, B, or Y: ");
                    }
                }

                printf("\n-----------------\t %c \t---------------\n", color[0]);
            } 
// check for wild card
            else if (strcmp(throwCard, "W") == 0) {
                printf("Choose a color (R, G, B, Y): ");
                while (1) 
                {
                    fflush(stdin);
                    scanf(" %c", &color[0]);
                    if (color[0] == 'R' || color[0] == 'G' || color[0] == 'B' || color[0] == 'Y') {
                        printf("Chosen Color : %c", color[0]);
                        currentCard[0] = color[0];
                        break;
                    } else {
                        printf("Invalid color choice. Please choose R, G, B, or Y: ");
                    }
                }
            }
            else
            {
                // Update the current card on the table
                strcpy(currentCard, throwCard);
                printf("-----------------\t %s \t---------------\n", currentCard);
            }

            printf("Valid card! Player 2 can throw this card.\n");
            printf("Player 2's deck after throwing card:\n");
            for (int i = 0; i < size2; i++)
            {
                printf("Card %d of player 2 : %s%s%s\n", i + 1, ANSI_COLOR_RED, player2Cards[i], ANSI_COLOR_RESET);
            }

            validthrow1 = 1;
        }
        else
        {
            printf("Invalid card! Player 2 cannot throw this card. The card should match the color or number.\n");
            printf("Try Again\n");
        }
    }}
}

void processCards()
{
    int currentplayer = 1;
    while (1)
    {
        if (currentplayer == 1)
        {
            player1Turn();
            if (size1 == 0)
            {
                printf("Player 1 Wins");
                break;
            }
        }
        else
        {
            player2Turn();
            if (size2 == 0)
            {
                printf("Player 2 Wins");
                break;
            }
        }
        if (currentplayer == 1) {
            currentplayer = 2;
        } else {
            currentplayer = 1;
        }
        
    }
}