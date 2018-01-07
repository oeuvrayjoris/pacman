#ifndef CAMERA1_H
#define CAMERA1_H

#include <glimac/glm.hpp>

class Camera1 {
    public:
        // Constructor
        Camera1();

        // Methods
        void setX(float new_x);
        void setY(float new_y);
        void setZ(float new_z);

        void moveX(float val);
        void moveY(float val);
        void moveZ(float val);
        void moveAngleX(float val);

        glm::mat4 getViewMatrix() const;

    private:
        // Attr
        float x;
        float y;
        float z;
        float angleX;
};

#endif //CAMERA1_H
