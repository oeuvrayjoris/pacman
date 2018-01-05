//
// Created by Jordan on 30/12/2017.
//

#include "glimac/Pacman.hpp"
#include "glimac/Board.hpp"
#include "glimac/Ghost.hpp"

// Constructors
Pacman::Pacman(Board *const board) : board(board) {
    score = 0;
    wait = PACMAN_MAX;
}

// Other methods
void Pacman::move(char key) {
    if (wait) {
        wait--;
    }
    else {
        getDirection(key);
        if (validDirection()) {
            changeCoords();
            if (board->getLevel()[coord_x][coord_y] != 0) { // if it's not an empty case

                int scoreAdd;
                if (board->getLevel()[coord_x][coord_y] == 2) { // Pellet
                    scoreAdd = 50;
                    super = SUPER_MAX;
                }
                else if (board->getLevel()[coord_x][coord_y] == 3) { // Fruit
                    scoreAdd = 500; // Deal with it after
                }
                else { // Normal dot
                    scoreAdd = 10;
                }
                leftDots--;
                increaseScore(scoreAdd);
            }
            board->changeValue(coord_x_old, coord_y_old, 0); // Modifications for the display
            board->changeValue(coord_x, coord_y, 10);
            wait = PACMAN_MAX;
            dirOld = dir;
        }

    }
}

void Pacman::getDirection(char key) {

    dir = key;
    if (!strchr(ALL_DIRS, key) || !validDirection())
        // Try moving in the same direction as before
        dir = dirOld;
}

bool Pacman::validDirection() {
    int elem;
    bool exists; // Will check if we collide with a wall
    bool existsG; // "Collision" with ghosts are authorized so when we run after one we can eat it
    // if the character in front of the player is a space, move in the appropriate direction
    switch (dir) {
        case 'q':
            elem = board->getLevel()[coord_x][coord_y - 1];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            existsG = std::find(std::begin(COLLISION_CREATURES), std::end(COLLISION_CREATURES), elem) != std::end(COLLISION_CREATURES);
            return exists || coord_y == 0 || existsG;
        case 'd':
            elem = board->getLevel()[coord_x][coord_y + 1];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            existsG = std::find(std::begin(COLLISION_CREATURES), std::end(COLLISION_CREATURES), elem) != std::end(COLLISION_CREATURES);
            return exists || coord_y == board->getLevelWidth()-1 || existsG;
        case 'z':
            elem = board->getLevel()[coord_x - 1][coord_y];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            existsG = std::find(std::begin(COLLISION_CREATURES), std::end(COLLISION_CREATURES), elem) != std::end(COLLISION_CREATURES);
            return exists || existsG;
        case 's':
            elem = board->getLevel()[coord_x + 1][coord_y];
            exists = std::find(std::begin(NO_COLLISION_TILES), std::end(NO_COLLISION_TILES), elem) != std::end(NO_COLLISION_TILES);
            existsG = std::find(std::begin(COLLISION_CREATURES), std::end(COLLISION_CREATURES), elem) != std::end(COLLISION_CREATURES);
            return exists || existsG;
    }
    return false;
}

void Pacman::changeCoords() {
    // save old coordinates
    coord_x_old = coord_x;
    coord_y_old = coord_y;
    switch (dir) {
        case 'q': // moving left
            // if travelling through the tunnel at the left
            if (coord_y == 0) {
                coord_y = board->getLevelWidth() - 1;
            }
            else {
                coord_y--;
            }
            break;
        case 'd': // moving right
            // if travelling through the tunnel at the right
            if (coord_y == board->getLevelWidth() - 1) {
                coord_y = 0;
            }
            else {
                coord_y++;
            }
            break;
        case 'z': // moving up
            coord_x--;

            break;
        case 's': // moving down
            coord_x++;
            break;
    }
}

void Pacman::increaseScore(int scoreAdd) {
    // Gain a life for every time we cross a multiple of 10000
    if (score / 10000 < (score + scoreAdd) / 10000) {
        lives++;
    }
    score += scoreAdd;
}

void Pacman::die(){
    lives--;
    mySleep(1000);
    board->changeValue(coord_x, coord_y, 0);
    if (lives != 0) {
        for (int i = 0; i < 4; i++)
            board->changeValue(board->getGhosts()[i]->getCoord_x(), board->getGhosts()[i]->getCoord_y(), board->getGhosts()[i]->getPrevElem());
        board->initGame(); // We place our elements as their initial locations
    }
    else {
        // Deal the game over case
        //board->setGameover(true)
    }
}

int Pacman::increaseKill() {
    killCount++;
    int scoreAdd = 200 * (int) pow(2, killCount - 1); // The score added double at each kill in a row
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