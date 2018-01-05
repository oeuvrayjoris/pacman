//
// Created by Jordan on 30/12/2017.
//

#ifndef IMACGL_CONSTANTS_HPP
#define IMACGL_CONSTANTS_HPP

#include <glimac/glm.hpp>

// directions and icons
const char ALL_DIRS[4] = {'z','q','s','d'};

// Board properties
const int NO_COLLISION_TILES[5] = {0, 1, 2, 3, 10};
const int COLLISION_CREATURES[4] = {11, 12, 13, 14};

// Timers
const int SPEED_FACTOR = 3;

const int SUPER_MAX   = 500 * SPEED_FACTOR;
const int ONE_UP_MAX  = 13 * SPEED_FACTOR;
const int PELLET_MAX  = 8 * SPEED_FACTOR;
const int PACMAN_MAX  = 8 * SPEED_FACTOR;
const int GHOST_MAX   = 10 * SPEED_FACTOR;
const int RUN_MAX     = 16 * SPEED_FACTOR;
const int DEAD_MAX    = 3 * SPEED_FACTOR;
const int MODE_MAX    = 1000 * SPEED_FACTOR;

// Ghost Names
const int BLINKY = 0;
const int PINKY  = 1;
const int INKY   = 2;
const int CLYDE  = 3;

// COLORS
const glm::vec3 WHITE_COLOR = glm::vec3(255, 255, 255);
const glm::vec3 RED_COLOR = glm::vec3(255, 0, 0);
const glm::vec3 MAGENTA_COLOR = glm::vec3(255,0,255);
const glm::vec3 CYAN_COLOR = glm::vec3(0,255,255);
const glm::vec3 ORANGE_COLOR = glm::vec3(255,165,0);
const glm::vec3 BLUE_COLOR = glm::vec3(0,0,139);
const glm::vec3 BLACK_COLOR = glm::vec3(0,0,0);

static void mySleep(int sleepMs) {
#ifdef LINUX
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}

/*
 * 0 - Empty case
 * 1 - Dot case
 * 2 - Pellet case
 * 3 - Bonus fruit case
 *
 * 4 - Edge
 * Not useful for now
 * 5 - Top left corner
 * 6 - Top right corner
 * 7 - Bottom left corner
 * 8 - Bottom right corner
 *
 * 10 - Pacman
 * 11 - Ghost 1
 * 12 - Ghost 2
 * 13 - Ghost 3
 * 14 - Ghost 4
 *
 * 20 - Gate
 */

#endif //IMACGL_CONSTANTS_HPP

