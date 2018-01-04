#include "glimac/Board.hpp"
#include "glimac/Pacman.hpp"
#include "glimac/Ghost.hpp"
#include "glimac/Pellet.hpp"

/* CONSTRUCTOR */
Board::Board() {
	levelHeight = 25;
	levelWidth = 25;

	pacman = new Pacman(this);
	for (int i = 0; i < 4; ++i) {
		ghosts[i] = new Ghost(this);
		pellets[i] = new Pellet(this);
	}

    load();
}

// Destructor
Board::~Board() {
    delete pacman;
    for (int i = 0; i < 4; ++i) {
        delete ghosts[i];
        delete pellets[i];
    }
}

/* METHODS */

void Board::load() {
    level = {
            {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
            {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4},
            {4, 2, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 2, 4},
            {4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 4},
            {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4},
            {4, 1, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 1, 4},
            {4, 1, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 1, 4},
            {4, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 4},
            {4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4},
            {0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 11, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 4, 1, 4, 0, 4, 4, 4, 20, 4, 4, 4, 0, 4, 1, 4, 0, 0, 0, 0, 0},
            {4, 4, 4, 4, 4, 4, 1, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 4, 1, 4, 4, 4, 4, 4, 4},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 4, 12, 0, 13, 0, 14, 4, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {4, 4, 4, 4, 4, 4, 1, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 4, 1, 4, 4, 4, 4, 4, 4},
            {0, 0, 0, 0, 0, 4, 1, 4, 0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 1, 4, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0},
            {4, 4, 4, 4, 4, 4, 1, 4, 0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 1, 4, 4, 4, 4, 4, 4},
            {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4},
            {4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 1, 4, 4, 4, 4, 1, 4},
            {4, 2, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 2, 4},
            {4, 4, 4, 4, 1, 4, 1, 4, 1, 4, 4, 4, 4, 4, 4, 4, 1, 4, 1, 4, 1, 4, 4, 4, 4},
            {4, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 4},
            {4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4},
            {4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4},
            {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}
    };
    levelWidth = level.at(0).size();
    levelHeight = level.size();
    pacman->setLeftDots(0);

    int elem, k = 0;
    for (int i = 0; i < levelHeight; i++) {
        for (int j = 0; j < levelWidth; j++) {
            elem = level[i][j];
            switch (elem){
                case 1: // normal dots
                    pacman->setLeftDots(pacman->getLeftDots() + 1);
                    break;
                case 2: // pellet
                    pacman->setLeftDots(pacman->getLeftDots() + 1);
                    pellets[k]->setCoord_x(i);
                    pellets[k]->setCoord_y(j);
                    k++;
                    break;
                case 10: // pacman
                    pacman->setCoord_x_init(i);
                    pacman->setCoord_y_init(j);
                    break;
                case 11: // ghost 1
                    ghosts[BLINKY]->setCoord_x_init(i);
                    ghosts[BLINKY]->setCoord_y_init(j);
                    ghosts[BLINKY]->setColorInit(RED_COLOR);
                    ghosts[BLINKY]->setId(elem);
                    ghosts[BLINKY]->setPrevElem(0);
                    break;
                case 12: // ghost 2
                    ghosts[PINKY]->setCoord_x_init(i);
                    ghosts[PINKY]->setCoord_y_init(j);
                    ghosts[PINKY]->setColorInit(MAGENTA_COLOR);
                    ghosts[PINKY]->setId(elem);
                    ghosts[PINKY]->setPrevElem(0);
                    break;
                case 13: // ghost 3
                    ghosts[INKY]->setCoord_x_init(i);
                    ghosts[INKY]->setCoord_y_init(j);
                    ghosts[INKY]->setColorInit(CYAN_COLOR);
                    ghosts[INKY]->setId(elem);
                    ghosts[INKY]->setPrevElem(0);
                    break;
                case 14: // ghost 4
                    ghosts[CLYDE]->setCoord_x_init(i);
                    ghosts[CLYDE]->setCoord_y_init(j);
                    ghosts[CLYDE]->setColorInit(ORANGE_COLOR);
                    ghosts[CLYDE]->setId(elem);
                    ghosts[CLYDE]->setPrevElem(0);
                    break;
                case 20:
                    gateCoord_x = i;
                    gateCoord_y = j;
                    break;
            }
        }
    }
    initGame();
}

void Board::changeValue(int m, int n, int value) {
    level[m][n] = value;
}

void Board::launchGame() {
    pacman->setScore(0);
    pacman->setLives(3);
    bool gameOver = false;
    load();
}

void Board::initGame(){

    pacman->setCoord_x(pacman->getCoord_x_init());
    pacman->setCoord_y(pacman->getCoord_y_init());
    pacman->setDir('q');
    pacman->setDirOld('q');
    pacman->setWait(0);
    pacman->setSuper(0);
    for (int i = 0; i < 4; ++i) {
        ghosts[i]->setCoord_x(ghosts[i]->getCoord_x_init());
        ghosts[i]->setCoord_y(ghosts[i]->getCoord_y_init());
        ghosts[i]->setMode('w');
        ghosts[i]->setWait(0);
    }
    ghosts[BLINKY]->setMode('s');
    ghosts[BLINKY]->setModeOld('s');
    ghosts[BLINKY]->setDir('q');
    if (pacman->getLeftDots() <= 235) {
        ghosts[PINKY]->setMode('e');
    }
    if (pacman->getLeftDots() <= 200) {
        ghosts[INKY]->setMode('e');
    }
    if (pacman->getLeftDots() <= 165) {
        ghosts[CLYDE]->setMode('e');
    }
}

void Board::moveGhosts() {
    // check for ghost mode changes
    if (pacman->getSuper() == SUPER_MAX) {
        pacman->setKillCount(0);
        for (int i = 0; i < 4; ++i) {
            if (ghosts[i]->getMode() != 'd') { // if the ghost is not dead yet
                ghosts[i]->setColor(BLUE_COLOR);
            }
            if (ghosts[i]->getMode() == 's' || ghosts[i]->getMode() == 'c') { // if the ghost is chasing / scattering
                ghosts[i]->setMode('f'); // become frightened
            }
        }
    }
    // We allow the ghosts to exit
    if (pacman->getLeftDots() == 235 && ghosts[PINKY]->getMode() == 'w') {
        ghosts[PINKY]->setMode('e');
    }
    if (pacman->getLeftDots() == 200 && ghosts[INKY]->getMode() == 'w') {
        ghosts[INKY]->setMode('e');
        std::cout << "INKY !" << std::endl;
    }
    if (pacman->getLeftDots() == 165 && ghosts[CLYDE]->getMode() == 'w') {
        ghosts[CLYDE]->setMode('e');
        std::cout << "CLYDE !" << std::endl;
    }
    for (int i = 0; i < 4; i++) {
        ghosts[i]->move(pacman->getCoord_x(), pacman->getCoord_y());
    }
}

void Board::checkForDeath() {
    for (int i = 0; i < 4; ++i) {
        if (pacman->getCoord_x() == ghosts[i]->getCoord_x() && pacman->getCoord_y() == ghosts[i]->getCoord_y() &&
            ghosts[i]->getMode() != 'd' && ghosts[i]->getMode() != 'n') { // If the ghosts are chasing/scattering
            if (ghosts[i]->getMode() != 'f') { // If the ghosts are not frightened
                pacman->die();
            }
            else {
                pacman->increaseKill();
                ghosts[i]->die();
            }
        }
    }
}

void Board::handleModes() {

}

void importGame() {

}

void exportGame() {

}


/* GETTERS */
int Board::getLevelHeight(){
    return levelHeight;
}

int Board::getLevelWidth(){
    return levelWidth;
}

std::vector<std::vector<int>> Board::getLevel() {
	return level;
}

int Board::getGateCoord_x() const {
    return gateCoord_x;
}

int Board::getGateCoord_y() const {
    return gateCoord_y;
}

bool Board::isSuper() const {
    return super;
}

Pacman *Board::getPacman() const {
    return pacman;
}

Ghost *const *Board::getGhosts() const {
    return ghosts;
}

/* SETTERS */
void Board::setLevelHeight(int new_m){
	levelHeight = new_m;
}

void Board::setLevelWidth(int new_n){
	levelWidth = new_n;
}

void Board::setLevel(std::vector<std::vector<int>> new_tab) {
	level = new_tab;
}

void Board::setGateCoord_x(int gateCoord_x) {
    Board::gateCoord_x = gateCoord_x;
}

void Board::setGateCoord_y(int gateCoord_y) {
    Board::gateCoord_y = gateCoord_y;
}

void Board::setSuper(bool super) {
    Board::super = super;
}