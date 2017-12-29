//
// Created by Jordan on 28/12/2017.
//

#include "glimac/Pacman.hpp"

Pacman::Pacman() {
    lives = 3;
    score = 0;
}

Pacman::Pacman(const std::string &name, int x_coord, int y_coord) : Creature(name, x_coord, y_coord) {
    lives = 3;
    score = 0.f;
}

int Pacman::getLives() const {
    return lives;
}

void Pacman::setLives(int lives) {
    Pacman::lives = lives;
}

float Pacman::getScore() const {
    return score;
}

void Pacman::setScore(int score) {
    Pacman::score = score;
}

void Pacman::loseLife() {
    lives--;
}

void Pacman::increaseScore(float value){
    score += value;
}