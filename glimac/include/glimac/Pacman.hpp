//
// Created by Jordan on 30/12/2017.
//

#ifndef IMACGL_PACMAN_HPP
#define IMACGL_PACMAN_HPP
#define GLEW_STATIC

#include <iostream>
#include <cstring>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include <afxres.h>
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>

#include <glimac/Constants.hpp>
class Board;

class Pacman {

public:
    // Constructors
    Pacman(Board *const board);

    // Others methods
    void move(char key);
    void getDirection(char key);
    void changeCoords();
    bool validDirection();

    void increaseScore(int scoreAdd);
    void die();
    int increaseKill();

    // Getters
    int getCoord_x() const;
    int getCoord_y() const;
    int getCoord_x_old() const;
    int getCoord_y_old() const;
    int getCoord_x_init() const;
    int getCoord_y_init() const;
    int getLeftDots() const;
    int getScore() const;
    const std::string &getName() const;
    char getDir() const;
    char getDirOld() const;
    int getLives() const;
    int getSuper() const;
    int getKillCount() const;
    int getWait() const;


    // Setters
    void setCoord_x(int coord_x);
    void setCoord_y(int coord_y);
    void setCoord_x_old(int coord_x_old);
    void setCoord_y_old(int coord_y_old);
    void setCoord_x_init(int coord_x_init);
    void setCoord_y_init(int coord_y_init);
    void setLeftDots(int leftDots);
    void setScore(int score);
    void setName(const std::string &name);
    void setDir(char dir);
    void setDirOld(char dirOld);
    void setLives(int lives);
    void setSuper(int super);
    void setKillCount(int killCount);
    void setWait(int wait);

private:
    int coord_x;
    int coord_y;
    int coord_x_old;
    int coord_y_old;
    int coord_x_init;
    int coord_y_init;

    int wait;

    int leftDots;
    int score;
    std::string name;

    char dir;
    char dirOld;

    int lives;
    int super;
    int killCount;

    Board *board;

};


#endif //IMACGL_PACMAN_HPP
