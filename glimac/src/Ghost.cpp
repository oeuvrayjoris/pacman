//
// Created by Jordan on 31/12/2017.
//

#include "glimac/Ghost.hpp"

// Constructors
Ghost::Ghost(Board *const board) : board(board) {

}

// Other methods
void Ghost::move(int target_x, int target_y) {
    if (wait) {
        wait--;
    }
    else {
        switch (mode) { // c = chasing, s = scattering, f = frightened, d = died // w = waiting, e = exiting, n = entering
            case 'w': // They bounce up and down in the prison
                wait = GHOST_MAX;
                board->changeValue(coord_x, coord_y, prevElem);
                if (coord_x == board->getGateCoord_x() + 2) {
                    coord_x++;
                }
                else {
                    coord_x--;
                }
                if (board->getLevel()[coord_x][coord_y] >= 0 && board->getLevel()[coord_x][coord_y] < 4) // Deal with collision with ghost/pacman so we dont duplicate symbols..
                    prevElem = board->getLevel()[coord_x][coord_y];
                board->changeValue(coord_x, coord_y, id);
                break;
            case 'e': // Find a path to the gate
                wait = GHOST_MAX;
                board->changeValue(coord_x, coord_y, prevElem);
                if (coord_x > board->getGateCoord_x() + 1) {
                    coord_x--;
                }
                else if (coord_y < board->getGateCoord_y()) {
                    coord_y++;
                }
                else if (coord_y > board->getGateCoord_y()) {
                    coord_y--;
                }
                else if (coord_x != board->getGateCoord_x() - 1) { // the ghost is on the door, we make him going out completely
                    coord_x--;
                }
                else { // If the ghost isn't in the prison anymore
                    modeOld = mode;
                    if (color == BLUE_COLOR) { // put as frightened
                        mode = 'f'; //
                    }
                    else {
                        mode = 'c'; // put as chasing
                    }
                    dir = 'q'; // a Ghost is supposed to go to the left after leaving the prison
                    dirOld = 'w';
                    wait = 0;
                }

                if (board->getLevel()[coord_x][coord_y] >= 0 && board->getLevel()[coord_x][coord_y] < 4) // Deal with collision with ghost/pacman so we dont duplicate symbols..
                    prevElem = board->getLevel()[coord_x][coord_y];
                board->changeValue(coord_x, coord_y, id);
                board->changeValue(board->getGateCoord_x(), board->getGateCoord_y(), 20); // We place our gate where it was
                break;
            case 'n': // Entering in the prison
                if (coord_x != board->getGateCoord_y() + 1) {
                    dir = 's';
                    changeCoords();
                    wait = DEAD_MAX;
                    board->changeValue(board->getGateCoord_x(), board->getGateCoord_y(), 20); // We place our gate where it was
                }
                else { // We set the ghost ready to exit
                    color = colorInit;
                    mode = 'e';
                    wait = GHOST_MAX;
                }
                break;
            case 's': // The ghost is scattering, going in random positions (normally it should target a corner of the maze)
                getOpposite();
                if (modeOld == 'e') {
                    modeOld = mode;
                }
                if (mode != modeOld) { // If we were already out, we just reverse direction
                    dir = dirOpp;
                    changeCoords();
                    modeOld = mode;
                }
                else {
                    randomDirection();
                }
                dirOld = dir;
                wait = GHOST_MAX;
                break;
            case 'c': // Chase the pacman
                getOpposite();
                if (modeOld == 'e') {
                    modeOld = mode;
                }
                if (mode != modeOld) { 
                    dir = dirOpp;
                    changeCoords();
                    modeOld = mode;
                }
                else {
                    if (id == 11 || id == 13) { // If Blinky, we chase Pacman
                        bool down = coord_x < board->getPacman()->getCoord_x();
                        bool up = coord_x > board->getPacman()->getCoord_x();
                        bool right = coord_x < board->getPacman()->getCoord_y();
                        bool left = coord_x > board->getPacman()->getCoord_y();
                        bool favorableDirs[4] = { up, left, down, right };
                        targetObject(favorableDirs);
                    }
                    /* Target where Pacman will go
                    else if (id == 12) {

                        int pos_x = board->getPacman()->getCoord_x();
                        int pos_y = board->getPacman()->getCoord_y();

                        if (board->getPacman()->getDir() == 'z') {
                            pos_x -= 2;
                            while (pos_x < board->getLevel().size())
                                pos_x++;
                            while (board->getLevel()[pos_x][pos_y] < 0 || board->getLevel()[pos_x][pos_y] > 3)
                                pos_x++;
                        }                        
                        else if (board->getPacman()->getDir() == 's') {
                            pos_x += 2;
                            while (pos_x > board->getLevel().size())
                                pos_x--;
                            while (board->getLevel()[pos_x][pos_y] < 0 || board->getLevel()[pos_x][pos_y] > 3)
                                pos_x--;
                        }                        
                        else if (board->getPacman()->getDir() == 'q') {
                            pos_y -= 2;
                            while (pos_y < board->getLevel()[0].size())
                                pos_y++;
                            while (board->getLevel()[pos_x][pos_y] < 0 || board->getLevel()[pos_x][pos_y] > 3)
                                pos_y++;
                        }                        
                        else if (board->getPacman()->getDir() == 'd') {
                            pos_y += 2;
                            while (pos_y > board->getLevel()[0].size())
                                pos_y--;
                            while (board->getLevel()[pos_x][pos_y] < 0 || board->getLevel()[pos_x][pos_y] > 3)
                                pos_y--;
                        }

                        bool down = coord_x < pos_x;
                        bool up = coord_x > pos_x;
                        bool right = coord_x < pos_y;
                        bool left = coord_x > pos_y;
                        bool favorableDirs[4] = { up, left, down, right };
                        targetObject(favorableDirs);

                    }*/
                    else if (id == 12 || id == 14) {
                        randomDirection();
                    }
                }
                dirOld = dir;
                wait = GHOST_MAX;
                break;
            case 'f': // The ghost is frightened (for the moment it moves randomly, but slower than before, it should avoid the pacman)
                getOpposite();
                if (modeOld == 'e') {
                    modeOld = mode;
                }
                if (mode != modeOld) { // If we were already out, we just reverse direction
                    dir = dirOpp;
                    changeCoords();
                    modeOld = mode;
                }
                else {
                    randomDirection();
                }
                dirOld = dir;
                wait = RUN_MAX;
                break;
            case 'd': // If the ghost died, he returns to the prison
                getOpposite();
                if (coord_x != board->getGateCoord_x() - 1 || coord_y != board->getGateCoord_y()) {
                    bool down = coord_x < board->getGateCoord_x() - 1;
                    bool up = coord_x > board->getGateCoord_x() - 1;
                    bool right = coord_y < board->getGateCoord_y();
                    bool left = coord_y > board->getGateCoord_y();
                    bool favorableDirs[4] = { up, left, down, right };
                    targetObject(favorableDirs);
                }
                else { // The ghost is just in front of the gate, so he enters in the room
                    mode = 'n';
                }
                dirOld = dir;
                wait = DEAD_MAX;
                break;
        }
    }
}

