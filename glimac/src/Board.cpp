#include "glimac/Board.hpp"

/* CONSTRUCTOR */

void Board::build() {
	std::vector<std::vector<int>> board{
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4},
		{4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 0, 0, 4, 0, 0, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 4, 4, 4, 0, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 4, 4, 4, 0, 4},
		{4, 0, 4, 4, 4, 4, 0, 4, 0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 0, 4, 4, 4, 4, 0, 4},
		{4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4},
		{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4},
		{0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 4, 4, 0, 4, 4, 4, 0, 4, 0, 4, 0, 0, 0, 0, 0},
		{4, 4, 4, 4, 4, 4, 0, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 4, 4, 4, 4, 4},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{4, 4, 4, 4, 4, 4, 0, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 4, 4, 4, 4, 4},
		{0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 0, 4, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0},
		{4, 4, 4, 4, 4, 4, 0, 4, 0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 0, 4, 4, 4, 4, 4, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4},
		{4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4},
		{4, 4, 4, 4, 0, 4, 0, 4, 0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 0, 4, 0, 4, 4, 4, 4},
		{4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
	};
	level = board;
}


/* CONSTRUCTOR */
Board::Board() {
	levelHeight = 25;
	levelWidth = 25;
	build();
}


/* GETTERS */
int Board::getLevelHeight(){
    return levelHeight;
}

int Board::getLevelWidth(){
    return levelWidth;
}

std::vector<std::vector<int>> Board::getLevel() {
	return level;
}

int Board::getGateCoord_x() const {
    return gateCoord_x;
}

int Board::getGateCoord_y() const {
    return gateCoord_y;
}

bool Board::isSuper() const {
    return super;
}


/* SETTERS */
void Board::setLevelHeight(int new_m){
	levelHeight = new_m;
}

void Board::setLevelWidth(int new_n){
	levelWidth = new_n;
}

void Board::setLevel(std::vector<std::vector<int>> new_tab) {
	level = new_tab;
}

void Board::setGateCoord_x(int gateCoord_x) {
    Board::gateCoord_x = gateCoord_x;
}

void Board::setGateCoord_y(int gateCoord_y) {
    Board::gateCoord_y = gateCoord_y;
}

void Board::setSuper(bool super) {
    Board::super = super;
}


/* METHODS */

void Board::changeValue(int m, int n, int value) {
    level[m][n] = value;
}