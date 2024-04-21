#ifndef GAME2048_H
#define GAME2048_H

// ANSI escape codes for clearing the screen
#define CLEAR_SCREEN ("\033[2J\033[H")
#define BOARD_SIZE   (4)

// Function Declarations
void initializeBoard(int board[BOARD_SIZE][BOARD_SIZE]);
void addRandomTile(int board[BOARD_SIZE][BOARD_SIZE]);
void moveLeft(int board[BOARD_SIZE][BOARD_SIZE]);
void rotateBoard90Clockwise(int board[BOARD_SIZE][BOARD_SIZE]);
void flipBoardHorizontally(int board[BOARD_SIZE][BOARD_SIZE]);
void moveTiles(int board[BOARD_SIZE][BOARD_SIZE], char direction);
int checkGameOver(int board[BOARD_SIZE][BOARD_SIZE]);
void displayBoard(int board[BOARD_SIZE][BOARD_SIZE]);
int run2048();

#endif // GAME2048_H
