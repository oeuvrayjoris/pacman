//
// Created by Jordan on 28/12/2017.
//

#include "../headers/Gem.hpp"

Gem::Gem() {
    value = 50;
}

Gem::Gem(int x_coord, int y_coord) : Item(x_coord, y_coord) {
    value = 50;

}
