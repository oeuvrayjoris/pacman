#ifndef IMACGL_BOARD_HPP
#define IMACGL_BOARD_HPP

#include <iostream>
#include <vector>

class Board {

public:

	// Constructors
	Board();

	// Destructor
	~Board();

	// Getters
	int getM();
	int getN();
    std::vector<std::vector<int>> getTab();

	// Setters
	void setM(int a);
	void setN(int b);
	void setTab(std::vector<std::vector<int>> newTab);

	private:
        // Attr
		int m;
		int n;
        std::vector<std::vector<int>> tab;
};

#endif