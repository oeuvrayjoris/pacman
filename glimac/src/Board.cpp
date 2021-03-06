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

void Board::load(std::string &fileName, bool newGame) {

    DataManager dataManager;
    rapidjson::Document d = dataManager.importFromJson(fileName);

    level.clear();

    levelHeight = d["levelHeight"].GetInt();
    levelWidth = d["levelWidth"].GetInt();
    if (newGame) {
        pacman->setScore(d["score"].GetInt());
        pacman->setLives(d["lives"].GetInt());
    }

    const rapidjson::Value &jsonLevel = d["level"];

    for (rapidjson::SizeType i = 0; i < jsonLevel.Size(); i++) { // Uses SizeType instead of size_t
        const rapidjson::Value &jsonSubLevel = jsonLevel[i];
        std::vector<int> subVector;
        for (rapidjson::SizeType j = 0; j < jsonSubLevel.Size(); j++){
            subVector.push_back(jsonSubLevel[j].GetInt());
        }
        level.push_back(subVector);
    }

    //loadConfig(d);

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
}

// Initialize values at each game start/restart
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
        ghosts[i]->setPrevElem(0);
    }
    ghosts[BLINKY]->setMode('s');
    ghosts[BLINKY]->setModeOld('s');
    ghosts[BLINKY]->setDir('q');
    if (pacman->getLeftDots() <= 190) {
        ghosts[PINKY]->setMode('e');
    }
    if (pacman->getLeftDots() <= 155) {
        ghosts[INKY]->setMode('e');
    }
    if (pacman->getLeftDots() <= 120) {
        ghosts[CLYDE]->setMode('e');
    }
}

void Board::nextLevel(){
    // Faire un truc pour l'affichage
    initGame();
}

void Board::moveGhosts() {
    // check for ghost mode changes
    if (pacman->getSuper() == SUPER_MAX) { // if Pacman just turned in super mode
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
    if (pacman->getLeftDots() == 190 && ghosts[PINKY]->getMode() == 'w') {
        ghosts[PINKY]->setMode('e');
    }
    if (pacman->getLeftDots() == 155 && ghosts[INKY]->getMode() == 'w') {
        ghosts[INKY]->setMode('e');
        std::cout << "INKY !" << std::endl;
    }
    if (pacman->getLeftDots() == 120 && ghosts[CLYDE]->getMode() == 'w') {
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
    // handle super pacman
    if (pacman->getSuper()) {
        pacman->setSuper(pacman->getSuper() - 1); // decrease super counter
        if (pacman->getSuper() <= 112 && pacman->getSuper() % 28 == 0) { // We alternate the color of the ghosts
            for (int i = 0; i < 4; ++i)
                if (ghosts[i]->getColor() == BLUE_COLOR) {
                    ghosts[i]->setColor(WHITE_COLOR);
                }
        }
        if (pacman->getSuper() <= 98 && (pacman->getSuper() + 14) % 28 == 0) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->getColor() == WHITE_COLOR && ghosts[i]->getMode() != 'd' && ghosts[i]->getMode() != 'n') {
                    ghosts[i]->setColor(BLUE_COLOR);
                }
            }
        }
        if (!pacman->getSuper()) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->getMode() != 'd' && ghosts[i]->getMode() != 'n') { // If they are not dead / entering the prison
                    ghosts[i]->setColor(ghosts[i]->getColorInit());
                }
                if (ghosts[i]->getMode() == 'f') { // if the ghost was frightned
                    ghosts[i]->setModeOld(ghosts[i]->getMode());
                    ghosts[i]->setMode('c');
                    //ghosts[i]->setMode('s'); // he starts scaterring
                }
            }
        }
    }

    // We alternate chase and scatter mode          /!\ Décommenter quand le 'c' sera fait
    
    if (ghostModeTimer) {
        --ghostModeTimer;
        if (ghostModeTimer == MODE_MAX / 4) {
            for (int i = 0; i < 4; ++i) {
                if (ghosts[i]->getMode() == 'c') {
                    ghosts[i]->setMode('s');
                }
            }
        }
    }
    else {
        for (int i = 0; i < 4; ++i) {
            if (ghosts[i]->getMode() == 's') {
                ghosts[i]->setMode('c');
            }
        }
        ghostModeTimer = MODE_MAX;
    }
}

void Board::loadConfig(rapidjson::Document &d, bool newGame) {

    level.clear();

    levelHeight = d["levelHeight"].GetInt();
    levelWidth = d["levelWidth"].GetInt();
    if (newGame) {
        pacman->setScore(d["score"].GetInt());
        pacman->setLives(d["lives"].GetInt());
    }

    const rapidjson::Value &jsonLevel = d["level"];

    for (rapidjson::SizeType i = 0; i < jsonLevel.Size(); i++) { // Uses SizeType instead of size_t
        const rapidjson::Value &jsonSubLevel = jsonLevel[i];
        std::vector<int> subVector;
        for (rapidjson::SizeType j = 0; j < jsonSubLevel.Size(); j++){
            subVector.push_back(jsonSubLevel[j].GetInt());
        }
        level.push_back(subVector);
    }


}

void Board::exportGame() {

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