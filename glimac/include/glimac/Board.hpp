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
    int getGateCoord_x() const;
    int getGateCoord_y() const;
    bool isSuper() const;

    // Setters
	void setLevelHeight(int new_m);
	void setLevelWidth(int new_n);
	void setLevel(std::vector<std::vector<int>> new_tab);
    void setGateCoord_x(int gateCoord_x);
    void setGateCoord_y(int gateCoord_y);
    void setSuper(bool super);

    // Methods
	void build();
	void changeValue(int m, int n, int value);

private:
	// Attr
	int levelHeight;
	int levelWidth;
	std::vector<std::vector<int>> level;
	int gateCoord_x;
	int gateCoord_y;
    bool super;
};

#endif