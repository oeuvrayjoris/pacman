#include <iostream>

#include <glimac/Camera1.hpp>

Camera1::Camera1() {
    x = -3.9;
    y = 4.105;
    z = -6.8;
    angleX = 83;
}

void Camera1::setX(float new_x) {
    x = new_x;
}

void Camera1::setY(float new_y) {
    y = new_y;
}

void Camera1::setZ(float new_z) {
    z = new_z;
}


void Camera1::moveX(float val) {
    x+=val;
    std::cout << "x = " << x << std::endl;
}

void Camera1::moveY(float val) {
    y+=val;
    std::cout << "y = " << y << std::endl;
}

void Camera1::moveZ(float val) {
    z+=val;
    std::cout << "z = " << z << std::endl;
}

void Camera1::moveAngleX(float val) {
    angleX+=val;
    std::cout << "angleX = " << angleX << std::endl;
}

glm::mat4 Camera1::getViewMatrix() const {
    glm::mat4 ViewMatrix;

    ViewMatrix = glm::translate(glm::mat4(1.f),glm::vec3(x, y, z));
    ViewMatrix = glm::rotate(ViewMatrix, angleX, glm::vec3(1, 0, 0));

    return ViewMatrix;
}
