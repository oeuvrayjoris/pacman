#ifndef IMACGL_BOARD_HPP
#define IMACGL_BOARD_HPP

#include <iostream>
#include <vector>

class Board {
    public:
        // Getters
		int getM();
		int getN();

        // Setters
        void setM(int a);
		void setN(int b);

        // Constructors
        Board();
        Board(int a, int b);

        // Destructor
        ~Board();

	private:
        // Attr
		int m;
		int n;
		int board[m][n];
};

#endif