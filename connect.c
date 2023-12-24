#include <stdio.h>

#define ROWS 6
#define COLS 7
char pone[20];
char ptwo[20];
int toktowin;

// Function to initialize the game board
void initializeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the game board
void printBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
    printf("---------------\n");
}

// Function to check if a player has won
int checkWin(char board[ROWS][COLS], char player) {
    int b = toktowin;  // Use the selected number of tokens to win

    // Check for horizontal wins
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - (b - 1); j++) {
            int consecutive = 0;
            for (int k = 0; k < b; k++) {
                if (board[i][j + k] == player) {
                    consecutive++;
                }
                if (consecutive == b) {
                    return 1;
                }
            }
        }
    }

    // Check for vertical wins
    for (int i = 0; i < ROWS - (b - 1); i++) {
        for (int j = 0; j < COLS; j++) {
            int consecutive = 0;
            for (int k = 0; k < b; k++) {
                if (board[i + k][j] == player) {
                    consecutive++;
                }
                if (consecutive == b) {
                    return 1;
                }
            }
        }
    }

    // Check for diagonal wins (top-left to bottom-right)
    for (int i = 0; i < ROWS - (b - 1); i++) {
        for (int j = 0; j < COLS - (b - 1); j++) {
            int consecutive = 0;
            for (int k = 0; k < b; k++) {
                if (board[i + k][j + k] == player) {
                    consecutive++;
                }
                if (consecutive == b) {
                    return 1;
                }
            }
        }
    }

    // Check for diagonal wins (bottom-left to top-right)
    for (int i = b - 1; i < ROWS; i++) {
        for (int j = 0; j < COLS - (b - 1); j++) {
            int consecutive = 0;
            for (int k = 0; k < b; k++) {
                if (board[i - k][j + k] == player) {
                    consecutive++;
                }
                if (consecutive == b) {
                    return 1;
                }
            }
        }
    }

    return 0;  // No win found
}


// Function to play the game
void playGame() {
    char board[ROWS][COLS];
    char currentPlayer = 'R';
    int moves = 0;

    initializeBoard(board);

    while (1) {
        printf("Current board:\n");
        printBoard(board);
        printf("Player %c's turn. Enter column (0-6): ", currentPlayer);

        int column;
        scanf_s("%d", &column);

        if (column < 0 || column >= COLS) {
            printf("Invalid column. Please enter a number between 0 and 6.\n");
            continue;
        }

        for (int i = ROWS - 1; i >= 0; i--) {
            if (board[i][column] == ' ') {
                board[i][column] = currentPlayer;
                break;
            }
            if (i == 0) {
                printf("Column is full. Try another column.\n");
                continue;
            }
        }

        if (checkWin(board, currentPlayer)) {
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        moves++;
        if (moves == ROWS * COLS) {
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'R') ? 'Y' : 'R';
    }
}

int main() {
    printf("Welcome to Connect 4!\n");
    printf("Enter player one name: \n");
    fgets(pone, 20, stdin);
    printf("\n%sis red\n ", pone);
    printf("\nEnter player two name: \n");
    fgets(ptwo, 20, stdin);
    printf("\n%sis yellow\n", ptwo);
    printf("How many tokens to win (3, 4, 5)?\n");
    scanf_s("%d", &toktowin);
    playGame();
    return 0;
}
