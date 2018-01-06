#include <iostream>

#include <glimac/Camera3.hpp>

Camera3::Camera3() {
    x = -3.9; // = 12 * -0.325
    y = 4.1; // = 20 * 0.205
    z = -5.8; // = 20 * -0.29
    angle_x = 45;
    angle_y = 0;
}

float Camera3::getZ() {
    return z;
}

void Camera3::setX(float new_x) {
    x = new_x;
}

void Camera3::setY(float new_y) {
    y = new_y;

}

void Camera3::setZ(float new_z) {
    z = new_z;

}

void Camera3::setAngleX(float new_angle_x) {
    angle_x = new_angle_x;
}

void Camera3::setAngleY(float new_angle_y) {
    angle_y = new_angle_y;
}

void Camera3::moveX(float val) {
    x+=val;
    std::cout << "x = " << x << std::endl;
}

void Camera3::moveY(float val) {
    y+=val;
    std::cout << "y = " << y << std::endl;
}

void Camera3::moveZ(float val) {
    z+=val;
    std::cout << "z = " << z << std::endl;
}

glm::mat4 Camera3::getViewMatrix() const {
    glm::mat4 ViewMatrix;

    ViewMatrix = glm::translate(glm::mat4(1.f),glm::vec3(x, y, z));
    ViewMatrix = glm::rotate(ViewMatrix, glm::radians(angle_x), glm::vec3(1,0,0));
    ViewMatrix = glm::rotate(ViewMatrix, glm::radians(angle_y), glm::vec3(0,1,0));

    return ViewMatrix;
}
