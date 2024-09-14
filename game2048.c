/**
 * @file game2048.c
 * @author Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 *
 * @brief Implements a set of functions for playing the 2048 game.
 * @details This file implements a set of functions for playing the 2048 game.
 *
 * @version 0.1
 * @date 2024-02-02
 *
 * @copyright Released under the MIT License. See LICENSE file for details.
 */


#include "game2048.h"
#include "random.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void Board_init(int board[Board_kSize][Board_kSize]) {
    for (int i = 0; i < Board_kSize; ++i) {
        for (int j = 0; j < Board_kSize; ++j) {
            board[i][j] = 0;
        }
    }
    Board_addRandomTile(board);
    Board_addRandomTile(board);
}

void Board_addRandomTile(int board[Board_kSize][Board_kSize]) {
    int tiles_empty_count = 0;
    for (int i = 0; i < Board_kSize; ++i) {
        for (int j = 0; j < Board_kSize; ++j) {
            if (board[i][j] != 0) { continue; }

            tiles_empty_count++;
        }
    }

    if (tiles_empty_count == 0) { return; }

    int tile_position = (int)random_generate() % tiles_empty_count;
    int tile_value    = ((int)random_generate() % 2 + 1) * 2; // Generates 2 or 4

    for (int i = 0; i < Board_kSize; ++i) {
        for (int j = 0; j < Board_kSize; ++j) {
            if (board[i][j] != 0) { continue; }

            if (tile_position == 0) {
                board[i][j] = tile_value;
                return;
            }
            tile_position--;
        }
    }
}

void Board_moveLeft(int board[Board_kSize][Board_kSize]) {
    bool merged[Board_kSize][Board_kSize] = { { false } };

    for (int i = 0; i < Board_kSize; ++i) {
        for (int j = 1; j < Board_kSize; ++j) {
            if (board[i][j] == 0) { continue; }

            int k = j;
            while (0 < k && board[i][k - 1] == 0) {
                board[i][k - 1] = board[i][k];
                board[i][k]     = 0;
                k--;
            }

            if (0 < k && board[i][k - 1] == board[i][k] && !merged[i][k - 1]) {
                board[i][k - 1] *= 2;
                board[i][k]      = 0;
                merged[i][k - 1] = true;
            }
        }
    }
}

void Board_rotate90Clockwise(int board[Board_kSize][Board_kSize]) {
    int temp[Board_kSize][Board_kSize] = { 0 };

    for (int i = 0; i < Board_kSize; ++i) {
        for (int j = 0; j < Board_kSize; ++j) {
            temp[j][Board_kSize - 1 - i] = board[i][j];
        }
    }

    if (memcpy_s(board, sizeof(temp), temp, sizeof(temp)) != 0) {
        assert(false);
    }
}

void Board_flipHorizontally(int board[Board_kSize][Board_kSize]) {
    for (int i = 0; i < Board_kSize; ++i) {
        for (int j = 0; j < Board_kSize / 2; ++j) {
            int temp                      = board[i][j];
            board[i][j]                   = board[i][Board_kSize - 1 - j];
            board[i][Board_kSize - 1 - j] = temp;
        }
    }
}

void Board_moveTiles(int board[Board_kSize][Board_kSize], char direction) {
    switch (direction) {
    case 'w': // Move up
        Board_rotate90Clockwise(board);
        Board_moveLeft(board);
        Board_rotate90Clockwise(board);
        Board_rotate90Clockwise(board);
        Board_rotate90Clockwise(board);
        break;
    case 's': // Move down
        Board_rotate90Clockwise(board);
        Board_rotate90Clockwise(board);
        Board_rotate90Clockwise(board);
        Board_moveLeft(board);
        Board_rotate90Clockwise(board);
        break;
    case 'a': // Move left
        Board_moveLeft(board);
        break;
    case 'd': // Move right
        Board_flipHorizontally(board);
        Board_moveLeft(board);
        Board_flipHorizontally(board);
        break;
    default:
        break;
    }
}

void Screen_drawBoard(int board[Board_kSize][Board_kSize]) {
    Screen_clear();

    for (int i = Board_kSize - 1; i > -1; --i) {
        for (int j = 0; j < Board_kSize; ++j) {
            if (board[i][j] == 0) {
                printf(".\t");
            } else {
                printf("%d\t", board[i][j]);
            }
        }
        printf("\n");
    }
}

int Game_run2048() {
    int  board[Board_kSize][Board_kSize] = { 0 };
    char user_input                      = 0;

    Board_init(board);

    while (true) {
        Screen_drawBoard(board);

        // Get user input
        printf("Enter move (w/a/s/d): ");
        if (!scanf_s(" %c", &user_input)) { assert(false); }

        Board_moveTiles(board, user_input); // Move tiles based on input
        Board_addRandomTile(board); // Add a random tile

        if (Game_overs(board)) {
            Screen_drawBoard(board);
            printf("Game Over!\n");
            break;
        }
    }

    return 0;
}

int Game_overs(int board[Board_kSize][Board_kSize]) {
    // Check if any move is possible (either an empty tile or a possible merge)
    for (int i = 0; i < Board_kSize; ++i) {
        for (int j = 0; j < Board_kSize; ++j) {
            if (board[i][j] == 0 || (i < Board_kSize - 1 && board[i][j] == board[i + 1][j]) || (j < Board_kSize - 1 && board[i][j] == board[i][j + 1])) {
                return false; // Game is not over
            }
        }
    }
    return true; // No moves left, game over
}
