//
// Created by Jordan on 31/12/2017.
//

#ifndef IMACGL_GHOST_HPP
#define IMACGL_GHOST_HPP

#include <iostream>
#include "Board.hpp"

class Ghost {
public:
    Ghost(Board *const board);
    void move(int, int);
    void targetObject(bool[4]);
    void randomDirection();
    bool testForCollision();
    void changeCoords();
    void getOpposite();
    void dead();

private:

    int coord_x;
    int coord_y;
    int coord_x_old;
    int coord_y_old;

    int wait;

    char dir;
    char dirOld;
    char dirOpp;

    char mode;
    char modeOld;

    Board *board;

};


#endif //IMACGL_GHOST_HPP
