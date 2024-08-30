#include <stdio.h>
#include <stdbool.h>

#define SIZE 3
#define EMPTY ' '
#define PLAYER_X 'X'
#define PLAYER_O 'O'

// To print the boards
void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("\n");
}

// Checking winning state
bool isWinning(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || 
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) || 
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

// To perform DFS and find minimum depth for a win
bool dfs(char board[SIZE][SIZE], int depth, char currentPlayer, int *minDepth, char minDepthBoard[SIZE][SIZE]) {
    if (isWinning(board, PLAYER_X) || isWinning(board, PLAYER_O)) {
        if (depth < *minDepth) {
            *minDepth = depth;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    minDepthBoard[i][j] = board[i][j];
                }
            }
        }
        printBoard(board); 
        return true;
    }

    if (depth == SIZE * SIZE) return false; 

    bool foundSolution = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = currentPlayer;
                if (dfs(board, depth + 1, (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X, minDepth, minDepthBoard)) {
                    foundSolution = true;
                }
                board[i][j] = EMPTY; 
            }
        }
    }
    return foundSolution;
}

int main() {
    char board[SIZE][SIZE] = {{EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}};
    int minDepth = SIZE * SIZE;
    char minDepthBoard[SIZE][SIZE] = {{EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}, {EMPTY, EMPTY, EMPTY}};
    printf("Goal States:\n");
    if (dfs(board, 0, PLAYER_X, &minDepth, minDepthBoard)) {
        printf("Minimum depth to win is: %d\n", minDepth);
        printf("Board state at minimum depth:\n");
        printBoard(minDepthBoard);
    } else {
        printf("No winning state found.\n");
    }
    return 0; 
}
