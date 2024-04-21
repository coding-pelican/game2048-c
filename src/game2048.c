#include "../include/game2048.h"
#include "../include/dh_random.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    addRandomTile(board);
    addRandomTile(board);
}

void addRandomTile(int board[BOARD_SIZE][BOARD_SIZE]) {
    int emptyTiles = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                emptyTiles++;
            }
        }
    }

    if (emptyTiles == 0) {
        return;
    }

    int tilePosition = (int)genRand() % emptyTiles;
    int tileValue = ((int)genRand() % 2 + 1) * 2; // Generates 2 or 4

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                if (tilePosition == 0) {
                    board[i][j] = tileValue;
                    return;
                }
                tilePosition--;
            }
        }
    }
}

void moveLeft(int board[BOARD_SIZE][BOARD_SIZE]) {
    bool merged[BOARD_SIZE][BOARD_SIZE] = { { false } };

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 1; j < BOARD_SIZE; j++) {
            if (board[i][j] != 0) {
                int k = j;
                while (k > 0 && board[i][k - 1] == 0) {
                    board[i][k - 1] = board[i][k];
                    board[i][k] = 0;
                    k--;
                }

                if (k > 0 && board[i][k - 1] == board[i][k] && !merged[i][k - 1]) {
                    board[i][k - 1] *= 2;
                    board[i][k] = 0;
                    merged[i][k - 1] = true;
                }
            }
        }
    }
}

void rotateBoard90Clockwise(int board[BOARD_SIZE][BOARD_SIZE]) {
    int tempBoard[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            tempBoard[j][BOARD_SIZE - 1 - i] = board[i][j];
        }
    }
    if (memcpy_s(board, sizeof(tempBoard), tempBoard, sizeof(tempBoard)) != 0) {
        assert(false);
    }
}

void flipBoardHorizontally(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE / 2; ++j) {
            int temp = board[i][j];
            board[i][j] = board[i][BOARD_SIZE - 1 - j];
            board[i][BOARD_SIZE - 1 - j] = temp;
        }
    }
}

void moveTiles(int board[BOARD_SIZE][BOARD_SIZE], char direction) {
    switch (direction) {
    case 'w': // Move up
        rotateBoard90Clockwise(board);
        moveLeft(board);
        rotateBoard90Clockwise(board);
        rotateBoard90Clockwise(board);
        rotateBoard90Clockwise(board);
        break;
    case 's': // Move down
        rotateBoard90Clockwise(board);
        rotateBoard90Clockwise(board);
        rotateBoard90Clockwise(board);
        moveLeft(board);
        rotateBoard90Clockwise(board);
        break;
    case 'a': // Move left
        moveLeft(board);
        break;
    case 'd': // Move right
        flipBoardHorizontally(board);
        moveLeft(board);
        flipBoardHorizontally(board);
        break;
    default:
        break;
    }
}

int checkGameOver(int board[BOARD_SIZE][BOARD_SIZE]) {
    // Check if any move is possible (either an empty tile or a possible merge)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0 || (i < BOARD_SIZE - 1 && board[i][j] == board[i + 1][j]) || (j < BOARD_SIZE - 1 && board[i][j] == board[i][j + 1])) {
                return 0; // Game is not over
            }
        }
    }
    return 1; // No moves left, game over
}

void displayBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf(CLEAR_SCREEN);

    for (int i = BOARD_SIZE - 1; i > -1; i--) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                printf(".\t");
            } else {
                printf("%d\t", board[i][j]);
            }
        }
        printf("\n");
    }
}

// Main function (for testing purposes)
int run2048() {
    int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
    char userInput = 0;

    initializeBoard(board);

    while (true) {
        displayBoard(board);

        // Get user input
        printf("Enter move (w/a/s/d): ");
        if (!scanf_s(" %c", &userInput)) {
            assert(false);
        }

        moveTiles(board, userInput); // Move tiles based on input
        addRandomTile(board);        // Add a random tile

        if (checkGameOver(board)) {
            displayBoard(board);
            printf("Game Over!\n");
            break;
        }
    }

    return 0;
}
