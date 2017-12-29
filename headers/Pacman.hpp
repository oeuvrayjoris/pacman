//
// Created by Jordan on 28/12/2017.
//

#ifndef IMACGL_PACMAN_HPP
#define IMACGL_PACMAN_HPP


#include "Creature.hpp"

class Pacman : public Creature {

public:

    Pacman();

    Pacman(const std::string &name, int x_coord, int y_coord);

    int getLives() const;

    void setLives(int lives);

    float getScore() const;

    void setScore(int score);

    void loseLife();

    void increaseScore(float value);

private:

    int lives;
    float score;
};


#endif //IMACGL_PACMAN_HPP
