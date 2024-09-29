#include <iostream>
#include <limits.h>

using namespace std;

#define PLAYER 'X'    // Maximizing player (AI)
#define OPPONENT 'O'  // Minimizing player (Human)

// Function to print the board
void printBoard(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if there are moves left on the board
bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

// Function to evaluate the board state
int evaluate(char board[3][3]) {
    // Check rows for victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == PLAYER)
                return +10;
            else if (board[row][0] == OPPONENT)
                return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == PLAYER)
                return +10;
            else if (board[0][col] == OPPONENT)
                return -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == PLAYER)
            return +10;
        else if (board[0][0] == OPPONENT)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == PLAYER)
            return +10;
        else if (board[0][2] == OPPONENT)
            return -10;
    }

    // No winner: return 0
    return 0;
}

// Alpha-Beta Pruning Algorithm
int alphaBeta(char board[3][3], int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    // If Maximizer or Minimizer has won, return the score
    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth;

    // If no moves are left, it's a draw
    if (!isMovesLeft(board))
        return 0;

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = PLAYER;
                    best = max(best, alphaBeta(board, depth + 1, false, alpha, beta));
                    board[i][j] = '_';
                    alpha = max(alpha, best);
                    if (beta <= alpha)  // Beta cut-off
                        break;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = OPPONENT;
                    best = min(best, alphaBeta(board, depth + 1, true, alpha, beta));
                    board[i][j] = '_';
                    beta = min(beta, best);
                    if (beta <= alpha)  // Alpha cut-off
                        break;
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the AI player
pair<int, int> findBestMoveAlphaBeta(char board[3][3]) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = PLAYER;
                int moveVal = alphaBeta(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = '_';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

int main() {
    char board[3][3] = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    while (isMovesLeft(board)) {
        int row, col;
        printBoard(board);
       
        // Ask the user (opponent) for their move
        cout << "Enter your move (row and column): ";
        cin >> row >> col;

        // Validate the user input
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != '_') {
            cout << "Invalid move. Please try again." << endl;
            continue;
        }

        // Make the opponent's move
        board[row][col] = OPPONENT;

        // Find the best move for the AI player using Alpha-Beta Pruning
        pair<int, int> bestMove = findBestMoveAlphaBeta(board);

        // Make the best move for the AI player
        if (isMovesLeft(board) && bestMove.first != -1 && bestMove.second != -1) {
            board[bestMove.first][bestMove.second] = PLAYER;
            cout << "AI played (" << bestMove.first << ", " << bestMove.second << ")\n";
        }

        // Check if the game has a winner
        int result = evaluate(board);
        if (result == 10) {
            cout << "AI wins!" << endl;
            break;
        } else if (result == -10) {
            cout << "You win!" << endl;
            break;
        } else if (!isMovesLeft(board)) {
            cout << "It's a draw!" << endl;
            break;
        }
    }

    printBoard(board);
    return 0;
}
