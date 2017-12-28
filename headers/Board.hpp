#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

class Board {
    public:
        // Getters
		int getX();
		int getY();

        // Setters
        void setX(int a);
		void setY(int b);

        // Constructors
        Board();
        Board(int m, int n);

        // Destructor
        ~Board();


	private:
        // Attr
		int x;
		int y;
		int board[y][x];
};

#endif