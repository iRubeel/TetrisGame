Tetris Game in C++ with SFML

Description

This project is a classic Tetris game developed in C++ and utilizes the Simple and Fast Multimedia Library (SFML). It features basic gameplay elements of Tetris, including moving and rotating Tetriminos, line clearing, and scoring. The game is designed to run on a simple windowing interface with smooth graphics and controls.

Features

Movement and rotation of Tetriminos.
Line clearing and scoring system.
Graphical rendering of game elements using SFML.
Keyboard inputs for control: arrow keys for movement and rotation.
Installation and Running the Game

To run this game, you will need to have SFML installed on your system. Follow the instructions on the SFML website to install SFML.

Compiling the Game

The game can be compiled using g++ with SFML. Use the following command to compile:

g++ main.cpp -o TetrisGame -I/path/to/SFML/include -L/path/to/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

Replace /path/to/SFML with the actual path where SFML is installed on your system.

Running the Game
After compiling, you can run the game using:
./TetrisGame

Controls

Up Arrow - Rotate Tetrimino
Left Arrow - Move Tetrimino left
Right Arrow - Move Tetrimino right
Down Arrow - Accelerate Tetrimino fall
