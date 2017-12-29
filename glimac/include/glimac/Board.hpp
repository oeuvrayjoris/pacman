#ifndef IMACGL_BOARD_HPP
#define IMACGL_BOARD_HPP

#include <iostream>
#include <vector>

class Board {
public:
	// Constructors
	Board();

	// Getters
	int getM();
	int getN();
	std::vector<std::vector<int>> getTab();

	// Setters
	void setM(int new_m);
	void setN(int new_n);
	void setTab(std::vector<std::vector<int>> new_tab);

	// Methods
	void build();
	void changeValue(int m, int n, int value);

private:
	// Attr
	int m;
	int n;
	std::vector<std::vector<int>> tab;
};

#endif