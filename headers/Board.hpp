#ifndef IMACGL_BOARD_HPP
#define IMACGL_BOARD_HPP

#include <iostream>
#include <vector>

class Board {
    public:
        // Getters
		int getLargeur();
		int getHauteur();
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
		int largeur;
		int hauteur;
		int tab[25][25];
};

#endif