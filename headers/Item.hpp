//
// Created by Jordan on 28/12/2017.
//

#ifndef IMACGL_ITEM_HPP
#define IMACGL_ITEM_HPP


class Item {

public:

    // Constructors

    Item();

    Item(int x_coord, int y_coord);

    // Getters and setters

    int getX_coord() const;

    void setX_coord(int x_coord);

    int getY_coord() const;

    void setY_coord(int y_coord);

    int getState() const;

    void setState(int state);

protected:
    int x_coord;
    int y_coord;
    int state;
    float value;
};


#endif //IMACGL_ITEM_HPP
