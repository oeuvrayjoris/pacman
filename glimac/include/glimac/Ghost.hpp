//
// Created by Jordan on 31/12/2017.
//

#ifndef IMACGL_GHOST_HPP
#define IMACGL_GHOST_HPP

#include <iostream>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include "Board.hpp"
#include "Constants.hpp"
#include "glm.hpp"

class Ghost {

public:

    // Constructors
    Ghost(Board *const board);

    // Others methods
    void move(int, int);
    void targetObject(bool[4]);
    void randomDirection();
    bool testForCollision();
    bool testForCollision_Creatures();
    void changeCoords();
    void getOpposite();
    void die();

    // Getters
    int getCoord_x() const;
    int getCoord_y() const;
    int getCoord_x_init() const;
    int getCoord_y_init() const;
    int getCoord_x_old() const;
    int getCoord_y_old() const;
    int getId() const;
    int getPrevElem() const;
    int getWait() const;
    char getDir() const;
    char getDirOld() const;
    char getDirOpp() const;
    char getMode() const;
    char getModeOld() const;
    glm::vec3 getColor() const;
    glm::vec3 getColorInit() const;

    // Setters
    void setCoord_x(int coord_x);
    void setCoord_y(int coord_y);
    void setCoord_x_init(int coord_x_old);
    void setCoord_y_init(int coord_y_old);
    void setCoord_x_old(int coord_x_old);
    void setCoord_y_old(int coord_y_old);
    void setId(int id);
    void setPrevElem(int prevElem);
    void setWait(int wait);
    void setDir(char dir);
    void setDirOld(char dirOld);
    void setDirOpp(char dirOpp);
    void setMode(char mode);
    void setModeOld(char modeOld);
    void setColor(glm::vec3 color);
    void setColorInit(glm::vec3 colorInit);


private:

    int coord_x;
    int coord_y;
    int coord_x_init;
    int coord_y_init;
    int coord_x_old;
    int coord_y_old;
    int id;
    int prevElem;

    int wait;
    char dir;
    char dirOld;
    char dirOpp;
    char mode; // c = chasing, s = scattering, f = frightened, d = died // w = waiting, e = exiting, n = entering
    char modeOld;
    glm::vec3 color;
    glm::vec3 colorInit;

    Board *board;

};


#endif //IMACGL_GHOST_HPP
