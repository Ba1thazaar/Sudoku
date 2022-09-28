
#include <iostream>
#include "board.h"
#include <io.h>
#include <fcntl.h>


bool MakeGuess(Board &board) {
    int x, y, value;
    std::wcout << "Please enter x position:";
    std::cin >> x;
    std::wcout << "Please enter y position:";
    std::cin >> y;
    std::wcout << "Please enter value";
    std::cin >> value;
    system("CLS");
    if (board.GuessValue(value, x, y)) {
        board.DisplayBoard();
        return true;
    }
    board.DisplayBoard();
    return false;
}

int main()
{
    int totalGuesses = 0;
    Board board = Board(9);
    std::wcout << "Sudoku!\n";

    board.DisplayBoard();
    //Main Game Loop
    while(totalGuesses < 10) {
        std::wcout << "\nIncorrect Guesses Left: ";
        std::wcout << 10 - totalGuesses << std::endl;
        if (!MakeGuess(board)) {
            totalGuesses++;
        }
    }
}

