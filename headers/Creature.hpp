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

    bool isMove_up() const;

    void setMove_up(bool move_up);

    bool isMove_down() const;

    void setMove_down(bool move_down);

    bool isMove_left() const;

    void setMove_left(bool move_left);

    bool isMove_right() const;

    void setMove_right(bool move_right);

    // Other methods

    void setDirection(int dir);

protected:
    std::string name;
    float speed;
    int x_coord;
    int y_coord;
    bool move_up, move_down, move_left, move_right;


};


#endif //IMACGL_CREATURE_HPP
