//
// Created by Jordan on 27/12/2017.
//

#ifndef IMACGL_CREATURE_HPP
#define IMACGL_CREATURE_HPP

#include <iostream>

class Creature {

public:
    Creature();

    Creature(const std::string &name, int x_coord, int y_coord);

    // Getters and setters

    const std::string &getName() const;

    void setName(const std::string &name);

    float getSpeed() const;

    void setSpeed(float speed);

    int getX_coord() const;

    void setX_coord(int x_coord);

    int getY_coord() const;

    void setY_coord(int y_coord);

    int getDirection() const;

    void setDirection(int direction);

    // Other methods

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();

protected:
    std::string name;
    float speed;
    int x_coord;
    int y_coord;
    int direction; // 1 for up, 2 for down, 3 for left, 4 for right


};


#endif //IMACGL_CREATURE_HPP
