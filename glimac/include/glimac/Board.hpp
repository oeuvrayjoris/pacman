#ifndef IMACGL_BOARD_HPP
#define IMACGL_BOARD_HPP

#include <iostream>
#include <vector>
#include "Constants.hpp"
#include <rapidjson/document.h>
#include <glimac/DataManager.hpp>

class Pacman;
class Ghost;
class Pellet;

class Board {
public:
    // Constructors
    Board();

    // Destructor
    ~Board();

    // Methods
    void load();
    void changeValue(int m, int n, int value);
    void launchGame();
    void initGame();
    void nextLevel();
    void moveGhosts();
    void checkForDeath();
    void handleModes();

    void loadConfig();
    void exportGame();

    // Getters
    int getLevelHeight();
    int getLevelWidth();
    std::vector<std::vector<int>> getLevel();
    int getGateCoord_x() const;
    int getGateCoord_y() const;
    bool isSuper() const;

    Pacman *getPacman() const;
    Ghost *const *getGhosts() const;

    // Setters
    void setLevelHeight(int new_m);
    void setLevelWidth(int new_n);
    void setLevel(std::vector<std::vector<int>> new_tab);
    void setGateCoord_x(int gateCoord_x);
    void setGateCoord_y(int gateCoord_y);
    void setSuper(bool super);

private:
    // Attr
    int levelHeight;
    int levelWidth;
    std::vector<std::vector<int>> level;


    int pelletTimer = PELLET_MAX;
    //int pelletColor = WHITE_COLOR;
    int ghostModeTimer = MODE_MAX;

    Pacman* pacman;
    Ghost* ghosts[4];
    Pellet* pellets[4];

    int gateCoord_x;
    int gateCoord_y;
    bool super;
};

#endif