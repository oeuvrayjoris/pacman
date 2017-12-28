#ifndef IMACGL_BOARD_HPP
#define IMACGL_BOARD_HPP

#include <iostream>
#include <vector>

class Board {
    public:
        // Getters
		int getM();
		int getN();
		std::vector<std::vector<int>> getTab();

        // Setters
        void setM(int a);
		void setN(int b);
		void setTab(std::vector<std::vector<int>> newTab);

        // Constructors
        Board();

        // Destructor
        ~Board();

	private:
        // Attr
		int m;
		int n;
		int tab[25][25];
};

#endif