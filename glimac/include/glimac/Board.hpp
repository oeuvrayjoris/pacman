#ifndef IMACGL_BOARD_HPP
#define IMACGL_BOARD_HPP

#include <iostream>
#include <vector>

class Board {
public:
	// Constructors
	Board();

	// Getters
	int getLevelHeight();
	int getLevelWidth();
	std::vector<std::vector<int>> getLevel();

	// Setters
	void setLevelHeight(int new_m);
	void setLevelWidth(int new_n);
	void setLevel(std::vector<std::vector<int>> new_tab);

	// Methods
	void build();
	void changeValue(int m, int n, int value);

private:
	// Attr
	int levelHeight;
	int levelWidth;
	std::vector<std::vector<int>> level;
};

#endif