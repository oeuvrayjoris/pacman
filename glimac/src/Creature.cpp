//
// Created by Jordan on 27/12/2017.
//

#include "glimac/Creature.hpp"

// Constructors

Creature::Creature() {}

Creature::Creature(const std::string &name, int x_coord, int y_coord) : name(name), x_coord(x_coord), y_coord(y_coord) {
    speed = 0.5f;
    //move_up, move_down, move_left, move_right = false;
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

int Creature::getDirection() const {
    return direction;
}

void Creature::setDirection(int direction) {
    Creature::direction = direction;
}

// Other methods

void Creature::moveUp() {
    x_coord--;
}

void Creature::moveDown() {
    x_coord++;
}

void Creature::moveLeft(){
    y_coord--;
}

void Creature::moveRight(){
    y_coord++;
}
