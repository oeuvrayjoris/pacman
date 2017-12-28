//
// Created by Jordan on 27/12/2017.
//

#include "../headers/Creature.hpp"

// Constructors

Creature::Creature() {}

Creature::Creature(const std::string &name, int x_coord, int y_coord) : name(name), x_coord(x_coord), y_coord(y_coord) {
    speed = 0.5f;
    move_up, move_down, move_left, move_right = false;
}

// Getters and setters

const std::string &Creature::getName() const {
    return name;
}

void Creature::setName(const std::string &name) {
    Creature::name = name;
}

float Creature::getSpeed() const {
    return speed;
}

void Creature::setSpeed(float speed) {
    Creature::speed = speed;
}

int Creature::getX_coord() const {
    return x_coord;
}

void Creature::setX_coord(int x_coord) {
    Creature::x_coord = x_coord;
}

int Creature::getY_coord() const {
    return y_coord;
}

void Creature::setY_coord(int y_coord) {
    Creature::y_coord = y_coord;
}

bool Creature::isMove_up() const {
    return move_up;
}

void Creature::setMove_up(bool move_up) {
    Creature::move_up = move_up;
}

bool Creature::isMove_down() const {
    return move_down;
}

void Creature::setMove_down(bool move_down) {
    Creature::move_down = move_down;
}

bool Creature::isMove_left() const {
    return move_left;
}

void Creature::setMove_left(bool move_left) {
    Creature::move_left = move_left;
}

bool Creature::isMove_right() const {
    return move_right;
}

void Creature::setMove_right(bool move_right) {
    Creature::move_right = move_right;
}

// Other methods

void Creature::setDirection(int dir){
    move_up = move_down = move_left = move_right = false;
    if(dir == 1)
        move_up = true;
    else if(dir == 2)
        move_down = true;
    else if(dir == 3)
        move_left = true;
    else if(dir == 4)
        move_right = true;
}