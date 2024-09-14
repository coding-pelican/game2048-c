/**
 * @file game2048.h
 * @author Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 *
 * @brief Provides a set of functions for playing the 2048 game.
 * @details This file defines a set of functions for playing the 2048 game.
 *
 * @version 0.1
 * @date 2024-09-14
 *
 * @copyright Released under the MIT License. See LICENSE file for details.
 */


#ifndef GAME2048_H
#define GAME2048_H

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)


#pragma region Board
/**
 * @brief The size of the game board.
 * @details The size of the game board, which is a constant value of 4.
 */
#define Board_kSize (4)
/**
 * @brief Initializes the game board with all tiles set to 0.
 * @param board The 2D array representing the game board.
 */
void Board_init(int board[Board_kSize][Board_kSize]);
/**
 * @brief Adds a new random tile (either 2 or 4) to an empty position on the game board.
 * @param board The 2D array representing the game board.
 */
void Board_addRandomTile(int board[Board_kSize][Board_kSize]);
/**
 * @brief Moves all tiles in the game board to the left, merging tiles of the same value.
 * @param board The 2D array representing the game board.
 */
void Board_moveLeft(int board[Board_kSize][Board_kSize]);
/**
 * @brief Rotates the game board 90 degrees clockwise.
 * @param board The 2D array representing the game board.
 */
void Board_rotate90Clockwise(int board[Board_kSize][Board_kSize]);
/**
 * @brief Flips the game board horizontally.
 * @param board The 2D array representing the game board.
 */
void Board_flipHorizontally(int board[Board_kSize][Board_kSize]);
/**
 * @brief Moves all tiles in the game board in the specified direction, merging tiles of the same value.
 * @param board The 2D array representing the game board.
 * @param direction The direction to move the tiles (e.g. 'l' for left, 'r' for right, 'u' for up, 'd' for down).
 */
void Board_moveTiles(int board[Board_kSize][Board_kSize], char direction);
#pragma endregion // Board

#pragma region Screen
/**
 * @brief Clears the terminal screen.
 * @details Clears the terminal screen by printing the ANSI escape codes to move the cursor to the top-left corner and clear the entire screen.
 */
#define Screen_clear() printf("\033[2J\033[H")
/**
 * @brief Draws the current state of the game board to the screen.
 * @param board The 2D array representing the game board.
 */
void Screen_drawBoard(int board[Board_kSize][Board_kSize]);
#pragma endregion // Screen

#pragma region Game
/**
 * @brief Runs the main game loop for the 2048 game.(for testing purposes)
 * @return Terminates the program.
 * @details This function is the entry point for the 2048 game.
            - It initializes the game board, adds the first random tile, and then enters a game loop that handles user
            input and updates the game state accordingly.
            - The game loop continues until the game is over, at which terminates the function returns.
 * TODO(dev-dasae): Records the final score of the game.
 */
int Game_run2048();
/**
 * @brief Checks if the game is over by determining if there are any valid moves left on the game board.
 * @param board The 2D array representing the game board.
 * @return 1 if the game is over, 0 otherwise.
 */
int Game_overs(int board[Board_kSize][Board_kSize]);
#pragma endregion // Game


#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

#endif // !GAME2048_H
