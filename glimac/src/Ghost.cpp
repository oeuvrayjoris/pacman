//
// Created by Jordan on 31/12/2017.
//

#include "glimac/Ghost.hpp"

Ghost::Ghost(Board *const board);

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

void Ghost::targetObject(bool[4]);

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

void Ghost::dead();