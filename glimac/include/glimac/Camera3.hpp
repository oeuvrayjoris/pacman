#ifndef CAMERA3_H
#define CAMERA3_H

#include <glimac/glm.hpp>

class Camera3 {
    public:
        // Constructor
        Camera3();

        // Methods
        float getZ();
        void setX(float new_x);
        void setY(float new_y);
        void setZ(float new_z);
        void setAngleX(float new_angle_x);

        void moveX(float val);
        void moveY(float val);
        void moveZ(float val);
        void moveAngleX(float val);
        void moveAngleY(float val);

        glm::mat4 getViewMatrix() const;

    private:
        // Attr
        float x;
        float y;
        float z;
        float angle_x;
};

#endif //CAMERA3_H
