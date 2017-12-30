//
// Created by Jordan on 30/12/2017.
//

#ifndef IMACGL_PACMAN_HPP
#define IMACGL_PACMAN_HPP

#include <iostream>
#include <cstring>
#include <glimac/Constants.hpp>
#include "Board.hpp"

class Pacman {

public:
    // Constructors
    Pacman(Board *board);

    // Getters

    int getCoord_x() const;
    int getCoord_y() const;
    int getCoord_x_old() const;
    int getCoord_y_old() const;
    int getLeftDots() const;
    int getScore() const;
    const std::string &getName() const;
    int getDir() const;
    int getDirOld() const;
    int getLives() const;
    int getSuper() const;
    int getKillCount() const;

    // Setters

    void setCoord_x(int coord_x);
    void setCoord_y(int coord_y);
    void setCoord_x_old(int coord_x_old);
    void setCoord_y_old(int coord_y_old);
    void setLeftDots(int leftDots);
    void setScore(int score);
    void setName(const std::string &name);
    void setDir(int dir);
    void setDirOld(int dirOld);
    void setLives(int lives);
    void setSuper(int super);
    void setKillCount(int killCount);

    // Others methods

    void Move();
    void GetDirection(char key);
    bool TestForCollision();

private:
    int coord_x;
    int coord_y;
    int coord_x_old;
    int coord_y_old;

    int leftDots;
    int score;
    std::string name;

    int dir;
    int dirOld;

    int lives;
    int super;
    int killCount;

    Board *board;

};


#endif //IMACGL_PACMAN_HPP
