#ifndef IMACGL_BOARD_HPP
#define IMACGL_BOARD_HPP

#include <iostream>
#include <vector>

class Board {
<<<<<<< HEAD
    public:
        // Getters
		int getLargeur();
		int getHauteur();
		std::vector<std::vector<int>> getTab();
=======
>>>>>>> 4085856f460a9d501551e89c9d99c7b8d41c41d6

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
<<<<<<< HEAD
		int largeur;
		int hauteur;
		int tab[25][25];
=======
		int m;
		int n;
        std::vector<std::vector<int>> tab;
>>>>>>> 4085856f460a9d501551e89c9d99c7b8d41c41d6
};

#endif