//
// Created by Jordan on 03/01/2018.
//

#ifndef IMACGL_PELLET_HPP
#define IMACGL_PELLET_HPP

#include "Board.hpp"

class Pellet {
private:
    int coord_x, coord_y;

    Board *board;

public:

    // Constructors
    Pellet(Board *const board);

    // Setters
    void setCoord_x(int x) {
        this->coord_x = x;
    }
    void setCoord_y(int y) {
        this->coord_y = y;
    }
};



#endif //IMACGL_PELLET_HPP
