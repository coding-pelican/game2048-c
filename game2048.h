#ifndef GAME2048_H
#define GAME2048_H

#define Board_kSize (4)

void Board_init(int board[Board_kSize][Board_kSize]);
void Board_addRandomTile(int board[Board_kSize][Board_kSize]);
void Board_moveLeft(int board[Board_kSize][Board_kSize]);
void Board_rotate90Clockwise(int board[Board_kSize][Board_kSize]);
void Board_flipHorizontally(int board[Board_kSize][Board_kSize]);
void Board_moveTiles(int board[Board_kSize][Board_kSize], char direction);

// ANSI escape codes for clearing the screen
#define Screen_clear() printf("\033[2J\033[H")
void Screen_drawBoard(int board[Board_kSize][Board_kSize]);

int Game_run2048();
int Game_overs(int board[Board_kSize][Board_kSize]);

#endif // !GAME2048_H