void Ghost::targetObject(bool const favorableDirs[4]) {
    int good = 0; // Number of good directions
    char possibleDirs[4] = {' ',' ',' ',' '};
    for (int i = 0; i < 4; i++) {
        dir = ALL_DIRS[i];
        if (favorableDirs[i] && !testForCollision() && dirOpp != dir) { // If we can go to this direction
            possibleDirs[good] = dir; // We keep it.
            good++;
        }
    }
    if (good == 0) {
        randomDirection();
    }
    else {
        dir = possibleDirs[rand() % good]; // We choose a random dir from the possible ones we have
        changeCoords();
    }
}

void Ghost::randomDirection() {
    getOpposite();
    bool goOpposite = testForCollision_Creatures(); // if 2 Ghosts are colliding
    if (goOpposite) {
        dir = dirOpp;
    }
    else {
        do {
            do {
                dir = ALL_DIRS[rand() % 4]; // we pick a random position different than the opposite
            } while (dir == dirOpp);
        } while (testForCollision() == true && testForCollision_Creatures() == false);
        changeCoords();
    }
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

bool Ghost::testForCollision_Creatures() {
    int elem;
    bool exists;
    switch (dir) {
        case 'q':
            elem = board->getLevel()[coord_x][coord_y - 1];
            exists = std::find(std::begin(COLLISION_CREATURES), std::end(COLLISION_CREATURES), elem) != std::end(COLLISION_CREATURES);
            // if travelling through the tunnel at the left
            if (exists) {
                return true;
            }
            break;
        case 'd':
            elem = board->getLevel()[coord_x][coord_y + 1];
            exists = std::find(std::begin(COLLISION_CREATURES), std::end(COLLISION_CREATURES), elem) != std::end(COLLISION_CREATURES);
            // if travelling through the tunnel at the right
            if (exists) {
                return true;
            }
            break;
        case 'z':
            elem = board->getLevel()[coord_x - 1][coord_y];
            exists = std::find(std::begin(COLLISION_CREATURES), std::end(COLLISION_CREATURES), elem) != std::end(COLLISION_CREATURES);
            if (exists) {
                return true;
            }
            break;
        case 's':
            elem = board->getLevel()[coord_x + 1][coord_y];
            exists = std::find(std::begin(COLLISION_CREATURES), std::end(COLLISION_CREATURES), elem) != std::end(COLLISION_CREATURES);
            if (exists) {
                return true;
            }
            break;
    }
    return false;
}

void Ghost::changeCoords() {
    board->changeValue(coord_x, coord_y, prevElem);
    switch(dir) {
        case 'q': // moving left
            if (coord_y == 0) // If we go through the tunnel to the left
                coord_y = board->getLevelWidth() - 1;
            else
                coord_y--;
            break;
        case 'd': // moving right
            if (coord_y == board->getLevelWidth() - 1) // If we go through the tunnel to the right
                coord_y = 0;
            else
                coord_y++;
            break;
        case 'z': // moving up
            coord_x--;
            break;
        case 's': // moving down
            coord_x++;
            break;
    }

    if (board->getLevel()[coord_x][coord_y] >= 0 && board->getLevel()[coord_x][coord_y] < 4) // Deal with collision with ghost/pacman so we dont duplicate symbols..
        prevElem = board->getLevel()[coord_x][coord_y]; // prevElem can only be dots, pellets, fruits or empty cases
    board->changeValue(coord_x, coord_y, id);
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
    color = WHITE_COLOR;
    modeOld = mode;
    mode = 'd';
}

void Ghost::blinkyBehaviour(){}
void Ghost::pinkyBehaviour(){}
void Ghost::inkyBehaviour(){}
void Ghost::clydeBehaviour(){}

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

int Ghost::getCoord_x_old() const {
    return coord_x_old;
}

int Ghost::getCoord_y_old() const {
    return coord_y_old;
}

int Ghost::getId() const {
    return id;
}

int Ghost::getPrevElem() const {
    return prevElem;
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

void Ghost::setCoord_x_old(int coord_x_old) {
    Ghost::coord_x_old = coord_x_old;
}

void Ghost::setCoord_y_old(int coord_y_old) {
    Ghost::coord_y_old = coord_y_old;
}

void Ghost::setId(int id) {
    Ghost::id = id;
}

void Ghost::setPrevElem(int prevElem) {
    Ghost::prevElem = prevElem;
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