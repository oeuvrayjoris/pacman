#ifndef TRACKBALL_CAMERA_H
#define TRACKBALL_CAMERA_H

#include <glimac/glm.hpp>

class TrackballCamera {
    public:
        // Constructor
        TrackballCamera();

        // Methods
        void moveFront(float delta);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        glm::mat4 getViewMatrix() const;
        void print();

    private:
        // Attr
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;
};

#endif //TRACKBALL_CAMERA_H
