//
// Created by Jordan on 30/12/2017.
//

#include "glimac/Pacman.hpp"

// Constructors

Pacman::Pacman(Board *board) : board(board) {
    score = 0;
}


// Getters

int Pacman::getCoord_x() const {
    return coord_x;
}

int Pacman::getCoord_y() const {
    return coord_y;
}

int Pacman::getCoord_x_old() const {
    return coord_x_old;
}

int Pacman::getCoord_y_old() const {
    return coord_y_old;
}

int Pacman::getLeftDots() const {
    return leftDots;
}

int Pacman::getScore() const {
    return score;
}

const std::string &Pacman::getName() const {
    return name;
}

int Pacman::getDir() const {
    return dir;
}

int Pacman::getDirOld() const {
    return dirOld;
}

int Pacman::getLives() const {
    return lives;
}

int Pacman::getSuper() const {
    return super;
}

int Pacman::getKillCount() const {
    return killCount;
}

// Setters

void Pacman::setCoord_x(int coord_x) {
    Pacman::coord_x = coord_x;
}

void Pacman::setCoord_y(int coord_y) {
    Pacman::coord_y = coord_y;
}

void Pacman::setCoord_x_old(int coord_x_old) {
    Pacman::coord_x_old = coord_x_old;
}

void Pacman::setCoord_y_old(int coord_y_old) {
    Pacman::coord_y_old = coord_y_old;
}

void Pacman::setLeftDots(int leftDots) {
    Pacman::leftDots = leftDots;
}

void Pacman::setScore(int score) {
    Pacman::score = score;
}

void Pacman::setName(const std::string &name) {
    Pacman::name = name;
}

void Pacman::setDir(int dir) {
    Pacman::dir = dir;
}

void Pacman::setDirOld(int dirOld) {
    Pacman::dirOld = dirOld;
}

void Pacman::setLives(int lives) {
    Pacman::lives = lives;
}

void Pacman::setSuper(int super) {
    Pacman::super = super;
}

void Pacman::setKillCount(int killCount) {
    Pacman::killCount = killCount;
}

// Other methods

void Pacman::Move() {

}

void Pacman::GetDirection(char key) {
    dir = key;
    // if not, try moving in the same direction as before
    if (!strchr(ALL_DIRS, dir)) {
        dir = dirOld;
    }
}

bool Pacman::TestForCollision() {

    // save old coordinates
    coord_x_old = coord_x;
    coord_y_old = coord_y;
    // if the character in front of the player is a space, move in the appropriate direction
    switch (dir) {
        case 'q':
            // if travelling through the tunnel at the left
            if (coord_x == 0) {
                coord_x = board->getLevelWidth() - 1;
            }
            else if (strchr(NO_COLLISION_TILES, board->GetLevel(coord_y, coord_x - 1))) {
                --coord_x;
            }
            break;
        case 'd':
            // if travelling through the tunnel at the right
            if (coord_x == board->getLevelWidth() - 1) {
                coord_x = 0;
            }
            else if (strchr(NO_COLLISION_TILES, board->GetLevel(coord_y, coord_x + 1))) {
                ++coord_x;
            }
            break;
        case 'w':
            if (strchr(NO_COLLISION_TILES, board->GetLevel(coord_y - 1, coord_x))) {
                --coord_y;
            }
            break;
        case 's':
            if (strchr(NO_COLLISION_TILES, board->GetLevel(coord_y + 1, coord_x))) {
                ++coord_y;
            }
    }
    // if coordinates were not changed, there was a collision
    if (coord_x == coord_x_old && coord_y == coord_y_old) {
        return true;
    }
    return false;
}