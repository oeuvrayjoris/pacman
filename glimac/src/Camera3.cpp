#include <iostream>

#include <glimac/Camera3.hpp>

Camera3::Camera3() {
    x = -3.9;
    y = 4.9;
    z = -5.8;
    angle_x = 45;
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

void Camera3::moveX(float val) {
    x+=val;
}

void Camera3::moveY(float val) {
    y+=val;
}

void Camera3::moveZ(float val) {
    z+=val;
}

void Camera3::moveAngleX(float val) {
    angle_x+=val;
}

glm::mat4 Camera3::getViewMatrix() const {
    glm::mat4 ViewMatrix;

    ViewMatrix = glm::translate(glm::mat4(1.f),glm::vec3(x, y, z));
    ViewMatrix = glm::rotate(ViewMatrix, glm::radians(angle_x), glm::vec3(1,0,0));


    return ViewMatrix;
}
