//
// Created by Jordan on 28/12/2017.
//

#include "../headers/Item.hpp"

// Constructors

Item::Item() {
    state = 1;
}

Item::Item(int x_coord, int y_coord) : x_coord(x_coord), y_coord(y_coord) {
    state = 1;
}

// Getters and setters

int Item::getX_coord() const {
    return x_coord;
}

void Item::setX_coord(int x_coord) {
    Item::x_coord = x_coord;
}

int Item::getY_coord() const {
    return y_coord;
}

void Item::setY_coord(int y_coord) {
    Item::y_coord = y_coord;
}

int Item::getState() const {
    return state;
}

void Item::setState(int state) {
    Item::state = state;
}
