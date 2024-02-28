#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 25 // defining the board size.

// the winning combination for the game.
const int winning_combos[12][5] = {
    // horixontal, vertical, and diagonal combinations.
    {0,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14},{15,16,17,18,19},{20,21,22,23,24},
    {0,5,10,15,20},{1,6,11,16,21},{2,7,12,17,22},{3,8,13,18,23},{4,9,14,19,24},
    {0,6,12,18,24},{4,8,12,16,20}
};
char board[BOARD_SIZE]; // the game board.

// Function declarations
void initializeBoard();
void displayBoard();
bool addMove(int move, char player);
bool checkWinner(char player);
bool playGame();  // function to play the game.
int getRandomMove(); // function to get a random AI movement.

int main() {
    srand(time(NULL)); // Seed for random number generation.

    bool playAgain;
    do {
        playAgain = playGame(); // check if the player want play agin.
    } while (playAgain);

    printf("Game Over. Thank you for playing!\n");
    return 0;
}

void initializeBoard() {
    //initialize the game board with '-' indicating empty spaces.
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = '-';
    }
}

void displayBoard() {
    // the current state of the board.
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%c ", board[i]);
        if ((i + 1) % 5 == 0) printf("\n");
    }
}

bool addMove(int move, char player) {
    // add move if the position is empty.
    if (board[move] == '-') {
        board[move] = player;
        return true;
    }
    return false;
}

bool checkWinner(char player) {
    // check if the currnt player has won the game.
    for (int i = 0; i < 12; i++) {
        // check each winning combinations.
        if (board[winning_combos[i][0]] == player && board[winning_combos[i][1]] == player &&
            board[winning_combos[i][2]] == player && board[winning_combos[i][3]] == player &&
            board[winning_combos[i][4]] == player) {
            return true;
        }
    }
    return false;
}

bool playGame() {
    initializeBoard(); // initializing the board for the new game.
    char players[2] = {'M', 'A'}; // player M for Mohamed Gabir, and player A for AI
    int turn = 0, move;
    bool moveMade;
     // loop for the runs.
    while (turn < BOARD_SIZE) {
        moveMade = false;
        displayBoard();
        printf("Player %c's turn\n", players[turn % 2]);

        while (!moveMade) {
            // get moves from the player AI.
            if (players[turn % 2] == 'A') {
                move = getRandomMove();
                printf("AI chooses position %d\n", move);
            } else {
                // get move from the player M.
                printf("Enter move index (0-24): ");
                scanf("%d", &move);
                if (move < 0 || move >= BOARD_SIZE) {
                    printf("Invalid move, try again 0-24\n");
                    continue;
                }
            }
            // add move to the board.
            moveMade = addMove(move, players[turn % 2]);
            if (!moveMade) {
                printf("Position already taken, try a different position.\n");
            }
        }
        // check for winner after each move.
        if (checkWinner(players[turn % 2])) {
            displayBoard();
            printf("Player %c is the winner!\n", players[turn % 2]);
            break;
        }

        turn++;
    }

    if (turn == BOARD_SIZE) {
        printf("It's a tie!\n"); // if no wins.
    }
    // ask the player if they want to play again.
    char restart[10];
    printf("Do you want to play again? (yes/no): ");
    scanf("%s", restart);
    return (restart[0] == 'y' || restart[0] == 'Y');
}
// genetate a random move for AI.
int getRandomMove() {
    int move;
    do {
        move = rand() % BOARD_SIZE;
    } while (board[move] != '-');
    return move;
}
