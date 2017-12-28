#include "../headers/Board.hpp"

/* GETTERS */
int Board::getM() {
    return m;
}

int Board::getN() {
    return n;
}


/* SETTERS */
void Board::setM(int a) {
	m = a;
}

void Board::setN(int b) {
	n = b;
}


/* CONSTRUCTORS */
Board::Board() {
	m = 0;
	n = 0;
	board = 0;
}

Board::Board(int a, int b) {
	m = a;
	n = b;
	board = 0;
}


/* DESTRUCTOR */
Board::~Board() {}




