//
// Created by Jordan on 28/12/2017.
//

#include "glimac/Ghost.hpp"

Ghost::Ghost() {
    value = 800.f;
    state = 1;
}

Ghost::Ghost(const std::string &name, int x_coord, int y_coord) : Creature(name, x_coord, y_coord) {
    value = 800.f;
    state = 1;
}

int Ghost::getState() const {
    return state;
}

void Ghost::setState(int state) {
    Ghost::state = state;
}

float Ghost::getValue() const {
    return value;
}

void Ghost::setValue(float value) {
    Ghost::value = value;
}
