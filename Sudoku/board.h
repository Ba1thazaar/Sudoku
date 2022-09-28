
#include "node.h"
#include <iostream>
#pragma once
#include <io.h>
#include <fcntl.h>
//Board Class

class Board {
	public:
		Board(int size);
		void DisplayBoard();
		bool GuessValue(int value, int posX, int posY);
	private:
		void HideValues();
		void BoardSetup();
		int boardSize;
		Node gameBoard[9][9];
		void GenerateSolution();
		Node FindLowestEntropy();
		void Collapse(int value, int posX, int posY);
};

//Constructor
Board::Board(int size) {
	boardSize = size;
	BoardSetup();
}

//Recalled on bad solution
void Board::BoardSetup() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			gameBoard[i][j].SetNodePosition(i, j, boardSize);
		}
	}
	GenerateSolution();
	HideValues();
}

//Displays the Sudoku board to the Console
void Board::DisplayBoard() {
	//This line is for the Unicode characters
	_setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			int value = gameBoard[i][j].GetValue();
			if (value == 0) {
				std::wcout << " ";
			}
			else {
				std::wcout << value;
			}
			if (j != boardSize -1) {
				if ((j + 1) % 3 == 0) {
					std::wcout << L" ▐ ";
				}
				else {
					std::wcout << " | ";
				}
			}
		}
		if (i != boardSize - 1) {
			if ((i + 1) % 3 == 0) {
				std::wcout << L"\n——————————————————————————————————\n";
			}
			else {
				std::wcout << "\n----------------------------------\n";
			}
		}
	}
}

//Creates solution for Sudoku board then removes values for playable game
void Board::GenerateSolution() {
	
	int determinedCount = 0;
	
	//determined count is the total number of squares (81 in a 9x9)
	//This keeps looping till all of the squares are solved;
	while (determinedCount < boardSize * boardSize) {
		Node currentNode = FindLowestEntropy();
		int x = currentNode.GetPosX();
		int y = currentNode.GetPosY();

		//Get the node with the lowest entropy, and select on of the superpositions
		if (!gameBoard[x][y].Propagate()) {
			BoardSetup();
		}
		//Remove superpositions of relevant nodes
		Collapse(gameBoard[x][y].GetValue(),x, y);
		determinedCount++;
	}
}

Node Board::FindLowestEntropy() {
	//Returns the node with the lowest entropy for propogation, this makes failure less likely
	Node targetNode = Node();
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (gameBoard[i][j].GetEntropy() < targetNode.GetEntropy()) {
				targetNode = gameBoard[i][j];
			}
		}
	}
	return targetNode;
}

void Board::Collapse(int value, int posX, int posY) {
	//Remove value from all others in column and row
	for (int i = 0; i < boardSize; i++) {
		gameBoard[i][posY].RemoveSuperPos(value);
		gameBoard[posX][i].RemoveSuperPos(value);
	}
	//Remove value from all others in box
	int boxXOffset = ((posX + 1) - (posX % 3)) - 1; // These calculate the starting coordinates of the box for X and Y
	int boxYOffset = ((posY + 1) - (posY % 3)) - 1;

	for (int i = boxXOffset; i < boxXOffset + 3; i++) {
		for (int j = boxYOffset; j < boxYOffset + 3; j++) {
			gameBoard[i][j].RemoveSuperPos(value);
		}
	}
}

//Randomly hides values so the player has something to solve
void Board::HideValues() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			int value = rand();
			if (value % 3 == 0 || value % 2 ==0) {
				gameBoard[i][j].Hide();
			}
		}
	}
}

bool Board::GuessValue(int value, int posX, int posY) {
	//pos Y altered to match traditional cartesian values
	if (gameBoard[8 - (posY - 1)][posX - 1].CheckValue(value)) {
		std::wcout << "\nCorrect!\n";
		gameBoard[8 - (posY - 1)][posX - 1].Reveal();
		return true;
	}
	else {
		std::wcout << "\nIncorrect :(\n";
		return false;
	}
}
