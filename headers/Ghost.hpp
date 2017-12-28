//
// Created by Jordan on 28/12/2017.
//

#ifndef IMACGL_GHOST_HPP
#define IMACGL_GHOST_HPP

#include "Creature.hpp"

class Ghost : public Creature {

public:

    Ghost();

    Ghost(const std::string &name, int x_coord, int y_coord);

    int getState() const;

    void setState(int state);

    float getValue() const;

    void setValue(float value);

private:
    
    int state; // 1 - Normal / 0 - Slowed ghost / -1 - Eaten ghost
    float value;
};


#endif //IMACGL_GHOST_HPP
