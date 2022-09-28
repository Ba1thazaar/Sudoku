#pragma once
//Node class
#include <list>
#include <cstdlib>
#include <iostream>
#include <io.h>
#include <fcntl.h>
class Node {
	public:
		Node();
		~Node();
		int GetValue();
		int GetPosX();
		int GetPosY();
		int GetEntropy();
		void SetNodePosition(int x, int y, int size);
		bool Propagate();
		void RemoveSuperPos(int targetValue);
		void Hide();
		void Reveal();
		bool CheckValue(int userValue);
		//assignment operator
		Node& operator=(const Node& n) {
			posX = n.posX;
			posY = n.posY;
			value = n.value;
			superPos = n.superPos;
			entropy = n.superPos.size();
			return *this;
		}
	private:
		int posX;
		int posY;
		int value;
		int boardSize = 9;
		int entropy;
		std::list<int> superPos;
		bool hidden = false;
};

//Constructor
Node::Node() {
	srand(time(NULL));
	value = 0;
	entropy = 10;
	boardSize = 9;
}

void Node::SetNodePosition(int x, int y, int size) {
	posX = x;
	posY = y;
	boardSize = size;
	value = 0;
	entropy = 10;
	//Populate superPos;
	for (int i = 0; i < boardSize; i++) {
		superPos.push_back(i + 1);
	}
	entropy = superPos.size();
}

//Destructor
Node::~Node() {
	//delete[] superPos;
}

void Node::Hide() {
	hidden = true;
}

void Node::Reveal() {
	hidden = false;
}

//only returns a value if not hidden
int Node::GetValue() {
	if (hidden == false) {
		return value;
	}
	else{
		return 0;
	}
}
int Node::GetPosX() {
	return posX;
}
int Node::GetPosY() {
	return posY;
}

int Node::GetEntropy() {
	return entropy;
}

//Select randomly from available superpositions
bool Node::Propagate() {
	//Some functions result in impossible solutions, return false when there are no superpositions left
	if (superPos.size() == 0) {
		std::wcout << "recalculating" << std::endl;
		return false;
	}
	int randIndex = (rand() % superPos.size());
	std::list<int>::iterator it = superPos.begin();
	for (int i = 0; i < randIndex; i++) {
		++it;
	}
	value = *it;
	entropy = 10;
	return true;
}

void Node::RemoveSuperPos(int targetValue) {
	if (value == 0) {
		superPos.remove(targetValue);
		entropy = superPos.size();
	}
}

bool Node::CheckValue(int userValue) {
	if (userValue == value) {
		return true;
	}
	return false;
}
