//
// Created by Jordan on 30/12/2017.
//

#include "glimac/Pacman.hpp"
#include "glimac/Board.hpp"

// Constructors
Pacman::Pacman(Board *const board) : board(board) {
    score = 0;
    wait = PACMAN_MAX;
}

// Other methods
void Pacman::move(char key) {
    if (wait) {
        --wait;
    }
    else {
        getDirection(key);
        if (testForCollision() == false) {

            if (board->getLevel()[coord_x][coord_y] != 0) {

                int scoreAdd;
                if (board->getLevel()[coord_x][coord_y] == 2) {
                    scoreAdd = 50;
                    super = SUPER_MAX;
                }
                else if (board->getLevel()[coord_x][coord_y] == 3) {
                    scoreAdd = 500;
                } else {
                    scoreAdd = 10;
                }
                --leftDots;
                increaseScore(scoreAdd);
            }
            board->changeValue(coord_x_old, coord_y_old, 0);
            board->changeValue(coord_x, coord_y, 10);
            wait = PACMAN_MAX;
            dirOld = dir;
        }

    }
}

void Pacman::getDirection(char key) {

    dir = key;
    if (!strchr(ALL_DIRS, key))
        // Try moving in the same direction as before
        dir = dirOld;
}

bool Pacman::testForCollision() {

    int elem;
    bool exists;
    // save old coordinates
    coord_x_old = coord_x;
    coord_y_old = coord_y;
    // if the character in front of the player is a space, move in the appropriate direction
    switch (dir) {
        case 'q':
            elem = board->getLevel()[coord_x][coord_y - 1];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);

            // if travelling through the tunnel at the left
            if (coord_y == 0) {
                coord_y = board->getLevelWidth() - 1;
            }
            else if (exists) {
                --coord_y;
            }
            break;
        case 'd':
            elem = board->getLevel()[coord_x][coord_y + 1];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            // if travelling through the tunnel at the right
            if (coord_y == board->getLevelWidth() - 1) {
                coord_y = 0;
            }
            else if (exists) {
                ++coord_y;
            }
            break;
        case 'z':
            elem = board->getLevel()[coord_x - 1][coord_y];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            if (exists) {
                --coord_x;
            }
            break;
        case 's':
            elem = board->getLevel()[coord_x + 1][coord_y];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            if (exists) {
                ++coord_x;
            }
            break;
    }
    // if coordinates were not changed, there was a collision
    if (coord_x == coord_x_old && coord_y == coord_y_old) {
        return true;
    }
    return false;
}

void Pacman::increaseScore(int scoreAdd) {
    // gain a life every time the score crosses a multiple of 10000
    if (score / 10000 < (score + scoreAdd) / 10000) {
        ++lives;
    }
    score += scoreAdd;
}

void Pacman::die(){
    lives--;

    Sleep(500);
    --lives;
    if (lives != 0) {
        board->initGame();
    }
    else {
        //board->PrintGameOver();
    }
}

int Pacman::increaseKill() {
    killCount++;
    int scoreAdd = 200 * pow(2, killCount - 1);
    increaseScore(scoreAdd);
    return scoreAdd;
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

int Pacman::getCoord_x_init() const {
    return coord_x_init;
}

int Pacman::getCoord_y_init() const {
    return coord_y_init;
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

char Pacman::getDir() const {
    return dir;
}

char Pacman::getDirOld() const {
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

int Pacman::getWait() const {
    return wait;
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

void Pacman::setCoord_x_init(int coord_x_init) {
    Pacman::coord_x_init = coord_x_init;
}

void Pacman::setCoord_y_init(int coord_y_init) {
    Pacman::coord_y_init = coord_y_init;
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

void Pacman::setDir(char dir) {
    Pacman::dir = dir;
}

void Pacman::setDirOld(char dirOld) {
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

void Pacman::setWait(int wait) {
    Pacman::wait = wait;
}