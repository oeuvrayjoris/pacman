//
// Created by Jordan on 31/12/2017.
//

#include "glimac/Ghost.hpp"

// Constructors
Ghost::Ghost(Board *const board) {
    // code here..
}

// Other methods
void Ghost::move(int, int) {
    if (wait) {
        --wait;
    }
    else {
        switch (mode) { // c = chasing, w = waiting, e = exiting, t = eatable, a = eaten, r = running, n = entering
            case 'w':

                wait = GHOST_MAX;
                break;
            case 'e':
                break;
            case 'c':
                break;
            case 't':
                break;
            case 'a':
                break;
            case 'r':
                break;
            case 'n':
                break;
        }
    }
}

void Ghost::targetObject(bool[4]) {
    // code here
}

void Ghost::randomDirection() {
    getOpposite();
    do {
        do {
            dir = ALL_DIRS[rand()%4];
        } while (dir == dirOpp);
    } while(testForCollision() == true);
}

bool Ghost::testForCollision() {
    int elem;
    bool exists;
    switch (dir) {
        case 'q':
            elem = board->getLevel()[coord_x][coord_y - 1];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            // if travelling through the tunnel at the left
            if (coord_y == 0 || exists) {
                return false;
            }
            break;
        case 'd':
            elem = board->getLevel()[coord_x][coord_y + 1];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            // if travelling through the tunnel at the right
            if (coord_y == board->getLevelWidth() - 1 || exists) {
                return false;
            }
            break;
        case 'z':
            elem = board->getLevel()[coord_x - 1][coord_y];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            if (exists) {
                return false;
            }
            break;
        case 's':
            elem = board->getLevel()[coord_x + 1][coord_y];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            if (exists) {
                return false;
            }
            break;
    }
    return true;
}

void Ghost::changeCoords() {
    switch(dir) {
        case 'q':
            if (coord_y == 0)
                coord_y = board->getLevelWidth() - 1;
            else
                --coord_y;
            break;
        case 'd':
            if (coord_y == board->getLevelWidth() - 1)
                coord_y = 0;
            else
                ++coord_y;
            break;
        case 'z':
            --coord_x;
            break;
        case 's':
            ++coord_x;
            break;
    }
}

void Ghost::getOpposite() {
    if (dirOld == 'z')
        dirOpp = 's';
    if(dirOld == 's')
        dirOpp = 'z';
    if(dirOld == 'q')
        dirOpp = 'd';
    if(dirOld == 'd')
        dirOpp = 'q';
}

void Ghost::die() {
    // code ...
}

// Getters
int Ghost::getCoord_x() const {
    return coord_x;
}

int Ghost::getCoord_y() const {
    return coord_y;
}

int Ghost::getCoord_x_init() const {
    return coord_x_init;
}

int Ghost::getCoord_y_init() const {
    return coord_y_init;
}

int Ghost::getWait() const {
    return wait;
}

char Ghost::getDir() const {
    return dir;
}

char Ghost::getDirOld() const {
    return dirOld;
}

char Ghost::getDirOpp() const {
    return dirOpp;
}

char Ghost::getMode() const {
    return mode;
}

char Ghost::getModeOld() const {
    return modeOld;
}

glm::vec3 Ghost::getColor() const {
    return color;
}

glm::vec3 Ghost::getColorInit() const {
    return colorInit;
}

// Setters
void Ghost::setCoord_x(int coord_x) {
    Ghost::coord_x = coord_x;
}

void Ghost::setCoord_y(int coord_y) {
    Ghost::coord_y = coord_y;
}

void Ghost::setCoord_x_init(int coord_x_old) {
    Ghost::coord_x_init = coord_x_old;
}

void Ghost::setCoord_y_init(int coord_y_old) {
    Ghost::coord_y_init = coord_y_old;
}

void Ghost::setWait(int wait) {
    Ghost::wait = wait;
}

void Ghost::setDir(char dir) {
    Ghost::dir = dir;
}

void Ghost::setDirOld(char dirOld) {
    Ghost::dirOld = dirOld;
}

void Ghost::setDirOpp(char dirOpp) {
    Ghost::dirOpp = dirOpp;
}

void Ghost::setMode(char mode) {
    Ghost::mode = mode;
}

void Ghost::setModeOld(char modeOld) {
    Ghost::modeOld = modeOld;
}

void Ghost::setColor(glm::vec3 color) {
    Ghost::color = color;
}

void Ghost::setColorInit(glm::vec3 colorInit) {
    Ghost::colorInit = colorInit;
}
