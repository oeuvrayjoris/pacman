//
// Created by Jordan on 30/12/2017.
//

#ifndef IMACGL_CONSTANTS_HPP
#define IMACGL_CONSTANTS_HPP

// directions and icons
const char ALL_DIRS[4] = {'z','q','s','d'};

// Board properties
const int NO_COLLISION_TILES[4] = {0, 1, 2, 3};

// Timers
const int SUPER_MAX   = 500;
const int ONE_UP_MAX  = 13;
const int PELLET_MAX  = 8;
const int PACMAN_MAX  = 30;
const int GHOST_MAX   = 30;
const int RUN_MAX     = 16;
const int DEAD_MAX    = 3;
const int MODE_MAX    = 1000;

// Ghost Names
const int BLINKY = 0;
const int PINKY  = 1;
const int INKY   = 2;
const int CLYDE  = 3;

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

