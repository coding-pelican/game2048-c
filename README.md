# Game 2048

This is an implementation of the classic 2048 game in C. The game is played in the console window and features the iconic sliding and merging of numbered tiles.

## Features

- Classic 2048 gameplay with console-based interface
- Player control using WASD keys
- Random tile generation
- Game over detection

## Getting Started

### Prerequisites

- C compiler (e.g., GCC, Clang, or MSVC)

### Building and Running

1. Clone the repository:

```shell
git clone https://github.com/coding-pelican/game2048-c.git
```

2. Navigate to the project directory:

```shell
cd game2048-c
```

3. Compile the source code:

```shell
clang main.c game2048.c -o game2048
```

4. Run the game:

```shell
./game2048
```

### Gameplay

- Use the WASD keys to move the tiles:
  - W: Move up
  - A: Move left
  - S: Move down
  - D: Move right
- Merge tiles with the same number to create larger numbers
- The game ends when no more moves are possible

### Code Structure

The project consists of the following files:

- `main.c`: The main entry point of the program
- `game2048.c`: The main game logic and rendering code
- `game2048.h`: Header file containing function declarations and constants
- `random.h`: Header file for random number generation
- `README.md`: This readme file providing an overview of the project

### Future Improvements

- Add score tracking
- Implement high score system
- Add color support for better visualization
- Implement undo functionality
- Add game board size selection option

### License

This project is released under the MIT License. See the [LICENSE](README.md) file for more details.

### Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, please open an issue or submit a
pull request.

### Contact

For any questions or inquiries, please contact the project author:
- Name: Gyeongtae Kim
- Email: <codingpelican@gmail.com>

Enjoy playing 2048!
